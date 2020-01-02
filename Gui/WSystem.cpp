#include "WSystem.h"

#include "json.hpp"

#include <qmessagebox.h>

#include <string>

using namespace std;

extern string local_computer;
extern string key;
extern string exceedDateTime;
extern string appFile;


WSystem::WSystem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	init();
	readConf();

	connect(ui.button_save, SIGNAL(clicked()), this, SLOT(onSave()));
}

WSystem::~WSystem()
{
}


void WSystem::init()
{
	//������ʽ
	ui.edit_ComputerId->setReadOnly(true);
	ui.edit_key->setReadOnly(true);
	ui.edit_exceedDateTime->setReadOnly(true);

	ui.edit_ComputerId->setText(QString::fromLocal8Bit(local_computer.c_str()));
	ui.edit_key->setText(QString::fromLocal8Bit(key.c_str()));
	ui.edit_exceedDateTime->setText(QString::fromLocal8Bit(exceedDateTime.c_str()));
}

bool WSystem::readConf()
{
	try
	{
		boost::property_tree::wptree value;

		read_json(appFile + "conf.json", value);

		QString temp_verifyEmail = QString::fromStdWString(value.get<wstring>(L"Main.VerifyEmail", L""));
		QString temp_verifyPasswd = QString::fromStdWString(value.get<wstring>(L"Main.VerifyPasswd", L""));

		QString temp_smtpSleep = QString::fromLocal8Bit(to_string(value.get<int>(L"Main.SmtpSleep", 0)).c_str());
		QString temp_oneQQDayMax = QString::fromLocal8Bit(to_string(value.get<int>(L"Main.OneQQDayMax", 0)).c_str());
		QString temp_oneQQSleep = QString::fromLocal8Bit(to_string(value.get<int>(L"Main.OneQQSleep", 0)).c_str());

		QString temp_oneGroupEmail = QString::fromLocal8Bit(to_string(value.get<int>(L"Main.OneGroupEmail", 0)).c_str());
		QString temp_oneGroupTime = QString::fromLocal8Bit(to_string(value.get<int>(L"Main.OneGroupTime", 0)).c_str());

		QString temp_keyWordMsgSize = QString::fromLocal8Bit(to_string(value.get<int>(L"Main.KeyWordMsgSize", 0)).c_str());


		ui.edit_keyWordMsgSize->setText(temp_keyWordMsgSize);

		ui.edit_oneGroupEmail->setText(temp_oneGroupEmail);
		ui.edit_oneGroupTime->setText(temp_oneGroupTime);
		
		ui.edit_verifyEmail->setText(temp_verifyEmail);
		ui.edit_verifyPasswd->setText(temp_verifyPasswd);

		ui.edit_smtpSleep->setText(temp_smtpSleep);
		ui.edit_oneQQDayMax->setText(temp_oneQQDayMax);
		ui.edit_oneQQSleep->setText(temp_oneQQSleep);
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

bool WSystem::writeConf()
{
	try
	{
		boost::property_tree::wptree value;
		read_json(appFile + "conf.json", value);

		//����Ƿ���� �������򴴽�һ��
		auto child = value.get_child_optional(L"Main");
		if (!child)
		{
			value.add_child(L"Main", boost::property_tree::wptree(L""));
			child = value.get_child_optional(L"Main");
		}

		child.value().put<int>(L"SmtpSleep", ui.edit_smtpSleep->text().toInt());
		child.value().put<int>(L"OneQQDayMax", ui.edit_oneQQDayMax->text().toInt());
		child.value().put<int>(L"OneQQSleep", ui.edit_oneQQSleep->text().toInt());
		
		
		child.value().put<wstring>(L"VerifyEmail", ui.edit_verifyEmail->text().toStdWString());
		child.value().put<wstring>(L"VerifyPasswd", ui.edit_verifyPasswd->text().toStdWString());

		child.value().put<int>(L"OneGroupTime", ui.edit_oneGroupTime->text().toInt());
		child.value().put<int>(L"OneGroupEmail", ui.edit_oneGroupEmail->text().toInt());

		child.value().put<int>(L"KeyWordMsgSize", ui.edit_keyWordMsgSize->text().toInt());

		json::write_json(appFile + "conf.json", value);
		Conf::makeUpdate();
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return false;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("д��json�쳣"), QMessageBox::Ok);
		return false;
	}

	return true;
}


void WSystem::onSave()
{
	if (ui.edit_verifyEmail->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��֤�����˺Ų���Ϊ��"), QMessageBox::Ok);
		return;
	}
	else if (ui.edit_verifyPasswd->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��֤�������벻��Ϊ��"), QMessageBox::Ok);
		return;
	}


	if (writeConf())
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("�ɹ�"), QString::fromLocal8Bit("����ɹ�"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ʧ��"), QMessageBox::Ok);
	}
}