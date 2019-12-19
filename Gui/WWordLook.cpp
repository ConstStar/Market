#include "WWordLook.h"

#include <qmessagebox.h>

#include "json.hpp"

#include <string>

using namespace std;


extern string appFile;

WWordLook::WWordLook(QString text, QWidget* parent)
	: QWidget(parent)
	, m_text(text)
	, m_useHtml(false)
{
	ui.setupUi(this);
	init();
}

WWordLook::~WWordLook()
{
}

void WWordLook::init()
{
	try
	{
		boost::property_tree::wptree value;

		read_json(appFile + "conf.json", value);
		m_useHtml = value.get<bool>(L"Main.UseHtml", false);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("´íÎó"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "´íÎó", MB_OK);
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("´íÎó"), QString::fromLocal8Bit("¶ÁÈ¡jsonÒì³£"), QMessageBox::Ok);
	}


	ui.textEdit->setReadOnly(true);
	if (m_useHtml)
	{
		ui.textEdit->setHtml(m_text);
	}
	else
	{
		ui.textEdit->setText(m_text);
	}
}