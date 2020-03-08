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

	//初始化
	ui.button_update->setEnabled(false);
	ui.label_name->setText(QString::fromLocal8Bit("软件名称\t懒人引流"));
	ui.label_localVersion->setText(QString::fromLocal8Bit(("当前版本\t" + version).c_str()));
	ui.text_updateLog->setReadOnly(true);

	//check();

	//检查更新
	connect(ui.button_check, SIGNAL(clicked()), this, SLOT(onCheck()));

	//安装更新
	connect(ui.button_update, SIGNAL(clicked()), this, SLOT(onUpdate()));
}

MarketUpdate::~MarketUpdate()
{
}


//插件开启时自动更新
void MarketUpdate::runApp()
{
	int ret = check();
	if (ret == 2)
	{
		this->show();
		QMessageBox* a = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("重要"), QString::fromLocal8Bit("本次为重要更新，正在更新请稍等"));
		a->setModal(true);
		a->show();
		update();
	}
	else if (ret == 1)
	{
		QMessageBox* a = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("更新"), QString::fromLocal8Bit("懒人引流 有新版本，请在软件设置中更新"));
		a->setModal(true);
		a->show();
	}
	else if (ret == 0)
	{
		//我也不知道啥原因 没有窗口必须自己强制关闭 否则会一直在后台
		exit(0);

	}
	else
	{
		QMessageBox* a = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("懒人引流 检查更新时出现异常"));
		a->setModal(true);
		a->show();
	}

}

//检查更新
int MarketUpdate::check()
{

	try
	{
		if (version.empty())
		{
			QMessageBox* a = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("版本号为空"), QString::fromLocal8Bit("当前版本号为空，正在获取最新版本"));
			a->show();

			//QMessageBox::information(NULL, QString::fromLocal8Bit("版本号为空"), QString::fromLocal8Bit("当前版本号为空，正在获取最新版本"), QMessageBox::Ok);
		}

		ui.button_check->setEnabled(false);
		ui.button_check->setText(QString::fromLocal8Bit("正在检查更新"));
		ui.label_newVersion->setText(QString::fromLocal8Bit("最新版本\t正在检查更新"));

		bool mustUpdate = false;

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

		sql << "SELECT `Version` , `Must` , `Url` , `UpdateTime` , `UpdateLog`  FROM `app` ";
		if (!version.empty())
			sql << "WHERE `Version` > '" << version << "' ";
		sql << "ORDER BY Version DESC;";


		res = stmt->executeQuery(sql.str().c_str()); // 标准sql语句

		int row = res->rowsCount();
		if (!row)
		{
			ui.button_check->setEnabled(true);
			ui.button_update->setEnabled(false);
			ui.button_check->setText(QString::fromLocal8Bit("没有更新"));
			ui.label_newVersion->setText(QString::fromLocal8Bit("最新版本\t没有更新"));
			return 0;
		}
		else
		{
			//获取内容
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

			//设置界面
			ui.label_newVersion->setText(QString::fromLocal8Bit("最新版本\t") + version);
			ui.label_updateTime->setText(QString::fromLocal8Bit("更新时间\t") + updataTime);
			ui.button_check->setText(QString::fromLocal8Bit("检查更新完成"));
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


		//如果为必须更新
		if (mustUpdate)
			return 2;
		else
			return 1;
	}
	/*catch (exception & e)`
	{
		ui.button_check->setEnabled(true);
		ui.button_check->setText(QString::fromLocal8Bit("检查更新失败"));
		ui.label_version->setText(QString::fromLocal8Bit("版本\t检查更新失败 ") + QString::fromLocal8Bit(e.what()));
		return;
	}*/
	catch (...)
	{
		ui.button_check->setEnabled(true);
		ui.button_check->setText(QString::fromLocal8Bit("检查更新失败"));
		ui.label_newVersion->setText(QString::fromLocal8Bit("更新版本\t检查更新失败"));
		return -1;
	}
	return -1;
}

//更新插件
void MarketUpdate::update()
{
	int prog_num = 0;


	//ui.progressBar = new QProgressBar;
	QProgressDialog* pd = new QProgressDialog(QString::fromLocal8Bit("正在下载最新组件..."), QString::fromLocal8Bit("取消"), 0, 100, this);
	//模态对话框
	pd->setWindowModality(Qt::WindowModal);
	//如果进度条运行的时间小于5，进度条就不会显示，默认是4S
	pd->setMinimumDuration(5);
	//设置标题
	pd->setWindowTitle(QString::fromLocal8Bit("请稍后"));

	//关闭加载完自动隐藏
	pd->setAutoClose(false);

	pd->setAutoReset(false);

	//显示处理框
	pd->show();
	bool theadOff = false;
	int ret = -1;
	string errorInf = "未知错误";
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
				errorInf = "下载超时";
				//QMessageBox::information(NULL, QString::fromLocal8Bit("失败"), QString::fromLocal8Bit("下载超时"));
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
		QMessageBox::about(NULL, QString::fromLocal8Bit("完成"), QString::fromLocal8Bit("安装完成，请重启酷Q载入新版本"));
	}
	else
	{
		QMessageBox::about(NULL, QString::fromLocal8Bit("失败"), QString::fromLocal8Bit(("下载失败 错误原因:" + errorInf + "\n请尝试手动下载在更新日志中的下载链接").c_str()));
	}

#if 0
	//写入配置文件 告诉插件下一次为第一次开启新版本
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
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("写入json异常"), QMessageBox::Ok);
		return;
	}
#endif
}

//按下检查更新 
void MarketUpdate::onCheck()
{
	int ret = check();
	if (ret == 2)
	{
		QMessageBox* a = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("重要"), QString::fromLocal8Bit("本次为重要更新，正在更新请稍等"));
		a->show();
		update();
	}
	else if (ret == 1)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("更新"), QString::fromLocal8Bit("有新版本"), QMessageBox::Ok);
	}
	else if (ret == 0)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("更新"), QString::fromLocal8Bit("没有更新"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("检查更新时出现异常"), QMessageBox::Ok);
	}
}


//安装更新
void MarketUpdate::onUpdate()
{
	update();
}