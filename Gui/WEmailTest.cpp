#include "WEmailTest.h"
#include <qmessagebox.h>
#include <qclipboard.h>
#include <qtconcurrentrun.h>

#include <email/phpSendEmail.hpp>
#include "json.hpp"

using namespace std;

extern string appFile;

OTHER_CONF otherCfg;

string phpPath(".\\PHPRun");
string phpFile(".\\PHPRun\\Core\\php.exe");
string sendFile(".\\PHPRun\\Send.php");
string verifyFile(".\\PHPRun\\Verify.php");

WEmailTest::WEmailTest(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//创建
	m_model = new QStandardItemModel;

	readLastWrod();
	read_emailList();
	read_wordList();

	////设置只能输入数字
	//QValidator* validator = new QIntValidator(0, 999999999999, this);
	//ui.edit_verifyEmail->setValidator(validator);

	connect(ui.button_test, SIGNAL(clicked()), this, SLOT(onTest()));
	connect(ui.button_verify, SIGNAL(clicked()), this, SLOT(onVerify()));
	connect(ui.tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
	connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(slotRowDoubleClicked(const QModelIndex&)));
}

WEmailTest::~WEmailTest()
{
}

//关闭事件
void WEmailTest::closeEvent(QCloseEvent* event)
{

	saveLastWrod();

}

//保存上次输入的内容
void WEmailTest::saveLastWrod()
{
	try
	{
		boost::property_tree::wptree value;
		read_json(appFile + "conf.json", value);

		//检测是否存在 不存在则创建一个
		auto child = value.get_child_optional(L"Win");
		if (!child)
		{
			value.add_child(L"Win", boost::property_tree::wptree(L""));
			child = value.get_child_optional(L"Win");
		}

		wstring test = ui.edit_putEmail->text().toStdWString();
		wstring verify = ui.edit_verifyEmail->text().toStdWString();

		child.value().put<wstring>(L"WEmailTest_LastGetEmail", test);
		child.value().put<wstring>(L"WEmailTest_LastVerify", verify);

		json::write_json(appFile + "conf.json", value);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit((string("WEmailTest保存上次输入的内容 ") + e.what()).c_str()), QMessageBox::Ok);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("写入json异常--WEmailTest保存上次输入的内容"), QMessageBox::Ok);
		return;
	}
}

//读取上输入的内容
void WEmailTest::readLastWrod()
{
	try
	{
		boost::property_tree::wptree value;

		read_json(appFile + "conf.json", value);

		QString temp_lastGetEmail = QString::fromStdWString(value.get<wstring>(L"Win.WEmailTest_LastGetEmail", L""));
		QString temp_lastVerify = QString::fromStdWString(value.get<wstring>(L"Win.WEmailTest_LastVerify", L""));

		ui.edit_putEmail->setText(temp_lastGetEmail);
		ui.edit_verifyEmail->setText(temp_lastVerify);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit((string("WEmailTest保存上次输入的内容 ") + e.what()).c_str()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("读取json异常--WEmailTest读取上次输入的内容"), QMessageBox::Ok);
		return;
	}
}


//获取其他设置
bool WEmailTest::get_otherConf()
{
	try
	{
		boost::property_tree::wptree value;

		read_json(appFile + "conf.json", value);
		otherCfg.useHtml = value.get<bool>(L"Main.UseHtml", false);

		otherCfg.verifyEmail = OperateStr::wstring2string(value.get<wstring>(L"Main.VerifyEmail", L""));
		otherCfg.verifyPasswd = OperateStr::wstring2string(value.get<wstring>(L"Main.VerifyPasswd", L""));

	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return false;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("读取json异常"), QMessageBox::Ok);
		return false;
	}

	return true;
}

//读取邮箱列表
bool WEmailTest::read_emailList()
{
	try
	{
		//清空原数据
		m_model->clear();

		//设置列头
		m_model->setColumnCount(7);
		m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("#"));
		m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("邮箱"));
		m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("状态"));
		m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("密码"));
		m_model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("SMTP"));
		m_model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("端口"));
		m_model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("SSL"));

		//设置列宽
		ui.tableView->setModel(m_model);
		ui.tableView->setColumnWidth(0, 30);
		ui.tableView->setColumnWidth(1, 170);
		ui.tableView->setColumnWidth(2, 200);
		ui.tableView->setColumnWidth(3, 150);
		ui.tableView->setColumnWidth(4, 140);
		ui.tableView->setColumnWidth(5, 40);
		ui.tableView->setColumnWidth(6, 40);

		//ui.tableView->resizeRowsToContents();//自适应多行文本
		ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);//自适应单元格长度

		//设置样式
		ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//检测是否有这个子
		auto child_test = value.get_child_optional(L"SmtpList");

		if (!child_test)
		{
			value.add_child(L"SmtpList", boost::property_tree::wptree(L""));
		}

		boost::property_tree::wptree child = value.get_child(L"SmtpList");

		for (auto temp : child)
		{
			//获取数据
			QString temp_smtp(QString::fromStdWString(temp.second.get<std::wstring>(L"Smtp").c_str()));
			QString temp_email(QString::fromStdWString(temp.second.get<std::wstring>(L"Email").c_str()));
			QString temp_passwd(QString::fromStdWString(temp.second.get<std::wstring>(L"Passwd").c_str()));

			QString temp_port(QString::fromStdWString(to_wstring(temp.second.get<int>(L"Port")).c_str()));

			bool temp_ssl = temp.second.get<bool>(L"SSL");

			auto p = new QStandardItem();


			int m_modelIndex = m_model->rowCount();

			p->setEditable(false);
			p->setCheckState(Qt::Unchecked);
			m_model->setItem(m_modelIndex, 0, p);


			m_model->setItem(m_modelIndex, 1, new QStandardItem(temp_email));
			m_model->setItem(m_modelIndex, 2, new QStandardItem());
			m_model->setItem(m_modelIndex, 3, new QStandardItem(temp_passwd));
			m_model->setItem(m_modelIndex, 4, new QStandardItem(temp_smtp));
			m_model->setItem(m_modelIndex, 5, new QStandardItem(temp_port));

			if (temp_ssl)
				m_model->setItem(m_modelIndex, 6, new QStandardItem(QString::fromLocal8Bit("√")));
			else
				m_model->setItem(m_modelIndex, 6, new QStandardItem(""));

		}

	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return false;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("读取json异常"), QMessageBox::Ok);
		return false;
	}

	return true;
}

//读取内容列表
bool WEmailTest::read_wordList()
{
	try
	{
		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//检测是否有这个子
		auto child_test = value.get_child_optional(L"WordList");

		if (!child_test)
		{
			value.add_child(L"WordList", boost::property_tree::wptree(L""));
		}

		boost::property_tree::wptree child = value.get_child(L"WordList");

		for (auto temp : child)
		{
			QString title_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Title").c_str()));

			ui.combo_word->addItem(title_temp);
		}

	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		return false;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("读取json异常"), QMessageBox::Ok);
		return false;
	}

	return true;
}

//点击开始发送按钮后
void WEmailTest::onTest()
{
	ui.button_test->setText(QString::fromLocal8Bit("正在测试中..."));
	ui.button_test->setEnabled(false);
	ui.button_test->update();

	//QFuture < void > future = QtConcurrent::run([&]() {
	try
	{
		string name;
		string title;
		string word;
		string putEmail;
		//string file;

		//读取其他配置
		get_otherConf();

		//接受消息的邮箱
		putEmail = ui.edit_putEmail->text().toStdString();

		//获取发送内容
		if (!get_word(ui.combo_word->currentIndex() + 1, name, title, word))
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("获取发送内容失败"), QMessageBox::Ok);
			ui.button_test->setText(QString::fromLocal8Bit("测试错误"));
			ui.button_test->setEnabled(true);
			return;
		}

		MsgValue(word);
		MsgValue(title);
		MsgValue(name);

		for (int i = 0; i < m_model->rowCount(); i++)
		{
			if (m_model->item(i)->checkState() == Qt::Checked)
			{
				m_model->itemFromIndex(m_model->index(i, 2))->setText(QString::fromLocal8Bit("准备发送"));
			}
		}

		ui.tableView->resizeRowsToContents();//自适应多行文本

		//开始遍历邮箱列表
		for (int i = 0; i < m_model->rowCount(); i++)
		{
			QCoreApplication::processEvents();

			if (m_model->item(i)->checkState() == Qt::Checked)
			{
				m_model->itemFromIndex(m_model->index(i, 2))->setText(QString::fromLocal8Bit("正在发送"));
				ui.tableView->update(m_model->index(i, 2));


				string emailText = m_model->item(i, 1)->text().toLocal8Bit();
				string passwd = m_model->item(i, 3)->text().toLocal8Bit();
				string smtp = m_model->item(i, 4)->text().toLocal8Bit();
				string port = m_model->item(i, 5)->text().toLocal8Bit();
				bool ssl = !(m_model->item(i, 6)->text().isEmpty());

				phpSendEmail email(
					phpPath,
					phpFile,
					sendFile,
					smtp,
					ssl,
					port,
					emailText,
					passwd,
					putEmail,
					name,
					title,
					word
				);

				/*设置格式*/

				//设置html格式
				email.setIsHtml(otherCfg.useHtml);


				QCoreApplication::processEvents();
				bool ret = email.send();
				QCoreApplication::processEvents();

				if (ret)
				{
					//string error = email.getInf();
					//m_model->itemFromIndex(m_model->index(i, 2))->setText(QString::fromLocal8Bit("发送成功 返回信息:") + QString::fromLocal8Bit(error.c_str()));
					m_model->itemFromIndex(m_model->index(i, 2))->setText(QString::fromLocal8Bit("发送成功"));
					ui.tableView->update(m_model->index(i, 2));
				}
				else
				{
					string error = email.getInf();

					if (error.empty())
					{
						error = "未知原因";
					}

					//修改提示内容
					m_model->itemFromIndex(m_model->index(i, 2))->setText(QString::fromLocal8Bit("发送失败 错误信息:") + QString::fromLocal8Bit(error.c_str()));
					ui.tableView->update(m_model->index(i, 2));
				}

			}
			ui.tableView->resizeRowsToContents();//自适应多行文本
		}
		ui.button_test->setText(QString::fromLocal8Bit("测试完成"));
		ui.button_test->setEnabled(true);

	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		ui.button_test->setText(QString::fromLocal8Bit("测试错误"));
		ui.button_test->setEnabled(true);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("读取json异常"), QMessageBox::Ok);

		ui.button_test->setText(QString::fromLocal8Bit("测试错误"));
		ui.button_test->setEnabled(true);
		return;
	}
	//});
}

//获取内容
bool WEmailTest::get_word(int id, string& name, string& title, string& word)
{

	try
	{
		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//检测是否有这个子
		auto child_test = value.get_child_optional(L"WordList");

		if (!child_test)
		{
			value.add_child(L"WordList", boost::property_tree::wptree(L""));
		}

		boost::property_tree::wptree child = value.get_child(L"WordList");

		for (auto temp : child)
		{
			//获取数据
			QString id_temp(QString::fromStdWString(temp.first.c_str()));

			if (id_temp.toInt() == id)
			{
				string name_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Name")).toLocal8Bit());
				string title_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Title")).toLocal8Bit());
				string word_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Word")).toLocal8Bit());
				//string file_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"File")).toLocal8Bit());

				name = name_temp;
				title = title_temp;
				word = word_temp;

				/*	for (auto one : word_temp)
					{
						if (one == '\n')
						{
							word += "\r\n";
						}
						else
						{
							word += one;
						}
					}*/


					//file = file_temp;

				return true;
			}

		}

	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		return false;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("读取json异常"), QMessageBox::Ok);
		return false;
	}


	return false;
}

//点击列表复选框事件
void WEmailTest::onTableClicked(const QModelIndex& m)
{
	if (m.column() == 0)
	{
		auto t = m_model->item(m.row())->checkState();
		m_model->item(m.row())->setCheckState((t == Qt::Checked) ? Qt::Unchecked : Qt::Checked);
	}
}

//验证QQ是否开通邮箱
void WEmailTest::onVerify()
{
	//获取其他设置
	get_otherConf();

	if (otherCfg.verifyEmail.empty())
	{
		QMessageBox::information(NULL, "未设置", "验证邮箱未设置，请在系统设置中设置验证邮箱");
		return;
	}

	ui.button_verify->setText(QString::fromLocal8Bit("正在验证中..."));
	ui.button_verify->setEnabled(false);

	//QFuture < void > future = QtConcurrent::run([&]() {

	phpSendEmail email(phpPath, phpFile, verifyFile, otherCfg.verifyEmail, otherCfg.verifyPasswd, ui.edit_verifyEmail->text().toStdString() + "@qq.com");

	QCoreApplication::processEvents();
	int ret = email.verify();
	QCoreApplication::processEvents();
	if (ret)
	{
		QMessageBox* box = new QMessageBox(
			QMessageBox::Information,
			QString::fromLocal8Bit("已开通"),
			QString::fromLocal8Bit(("对方已开通邮箱 返回信息:" + email.getInf()).c_str()),
			QMessageBox::Ok);
		box->show();
		ui.button_verify->setText(QString::fromLocal8Bit("此邮箱已开通"));
	}
	else
	{
		QMessageBox* box = new QMessageBox(
			QMessageBox::Information,
			QString::fromLocal8Bit("未开通"),
			QString::fromLocal8Bit(("对方未开通邮箱 返回信息:" + email.getInf()).c_str()),
			QMessageBox::Ok);
		box->show();
		ui.button_verify->setText(QString::fromLocal8Bit("此邮箱未开通"));
	}

	ui.button_verify->setEnabled(true);
	//		});


}

//双击事件
void WEmailTest::slotRowDoubleClicked(const QModelIndex& w)
{
	QString buf = w.data().toString();

	//复制到剪切板
	QClipboard* board = QApplication::clipboard();
	board->setText(buf);

	//提示内容
	ui.label_state->clear();
	ui.label_state->setText(QString::fromLocal8Bit("(已复制到剪切板)"));

	//定时清除提示内容
	QFuture < void > future = QtConcurrent::run([&]()
		{
			Sleep(5000);
			ui.label_state->clear();
			ui.label_state->setText(QString::fromLocal8Bit("(双击复制)"));
		}
	);

}


//消息变量
void WEmailTest::MsgValue(string& str)
{
	//获取当前时间
	SYSTEMTIME sys;
	GetLocalTime(&sys);

	char date[20];
	char time[20];
	char Week[20];

	sprintf(date, "%4d年%02d月%02d日", sys.wYear, sys.wMonth, sys.wDay);
	sprintf(time, "%02d:%02d:%02d.%03d", sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	sprintf(Week, "星期%d", sys.wDayOfWeek);

	//日期
	replace_all_distinct(str, "{日期}", date);

	//时间
	replace_all_distinct(str, "{时间}", time);

	//星期
	replace_all_distinct(str, "{星期}", Week);

	//触发的QQ号码
	replace_all_distinct(str, "{QQ号码}", to_string(12345678));

	//群号码
	replace_all_distinct(str, "{群号码}", to_string(87654321));

	//触发的QQ名称
	replace_all_distinct(str, "{QQ名称}", "昵称");

	//触发的QQ名片
	//replace_all_distinct(str, "{群名片}", "名片");

	//触发的群名称
	replace_all_distinct(str, "{群名称}", "群名称");


	//地区
	//replace_all_distinct(str, "{地区}", "北京");


	replace_all_distinct(str, "{性别}", "男");

	//年龄
	replace_all_distinct(str, "{年龄}", "18");

	//随机数变量
	replace_all_random(str);


}

//字符串替换
void WEmailTest::replace_all_distinct(string& str, string old_value, string new_value)
{
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length())
	{
		if ((pos = str.find(old_value, pos)) != string::npos)
		{
			str.replace(pos, old_value.length(), new_value);
		}
		else { break; }
	}
	//return str;
}

//字符串替换
void WEmailTest::replace_all_random(string& str)
{
	srand(time(NULL));
	//随机数字
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{随机数字}", pos)) != string::npos)
		{
			//随机数字
			char num = rand() % 10 + 48;
			str.replace(pos, string("{随机数字}").length(), string(1, num));
		}
		else { break; }
	}

	//随机符号
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{随机符号}", pos)) != string::npos)
		{	//随机符号
			char symbol = rand() % 32 + 1;
			if (symbol <= 15)
			{
				symbol = 15 - symbol;
				symbol += 33;
			}
			else if (symbol <= 22)
			{
				symbol = 22 - symbol;
				symbol += 58;
			}
			else if (symbol <= 28)
			{
				symbol = 28 - symbol;
				symbol += 91;
			}
			else if (symbol <= 32)
			{
				symbol = 32 - symbol;
				symbol += 123;
			}
			else
			{
				symbol = '!';
			}
			str.replace(pos, string("{随机符号}").length(), string(1, symbol));
		}
		else { break; }
	}

	//随机大写字母
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{随机大写字母}", pos)) != string::npos)
		{
			//随机大写字母
			char capital = rand() % 26 + 65;
			str.replace(pos, string("{随机大写字母}").length(), string(1, capital));
		}
		else { break; }
	}

	//随机小写字母
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{随机小写字母}", pos)) != string::npos)
		{
			//随机小写字母
			char lowercase = rand() % 26 + 97;
			str.replace(pos, string("{随机小写字母}").length(), string(1, lowercase));
		}
		else { break; }
	}



	//return str;
}
