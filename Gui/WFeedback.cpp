#include "WFeedback.h"

#include <qmessagebox.h>
#include <qtconcurrentrun.h>

#include <email/phpSendEmail.hpp>
#include "json.hpp"

extern string appFile;


extern string phpPath;
extern string phpFile;
extern string sendFile;


WFeedback::WFeedback(QWidget* parent)
	: QWidget(parent)
{

	ui.setupUi(this);

	//读取数据
	read_data();

	//添加联系方式
	ui.combo_contact->addItem(QString::fromLocal8Bit("QQ"));
	ui.combo_contact->addItem(QString::fromLocal8Bit("微信"));
	ui.combo_contact->addItem(QString::fromLocal8Bit("邮箱"));
	ui.combo_contact->addItem(QString::fromLocal8Bit("手机号"));

	connect(ui.button_send, SIGNAL(clicked()), this, SLOT(buttonSend()));
}

WFeedback::~WFeedback()
{
}

//读取数据
bool WFeedback::read_data()
{
	try
	{
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
			QString email_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Email").c_str()));

			ui.combo_smtp->addItem(email_temp);
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


//点击反馈按钮后
void WFeedback::buttonSend()
{

	if (ui.edit_title->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("邮箱标题不能为空"), QMessageBox::Ok);
		return;
	}
	else if (ui.text_word->toPlainText().isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("邮箱内容不能为空"), QMessageBox::Ok);
		return;
	}


	ui.button_send->setEnabled(false);
	ui.button_send->setText(QString::fromLocal8Bit("正在提交,请稍候"));
	ui.button_send->update();

	QFuture <void> future = QtConcurrent::run([&]() {
		try
		{
			QString email = ui.combo_smtp->currentText();
			QString passwd;
			QString smtp;
			int port;
			bool ssl;

			if (get_email(email, passwd, smtp, port, ssl) == false)
			{
				QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("获取smtp数据失败"), QMessageBox::Ok);

				ui.button_send->setEnabled(true);
				ui.button_send->setText(QString::fromLocal8Bit("提交失败"));
				return;
			}

			//Csmtp a(
			//	port,
			//	smtp.toStdString(),
			//	email.toStdString(),// 来源邮箱
			//	passwd.toStdString(),   //密码
			//	"反馈"//发送名称
			//);

			string title = ui.edit_title->text().toLocal8Bit();
			string word;

			word += "联系方式: ";
			word += ui.combo_contact->currentText().toLocal8Bit();
			word += " ";
			word += ui.edit_contact->text().toLocal8Bit();
			word += " 发送邮箱: ";
			word += ui.combo_smtp->currentText().toLocal8Bit();
			word += "\r\n\r\n内容:";
			word += ui.text_word->toPlainText().toLocal8Bit();

			phpSendEmail a(
				phpPath,
				phpFile,
				sendFile,
				smtp.toStdString(),
				ssl,
				to_string(port),
				email.toStdString(),
				passwd.toStdString(),
				"1164442003@qq.com",
				"反顾",
				title,
				word
			);

			if (a.send() == false)
			{
				throw exception(a.getInf().c_str());
			}

			QMessageBox::information(NULL, QString::fromLocal8Bit("谢谢"), QString::fromLocal8Bit("反馈成功，您的反馈是我们最大的动力，谢谢您"), QMessageBox::Ok);
			ui.button_send->setEnabled(true);
			ui.button_send->setText(QString::fromLocal8Bit("提交成功"));
		}
		catch (exception & e)
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("反馈失败"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
			ui.button_send->setEnabled(true);
			ui.button_send->setText(QString::fromLocal8Bit("提交失败"));
		}
		catch (...)
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("反馈失败"), QString::fromLocal8Bit("未知异常"), QMessageBox::Ok);
			ui.button_send->setEnabled(true);
			ui.button_send->setText(QString::fromLocal8Bit("提交失败"));
		}
		}
	);
}


//获取邮箱
bool WFeedback::get_email(QString& emailStr, QString& passwd, QString& smtp, int& port, bool& ssl)
{
	try
	{
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
			QString email_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Email").c_str()));

			if (emailStr == email_temp)
			{
				QString smtp_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Smtp").c_str()));
				QString passwd_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Passwd").c_str()));

				QString port_temp(QString::fromStdWString(to_wstring(temp.second.get<int>(L"Port")).c_str()));

				ssl = temp.second.get<int>(L"SSL", false);

				passwd = passwd_temp;
				smtp = smtp_temp;
				port = port_temp.toInt();

				return true;
			}
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

	return false;
}