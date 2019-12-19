#include "WOther.h"

#include <qmessagebox.h>

#include "json.hpp"

extern string appFile;

WOther::WOther(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	read_main();

	connect(ui.button_save, SIGNAL(clicked()), this, SLOT(buttonSave()));
}

WOther::~WOther()
{
}

void WOther::buttonSave()
{
	write_main();

	QMessageBox::information(NULL, QString::fromLocal8Bit("成功"), QString::fromLocal8Bit("保存成功"), QMessageBox::Ok);
}

bool WOther::write_main()
{
	try
	{
		boost::property_tree::wptree value;
		read_json(appFile + "conf.json", value);

		//检测是否存在 不存在则创建一个
		auto child = value.get_child_optional(L"Main");
		if (!child)
		{
			value.add_child(L"Main", boost::property_tree::wptree(L""));
			child = value.get_child_optional(L"Main");
		}

		//child.value().put<bool>(L"OpenNewGroup", ui.check_openNewGroup->isChecked());
		child.value().put<bool>(L"UseHtml", ui.check_useHtml->isChecked());
		child.value().put<bool>(L"AddFriend", ui.check_addFriend->isChecked());
		child.value().put<bool>(L"AddGroupInto", ui.check_addGroupInto->isChecked());
		child.value().put<bool>(L"QuitGroupSend", ui.check_quitGroupSend->isChecked());


		json::write_json(appFile+"conf.json", value);
		Conf::makeUpdate();
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return false;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("写入json异常"), QMessageBox::Ok);
		return false;
	}

	return true;
}

bool WOther::read_main()
{
	try
	{
		boost::property_tree::wptree value;

		read_json(appFile + "conf.json", value);
		bool temp_addGroupInto = value.get<bool>(L"Main.AddGroupInto", false);
		bool temp_useHtml = value.get<bool>(L"Main.UseHtml", false);
		bool temp_addFriend = value.get<bool>(L"Main.AddFriend", false);
		//bool temp_openNewGroup = value.get<bool>(L"Main.", false);
		bool temp_quitGroupSend = value.get<bool>(L"Main.QuitGroupSend", false);

		ui.check_useHtml->setChecked(temp_useHtml);
		ui.check_addFriend->setChecked(temp_addFriend);
		ui.check_addGroupInto->setChecked(temp_addGroupInto);
		//ui.check_openNewGroup->setChecked(temp_openNewGroup);
		ui.check_quitGroupSend->setChecked(temp_quitGroupSend);
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

