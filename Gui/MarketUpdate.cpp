#include "MarketUpdate.h"

#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qmessagebox.h>
#include <qprogressdialog.h>
#include <qtconcurrentrun.h>

#include <mysql/jdbc.h>

#include <sstream>
#include <string>

#include "json.hpp"
#include "Download.hpp"

using namespace std;


#define MYSQL_ADDR "111.229.185.226"
#define MYSQL_NAME "Market"
#define MYSQL_PASSWD "28BCSeCWrsfL5LL5"

extern string version;
extern string appFile;

MarketUpdate::MarketUpdate(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//��ʼ��
	ui.button_update->setEnabled(false);
	ui.label_name->setText(QString::fromLocal8Bit("�������\t��������"));
	ui.label_localVersion->setText(QString::fromLocal8Bit(("��ǰ�汾\t" + version).c_str()));
	ui.text_updateLog->setReadOnly(true);

	//check();

	//������
	connect(ui.button_check, SIGNAL(clicked()), this, SLOT(onCheck()));

	//��װ����
	connect(ui.button_update, SIGNAL(clicked()), this, SLOT(onUpdate()));
}

MarketUpdate::~MarketUpdate()
{
}


//�������ʱ�Զ�����
void MarketUpdate::runApp()
{
	int ret = check();
	if (ret == 2)
	{
		this->show();
		QMessageBox* a = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("��Ҫ"), QString::fromLocal8Bit("����Ϊ��Ҫ���£����ڸ������Ե�"));
		a->setModal(true);
		a->show();
		update();
	}
	else if (ret == 1)
	{
		QMessageBox* a = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������� ���°汾��������������и���"));
		a->setModal(true);
		a->show();
	}
	else if (ret == 0)
	{
		//��Ҳ��֪��ɶԭ�� û�д��ڱ����Լ�ǿ�ƹر� �����һֱ�ں�̨
		exit(0);

	}
	else
	{
		QMessageBox* a = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������� ������ʱ�����쳣"));
		a->setModal(true);
		a->show();
	}

}

//������
int MarketUpdate::check()
{

	try
	{
		if (version.empty())
		{
			QMessageBox* a = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("�汾��Ϊ��"), QString::fromLocal8Bit("��ǰ�汾��Ϊ�գ����ڻ�ȡ���°汾"));
			a->show();

			//QMessageBox::information(NULL, QString::fromLocal8Bit("�汾��Ϊ��"), QString::fromLocal8Bit("��ǰ�汾��Ϊ�գ����ڻ�ȡ���°汾"), QMessageBox::Ok);
		}

		ui.button_check->setEnabled(false);
		ui.button_check->setText(QString::fromLocal8Bit("���ڼ�����"));
		ui.label_newVersion->setText(QString::fromLocal8Bit("���°汾\t���ڼ�����"));

		bool mustUpdate = false;

		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;

		/* �������� */
		driver = get_driver_instance();
		con = driver->connect(MYSQL_ADDR, MYSQL_NAME, MYSQL_PASSWD); // ��Ҫ�޸�Ϊ�����ݿ���û�����
		/* ���� MySQL ���ݿ� university  */
		con->setSchema("Market");
		stmt = con->createStatement();

		stringstream sql;

		sql << "SELECT `Version` , `Must` , `Url` , `UpdateTime` , `UpdateLog`  FROM `app` ";
		if (!version.empty())
			sql << "WHERE `Version` > '" << version << "' ";
		sql << "ORDER BY Version DESC;";


		res = stmt->executeQuery(sql.str().c_str()); // ��׼sql���

		int row = res->rowsCount();
		if (!row)
		{
			ui.button_check->setEnabled(true);
			ui.button_update->setEnabled(false);
			ui.button_check->setText(QString::fromLocal8Bit("û�и���"));
			ui.label_newVersion->setText(QString::fromLocal8Bit("���°汾\tû�и���"));
			return 0;
		}
		else
		{
			//��ȡ����
			res->next();
			m_url = QString::fromUtf8(res->getString("Url").c_str());
			mustUpdate = res->getBoolean("Must");
			QString version = QString::fromUtf8(res->getString("Version").c_str());
			QString updataTime = QString::fromUtf8(res->getString("UpdateTime").c_str());
			QString updataLog = QString::fromUtf8(res->getString("UpdateLog").c_str());

			while(res->next())
			{
				if (!mustUpdate)
					mustUpdate = res->getBoolean("Must");
			}

			//���ý���
			ui.label_newVersion->setText(QString::fromLocal8Bit("���°汾\t") + version);
			ui.label_updateTime->setText(QString::fromLocal8Bit("����ʱ��\t") + updataTime);
			ui.button_check->setText(QString::fromLocal8Bit("���������"));
			ui.text_updateLog->setText(updataLog);

			ui.button_check->setEnabled(true);
			ui.button_update->setEnabled(true);
		}


		res->close();
		con->close();
		stmt->close();
		delete res;
		delete stmt;
		delete con;


		//���Ϊ�������
		if (mustUpdate)
			return 2;
		else
			return 1;
	}
	/*catch (exception & e)`
	{
		ui.button_check->setEnabled(true);
		ui.button_check->setText(QString::fromLocal8Bit("������ʧ��"));
		ui.label_version->setText(QString::fromLocal8Bit("�汾\t������ʧ�� ") + QString::fromLocal8Bit(e.what()));
		return;
	}*/
	catch (...)
	{
		ui.button_check->setEnabled(true);
		ui.button_check->setText(QString::fromLocal8Bit("������ʧ��"));
		ui.label_newVersion->setText(QString::fromLocal8Bit("���°汾\t������ʧ��"));
		return -1;
	}
	return -1;
}

//���²��
void MarketUpdate::update()
{
	int prog_num = 0;


	//ui.progressBar = new QProgressBar;
	QProgressDialog* pd = new QProgressDialog(QString::fromLocal8Bit("���������������..."), QString::fromLocal8Bit("ȡ��"), 0, 100, this);
	//ģ̬�Ի���
	pd->setWindowModality(Qt::WindowModal);
	//������������е�ʱ��С��5���������Ͳ�����ʾ��Ĭ����4S
	pd->setMinimumDuration(5);
	//���ñ���
	pd->setWindowTitle(QString::fromLocal8Bit("���Ժ�"));

	//�رռ������Զ�����
	pd->setAutoClose(false);

	pd->setAutoReset(false);

	//��ʾ�����
	pd->show();
	bool theadOff = false;
	int ret = -1;
	string errorInf = "δ֪����";
	auto ph = new std::thread([&]()
		{
			Download a(m_url.toStdString(), "./app/cn.xiaoxiaoge.Market.cpk", "./app/cn.xiaoxiaoge.Market.tmp", prog_num);
			ret = a.start();
			errorInf = a.get_error();
		});

	int prog_num2;
	int s = 0;
	while (1)
	{
		if (prog_num2 == prog_num)
		{
			s++;
			if (s > 500)
			{
				//future.cancel();
				//delete ph;

				ret = false;
				errorInf = "���س�ʱ";
				//QMessageBox::information(NULL, QString::fromLocal8Bit("ʧ��"), QString::fromLocal8Bit("���س�ʱ"));
				break;
			}
		}
		else
		{
			s = 0;
			prog_num2 = prog_num;
		}

		QCoreApplication::processEvents();

		pd->setValue(prog_num);
		if (prog_num >= 100)
		{
			pd->setValue(100);
			break;
		}
		if (ret == false || ret == true)
			break;

		_sleep(100);
	}


	pd->close();
	delete pd;

	if (ret)
	{
		QMessageBox::about(NULL, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("��װ��ɣ���������Q�����°汾"));
	}
	else
	{
		QMessageBox::about(NULL, QString::fromLocal8Bit("ʧ��"), QString::fromLocal8Bit(("����ʧ�� ����ԭ��:" + errorInf + "\n�볢���ֶ������ڸ�����־�е���������").c_str()));
	}

#if 0
	//д�������ļ� ���߲����һ��Ϊ��һ�ο����°汾
	try
	{

		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		auto child = value.get_child_optional(L"Main");
		if (!child)
		{
			value.add_child(L"Main", boost::property_tree::wptree(L""));
		}

		value.put<bool>(L"Main.IsOne", true);
		json::write_json(appFile + "conf.json", value);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("д��json�쳣"), QMessageBox::Ok);
		return;
	}
#endif
}

//���¼����� 
void MarketUpdate::onCheck()
{
	int ret = check();
	if (ret == 2)
	{
		QMessageBox* a = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("��Ҫ"), QString::fromLocal8Bit("����Ϊ��Ҫ���£����ڸ������Ե�"));
		a->show();
		update();
	}
	else if (ret == 1)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���°汾"), QMessageBox::Ok);
	}
	else if (ret == 0)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("û�и���"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������ʱ�����쳣"), QMessageBox::Ok);
	}
}


//��װ����
void MarketUpdate::onUpdate()
{
	update();
}