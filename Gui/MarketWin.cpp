#include "MarketWin.h"

#include <qmessagebox.h>
#include <qsql.h>
#include <qsqlquery.h>
#include <qclipboard.h>
#include <qtconcurrentrun.h>
#include <qfuture.h>

#include "WEmailList.h"
#include "WWordList.h"
#include "WGroupList.h"
#include "WSystem.h"
#include "WOther.h"
#include "WEmailTest.h"
#include "WFeedback.h"
#include "MarketUpdate.h"
#include "WKeyWordGroup.h"

#include "json.hpp"

#include <map>
#include <string>

#include <Windows.h>
using namespace std;

extern string appFile;
extern map<long long, wstring> WinGroupList;

MarketWin::MarketWin(QWidget* parent)
	: QMainWindow(parent)
	, sql("SELECT Time,QQId,GroupId,Type,Word FROM log ORDER BY Time;")
	, model(NULL)
{
	ui.setupUi(this);

	//����Ĭ��ֵ
	//QssStyle::setStyle(":/moren.qss");

	ui.check_updata->setChecked(true);

	db = QSqlDatabase::addDatabase("QSQLITE");
	//db.setDatabaseName("./log.db");
	db.setDatabaseName(":memory:");

	if (!db.open())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�޷������ݿ�"), QMessageBox::Ok);
	}

	readLog();

	connect(ui.button_smtpList, SIGNAL(clicked()), this, SLOT(OpenSmtpList()));
	connect(ui.button_wordList, SIGNAL(clicked()), this, SLOT(OpenWordList()));
	connect(ui.button_groupList, SIGNAL(clicked()), this, SLOT(OpenGroupList()));
	connect(ui.button_system, SIGNAL(clicked()), this, SLOT(OpenSystem()));
	connect(ui.button_keyWordGroup, SIGNAL(clicked()), this, SLOT(OpenKeyWordGroup()));
	connect(ui.button_emailTest, SIGNAL(clicked()), this, SLOT(OpenEmailTest()));
	connect(ui.button_other, SIGNAL(clicked()), this, SLOT(OpenOher()));
	connect(ui.button_update, SIGNAL(clicked()), this, SLOT(OpenUpdata()));
	//connect(ui.button_feedback, SIGNAL(clicked()), this, SLOT(OpenFeedback()));
	connect(ui.button_filter, SIGNAL(clicked()), this, SLOT(FilterLogSql()));
	connect(ui.button_updateList, SIGNAL(clicked()), this, SLOT(onUpdataList()));
	connect(ui.button_clearLog, SIGNAL(clicked()), this, SLOT(onClearLog()));
	connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(slotRowDoubleClicked(const QModelIndex&)));
}

MarketWin::~MarketWin()
{

}

//�ر��¼�
void MarketWin::closeEvent(QCloseEvent* event)
{
	//updateLog.cancel();

	db.close();
}

//��ȡͳ������
void MarketWin::readCount()
{
	try
	{
		boost::property_tree::wptree value;

		json::read_json(appFile + "conf.json", value);
		int temp_countDay = value.get<int>(L"Main.CountDay", 0);
		int temp_countAll = value.get<int>(L"Main.CountAll", 0);

		//�� �� �۷�
		QString countDay(to_string(temp_countDay).c_str());
		ui.edit_countDay->setText(countDay);

		QString countAll(to_string(temp_countAll).c_str());
		ui.edit_countAll->setText(countAll);

		int temp_count = WinGroupList.size();
		QString countGroup(to_string(temp_count).c_str());

		ui.edit_countGroup->setText(countGroup);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡjson�쳣"), QMessageBox::Ok);
		return;
	}

	return;
}

//������־����
void MarketWin::FilterLogSql()
{
	try
	{
		bool or = false;
		sql = "SELECT Time,QQId,GroupId,Type,Word FROM log WHERE Type IN(";
		if (ui.check_ok->isChecked())
		{
			sql += QString::fromLocal8Bit("'���ͳɹ�'");
			or = true;
		}
		if (ui.check_error->isChecked())
		{
			if (or )
				sql += ",";

			sql += QString::fromLocal8Bit("'����ʧ��'");
			or = true;
		}
		if (ui.check_intoGroup->isChecked())
		{
			if (or )
				sql += ",";

			sql += QString::fromLocal8Bit("'��Ա��Ⱥ'");
			or = true;
		}
		if (ui.check_quit->isChecked())
		{
			if (or )
				sql += ",";

			sql += QString::fromLocal8Bit("'��Ա��Ⱥ'");
			or = true;
		}
		if (ui.check_keyWord->isChecked())
		{
			if (or )
				sql += ",";

			sql += QString::fromLocal8Bit("'�����ؼ���'");
			or = true;
		}
		if (ui.check_system->isChecked())
		{
			if (or )
				sql += ",";

			sql += QString::fromLocal8Bit("'ϵͳ'");
			or = true;
		}
		sql += ") ORDER BY Time;";


		onUpdataList();


		ui.tableView->scrollToBottom();//�������õ�
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡ���ݿ��쳣"), QMessageBox::Ok);
		return;
	}
}

//��ȡ����
void MarketWin::readLog()
{
	try
	{
		//��ȡͳ�ƴ���
		readCount();
		//QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
		//db.setDatabaseName("./log.db");


		if (!db.open())
		{
			throw exception("��ȡ��־ʧ�� �޷������ݿ�");
		}

		QSqlQuery query(db);
		query.exec("CREATE TABLE IF NOT EXISTS log (Time DATETIME,QQId INT (15),GroupId INT (15),Type CHAR (20),Word TEXT);");

		model = new mySqlQueryModel(this);

		model->setQuery(sql, db);// "SELECT Time,QQId,GroupId,Type,Word FROM log ORDER BY Time;");

		model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("����ʱ��"));
		model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("QQ"));
		model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("Ⱥ��"));
		model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("����"));
		model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("����"));


		ui.tableView->setModel(model);

		//db.close();

		ui.tableView->setColumnWidth(0, 170);
		ui.tableView->setColumnWidth(1, 110);
		ui.tableView->setColumnWidth(2, 110);
		ui.tableView->setColumnWidth(3, 90);
		ui.tableView->setColumnWidth(4, 400);


		ui.tableView->setWordWrap(true);
		//ui.tableView->resizeRowsToContents();//����Ӧ�����ı�
		ui.tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);//����Ӧ��Ԫ�񳤶�


		ui.tableView->scrollToBottom();//�������õ�


		////ʵʱ����
		//QFuture <void> future = QtConcurrent::run([&]()
		//	{
		//		//��ʱ����
		//		//int rowCount = model->rowCount();
		//		while (true)
		//		{
		//			Sleep(3000);
		//			////��ȡͳ�ƴ���


		//			
		//		}

		//	}
		//);

		ui.tableView->resizeRowsToContents();//����Ӧ�����ı�
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡ���ݿ��쳣"), QMessageBox::Ok);
		return;
	}
}

//˫���¼�
void MarketWin::slotRowDoubleClicked(const QModelIndex& w)
{
	QString buf = w.data().toString();

	//���Ƶ����а�
	QClipboard* board = QApplication::clipboard();
	board->setText(buf);

	//��ʾ����
	ui.label_state->setText(QString::fromLocal8Bit("(�Ѹ��Ƶ����а�)"));

	//��ʱ�����ʾ����
	QFuture < void > future = QtConcurrent::run([&]()
	{
		Sleep(5000);
		ui.label_state->clear();
	}
	);

}

//��������־��ť
void MarketWin::onClearLog()
{
	if (db.isOpen())
	{
		QSqlQuery query(db);
		query.exec("DELETE FROM log;");

		onUpdataList();
	}
}


void MarketWin::sqlExec(const char* sql)
{
	if (db.isOpen() && model != NULL)
	{
		static int count = 0;

		QSqlQuery query(db);
		query.exec(sql);
		count++;

		if (count > 300)
		{
			count = 0;
			query.exec("DELETE FROM log WHERE time < datetime('now','localtime','-10 minute');");
		}

		//��������
		if (ui.check_updata->isChecked())
		{
			readCount();

			model->setQuery(this->sql, db);
			//logColor();//������ɫ

			//�б�仯ʱ
			//if (rowCount != model->rowCount())
			//{
			//ui.tableView->update();
			ui.tableView->resizeRowsToContents();//����Ӧ�����ı�
			ui.tableView->scrollToBottom();//�������õ�
			//rowCount = model->rowCount();
			//}
		}
	}
}

//ˢ���б�
void MarketWin::onUpdataList()
{
	model->setQuery(sql, db);
}

//��smtp�б�
void MarketWin::OpenSmtpList()
{
	WEmailList* a = new WEmailList;
	a->show();
}

//�������б�
void MarketWin::OpenWordList()
{
	WWordList* a = new WWordList;
	a->show();
}

//��Ⱥ�б�
void MarketWin::OpenGroupList()
{
	WGroupList* a = new WGroupList;

	a->show();
}

//��Ⱥ�ؼ����б�
void MarketWin::OpenKeyWordGroup()
{
	WKeyWordGroup* a = new WKeyWordGroup;

	a->show();
}


//����������
void MarketWin::OpenOher()
{
	WOther* a = new WOther;
	a->show();
}

//��ϵͳ����
void MarketWin::OpenSystem()
{
	WSystem* a = new WSystem;
	a->show();
}

//���������
void MarketWin::OpenEmailTest()
{
	WEmailTest* a = new WEmailTest;
	a->show();
}

//���߸���
void MarketWin::OpenUpdata()
{
	MarketUpdate* a = new MarketUpdate;
	a->show();

}

//�û�����
void MarketWin::OpenFeedback()
{
	WFeedback* a = new WFeedback;
	a->show();
}