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

	//��ȡ����
	read_data();

	//�����ϵ��ʽ
	ui.combo_contact->addItem(QString::fromLocal8Bit("QQ"));
	ui.combo_contact->addItem(QString::fromLocal8Bit("΢��"));
	ui.combo_contact->addItem(QString::fromLocal8Bit("����"));
	ui.combo_contact->addItem(QString::fromLocal8Bit("�ֻ���"));

	connect(ui.button_send, SIGNAL(clicked()), this, SLOT(buttonSend()));
}

WFeedback::~WFeedback()
{
}

//��ȡ����
bool WFeedback::read_data()
{
	try
	{
		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//����Ƿ��������
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
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return false;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡjson�쳣"), QMessageBox::Ok);
		return false;
	}

	return true;
}


//���������ť��
void WFeedback::buttonSend()
{

	if (ui.edit_title->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������ⲻ��Ϊ��"), QMessageBox::Ok);
		return;
	}
	else if (ui.text_word->toPlainText().isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������ݲ���Ϊ��"), QMessageBox::Ok);
		return;
	}


	ui.button_send->setEnabled(false);
	ui.button_send->setText(QString::fromLocal8Bit("�����ύ,���Ժ�"));
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
				QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡsmtp����ʧ��"), QMessageBox::Ok);

				ui.button_send->setEnabled(true);
				ui.button_send->setText(QString::fromLocal8Bit("�ύʧ��"));
				return;
			}

			//Csmtp a(
			//	port,
			//	smtp.toStdString(),
			//	email.toStdString(),// ��Դ����
			//	passwd.toStdString(),   //����
			//	"����"//��������
			//);

			string title = ui.edit_title->text().toLocal8Bit();
			string word;

			word += "��ϵ��ʽ: ";
			word += ui.combo_contact->currentText().toLocal8Bit();
			word += " ";
			word += ui.edit_contact->text().toLocal8Bit();
			word += " ��������: ";
			word += ui.combo_smtp->currentText().toLocal8Bit();
			word += "\r\n\r\n����:";
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
				"����",
				title,
				word
			);

			if (a.send() == false)
			{
				throw exception(a.getInf().c_str());
			}

			QMessageBox::information(NULL, QString::fromLocal8Bit("лл"), QString::fromLocal8Bit("�����ɹ������ķ������������Ķ�����лл��"), QMessageBox::Ok);
			ui.button_send->setEnabled(true);
			ui.button_send->setText(QString::fromLocal8Bit("�ύ�ɹ�"));
		}
		catch (exception & e)
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("����ʧ��"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
			ui.button_send->setEnabled(true);
			ui.button_send->setText(QString::fromLocal8Bit("�ύʧ��"));
		}
		catch (...)
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("����ʧ��"), QString::fromLocal8Bit("δ֪�쳣"), QMessageBox::Ok);
			ui.button_send->setEnabled(true);
			ui.button_send->setText(QString::fromLocal8Bit("�ύʧ��"));
		}
		}
	);
}


//��ȡ����
bool WFeedback::get_email(QString& emailStr, QString& passwd, QString& smtp, int& port, bool& ssl)
{
	try
	{
		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//����Ƿ��������
		auto child_test = value.get_child_optional(L"SmtpList");

		if (!child_test)
		{
			value.add_child(L"SmtpList", boost::property_tree::wptree(L""));
		}

		boost::property_tree::wptree child = value.get_child(L"SmtpList");

		for (auto temp : child)
		{
			//��ȡ����
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
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return false;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡjson�쳣"), QMessageBox::Ok);
		return false;
	}

	return false;
}