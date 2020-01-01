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

//写入密钥
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
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(" 写入json异常"), QMessageBox::Ok);
		return;
	}
}

//点击激活按钮
void MarketKey::onPushButton()
{
	try
	{
		if (!ui.checkBox->isChecked())
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("必须同意用户协议才能使用"), QMessageBox::Ok);
			return;
		}

		if (ui.edit_QQId->text().isEmpty() || ui.edit_key->text().isEmpty())
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("输入有误，主人QQ 和 秘钥 不能为空"), QMessageBox::Ok);
			return;
		}

		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;

		/* 创建连接 */
		driver = get_driver_instance();
		con = driver->connect(MYSQL_ADDR, MYSQL_NAME, MYSQL_PASSWD); // 需要修改为你数据库的用户密码
		/* 连接 MySQL 数据库 university  */
		con->setSchema("Market");
		stmt = con->createStatement();

		stringstream sql;

		sql << "SELECT `Computer` FROM `key` WHERE ";
		sql << "`Key` = '" << ui.edit_key->text().toStdString();
		sql << "';";


		res = stmt->executeQuery(sql.str().c_str()); // 标准sql语句

		int row = res->rowsCount();
		string sql_Computer;
		if (row)
		{
			while (res->next())
			{
				/* 通过数字偏移量, 1 代表第一列 */
				sql_Computer = res->getString(1).c_str();
			}

			//如果为空则注册密钥
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
				QMessageBox::information(NULL, QString::fromLocal8Bit("成功"), QString::fromLocal8Bit("秘钥使用成功,请手动重启酷Q 重新验证新秘钥"), QMessageBox::Ok);
				return;
			}
			//如果不为空则验证机器码
			else
			{

				if (local_computer == sql_Computer)
				{
					//密钥正确
					writeKey();
					QMessageBox::information(NULL, QString::fromLocal8Bit("成功"), QString::fromLocal8Bit("绑定秘钥成功,请手动重启酷Q 重新验证新秘钥"), QMessageBox::Ok);
					return;
				}
				else
				{
					QMessageBox::information(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("秘钥未绑定此计算机"), QMessageBox::Ok);
					return;
				}

			}
		}
		else
		{
			//密钥无效
			QMessageBox::information(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("秘钥不存在"), QMessageBox::Ok);
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
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("验证秘钥时出现异常"), QMessageBox::Ok);
	}

}

void MarketKey::onUserAgree()
{
	WUserAgree* a = new WUserAgree;
	a->show();
}