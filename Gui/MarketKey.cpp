#include "MarketKey.h"
#include "WUserAgree.h"

#include "json.hpp"

#include <sstream>
#include <string>

#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qmessagebox.h>

#include <mysql/jdbc.h>

using namespace std;

#define MYSQL_ADDR "111.229.185.226"
#define MYSQL_NAME "Market"
#define MYSQL_PASSWD "28BCSeCWrsfL5LL5"

extern string local_computer;
extern string appFile;
extern string key;

MarketKey::MarketKey(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.edit_key->setText(QString::fromLocal8Bit(key.c_str()));

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(onPushButton()));
	connect(ui.button_userAgree, SIGNAL(clicked()), this, SLOT(onUserAgree()));
}

MarketKey::~MarketKey()
{
}

//д����Կ
void MarketKey::writeKey()
{
	try
	{
		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);


		value.put<wstring>(L"Main.Key", ui.edit_key->text().toStdWString());

		json::write_json(appFile + "conf.json", value);

		Conf::makeUpdate();

	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(" д��json�쳣"), QMessageBox::Ok);
		return;
	}
}

//������ť
void MarketKey::onPushButton()
{
	try
	{
		if (!ui.checkBox->isChecked())
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ͬ���û�Э�����ʹ��"), QMessageBox::Ok);
			return;
		}

		if (ui.edit_QQId->text().isEmpty() || ui.edit_key->text().isEmpty())
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������������QQ �� ��Կ ����Ϊ��"), QMessageBox::Ok);
			return;
		}

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

		sql << "SELECT `Computer` FROM `key` WHERE ";
		sql << "`Key` = '" << ui.edit_key->text().toStdString();
		sql << "';";


		res = stmt->executeQuery(sql.str().c_str()); // ��׼sql���

		int row = res->rowsCount();
		string sql_Computer;
		if (row)
		{
			while (res->next())
			{
				/* ͨ������ƫ����, 1 �����һ�� */
				sql_Computer = res->getString(1).c_str();
			}

			//���Ϊ����ע����Կ
			if (sql_Computer.empty())
			{
				stringstream sql;

				sql << "UPDATE `Market`.`key` SET ";
				sql << "`Computer` = '" << local_computer << "', ";
				sql << "`LoginDateTime` = NOW(), ";
				sql << "`UsingDateTime` = NOW(), ";
				sql << "`QQId` = '" << ui.edit_QQId->text().toStdString() << "' ";
				sql << "WHERE `Key` = '" << ui.edit_key->text().toStdString() << "';";

				stmt->executeUpdate(sql.str().c_str());

				writeKey();
				QMessageBox::information(NULL, QString::fromLocal8Bit("�ɹ�"), QString::fromLocal8Bit("��Կʹ�óɹ�,���ֶ�������Q ������֤����Կ"), QMessageBox::Ok);
				return;
			}
			//�����Ϊ������֤������
			else
			{

				if (local_computer == sql_Computer)
				{
					//��Կ��ȷ
					writeKey();
					QMessageBox::information(NULL, QString::fromLocal8Bit("�ɹ�"), QString::fromLocal8Bit("����Կ�ɹ�,���ֶ�������Q ������֤����Կ"), QMessageBox::Ok);
					return;
				}
				else
				{
					QMessageBox::information(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��Կδ�󶨴˼����"), QMessageBox::Ok);
					return;
				}

			}
		}
		else
		{
			//��Կ��Ч
			QMessageBox::information(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��Կ������"), QMessageBox::Ok);
			return;
		}

		res->close();
		con->close();
		stmt->close();
		delete res;
		delete stmt;
		delete con;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��֤��Կʱ�����쳣"), QMessageBox::Ok);
	}

}

void MarketKey::onUserAgree()
{
	WUserAgree* a = new WUserAgree;
	a->show();
}