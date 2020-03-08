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

	//设置默认值
	//QssStyle::setStyle(":/moren.qss");

	ui.check_updata->setChecked(true);

	db = QSqlDatabase::addDatabase("QSQLITE");
	//db.setDatabaseName("./log.db");
	db.setDatabaseName(":memory:");

	if (!db.open())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("无法打开数据库"), QMessageBox::Ok);
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

//关闭事件
void MarketWin::closeEvent(QCloseEvent* event)
{
	//updateLog.cancel();

	db.close();
}

//读取统计数量
void MarketWin::readCount()
{
	try
	{
		boost::property_tree::wptree value;

		json::read_json(appFile + "conf.json", value);
		int temp_countDay = value.get<int>(L"Main.CountDay", 0);
		int temp_countAll = value.get<int>(L"Main.CountAll", 0);

		//今发 和 累发
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
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("读取json异常"), QMessageBox::Ok);
		return;
	}

	return;
}

//过滤日志内容
void MarketWin::FilterLogSql()
{
	try
	{
		bool or = false;
		sql = "SELECT Time,QQId,GroupId,Type,Word FROM log WHERE Type IN(";
		if (ui.check_ok->isChecked())
		{
			sql += QString::fromLocal8Bit("'发送成功'");
			or = true;
		}
		if (ui.check_error->isChecked())
		{
			if (or )
				sql += ",";

			sql += QString::fromLocal8Bit("'发送失败'");
			or = true;
		}
		if (ui.check_intoGroup->isChecked())
		{
			if (or )
				sql += ",";

			sql += QString::fromLocal8Bit("'成员进群'");
			or = true;
		}
		if (ui.check_quit->isChecked())
		{
			if (or )
				sql += ",";

			sql += QString::fromLocal8Bit("'成员退群'");
			or = true;
		}
		if (ui.check_keyWord->isChecked())
		{
			if (or )
				sql += ",";

			sql += QString::fromLocal8Bit("'触发关键词'");
			or = true;
		}
		if (ui.check_system->isChecked())
		{
			if (or )
				sql += ",";

			sql += QString::fromLocal8Bit("'系统'");
			or = true;
		}
		sql += ") ORDER BY Time;";


		onUpdataList();


		ui.tableView->scrollToBottom();//滚动条置底
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("读取数据库异常"), QMessageBox::Ok);
		return;
	}
}

//读取内容
void MarketWin::readLog()
{
	try
	{
		//读取统计次数
		readCount();
		//QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
		//db.setDatabaseName("./log.db");


		if (!db.open())
		{
			throw exception("读取日志失败 无法打开数据库");
		}

		QSqlQuery query(db);
		query.exec("CREATE TABLE IF NOT EXISTS log (Time DATETIME,QQId INT (15),GroupId INT (15),Type CHAR (20),Word TEXT);");

		model = new mySqlQueryModel(this);

		model->setQuery(sql, db);// "SELECT Time,QQId,GroupId,Type,Word FROM log ORDER BY Time;");

		model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("日期时间"));
		model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("QQ"));
		model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("群号"));
		model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("类型"));
		model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("内容"));


		ui.tableView->setModel(model);

		//db.close();

		ui.tableView->setColumnWidth(0, 170);
		ui.tableView->setColumnWidth(1, 110);
		ui.tableView->setColumnWidth(2, 110);
		ui.tableView->setColumnWidth(3, 90);
		ui.tableView->setColumnWidth(4, 400);


		ui.tableView->setWordWrap(true);
		//ui.tableView->resizeRowsToContents();//自适应多行文本
		ui.tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);//自适应单元格长度


		ui.tableView->scrollToBottom();//滚动条置底


		////实时更新
		//QFuture <void> future = QtConcurrent::run([&]()
		//	{
		//		//定时更新
		//		//int rowCount = model->rowCount();
		//		while (true)
		//		{
		//			Sleep(3000);
		//			////读取统计次数


		//			
		//		}

		//	}
		//);

		ui.tableView->resizeRowsToContents();//自适应多行文本
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("读取数据库异常"), QMessageBox::Ok);
		return;
	}
}

//双击事件
void MarketWin::slotRowDoubleClicked(const QModelIndex& w)
{
	QString buf = w.data().toString();

	//复制到剪切板
	QClipboard* board = QApplication::clipboard();
	board->setText(buf);

	//提示内容
	ui.label_state->setText(QString::fromLocal8Bit("(已复制到剪切板)"));

	//定时清除提示内容
	QFuture < void > future = QtConcurrent::run([&]()
	{
		Sleep(5000);
		ui.label_state->clear();
	}
	);

}

//点击清空日志按钮
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

		//主动更新
		if (ui.check_updata->isChecked())
		{
			readCount();

			model->setQuery(this->sql, db);
			//logColor();//设置颜色

			//列表变化时
			//if (rowCount != model->rowCount())
			//{
			//ui.tableView->update();
			ui.tableView->resizeRowsToContents();//自适应多行文本
			ui.tableView->scrollToBottom();//滚动条置底
			//rowCount = model->rowCount();
			//}
		}
	}
}

//刷新列表
void MarketWin::onUpdataList()
{
	model->setQuery(sql, db);
}

//打开smtp列表
void MarketWin::OpenSmtpList()
{
	WEmailList* a = new WEmailList;
	a->show();
}

//打开内容列表
void MarketWin::OpenWordList()
{
	WWordList* a = new WWordList;
	a->show();
}

//打开群列表
void MarketWin::OpenGroupList()
{
	WGroupList* a = new WGroupList;

	a->show();
}

//打开群关键词列表
void MarketWin::OpenKeyWordGroup()
{
	WKeyWordGroup* a = new WKeyWordGroup;

	a->show();
}


//打开其他设置
void MarketWin::OpenOher()
{
	WOther* a = new WOther;
	a->show();
}

//打开系统设置
void MarketWin::OpenSystem()
{
	WSystem* a = new WSystem;
	a->show();
}

//打开邮箱测试
void MarketWin::OpenEmailTest()
{
	WEmailTest* a = new WEmailTest;
	a->show();
}

//在线更新
void MarketWin::OpenUpdata()
{
	MarketUpdate* a = new MarketUpdate;
	a->show();

}

//用户反馈
void MarketWin::OpenFeedback()
{
	WFeedback* a = new WFeedback;
	a->show();
}