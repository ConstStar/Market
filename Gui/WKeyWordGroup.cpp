#include "WKeyWordGroup.h"

#include <string>
#include <qmessagebox.h>

#include "json.hpp"

using namespace std;


extern string appFile;

WKeyWordGroup::WKeyWordGroup(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	init();

	connect(ui.button_save, SIGNAL(clicked()), this, SLOT(onSave()));
	connect(ui.check_streng, SIGNAL(clicked()), this, SLOT(onCheck()));
}

WKeyWordGroup::~WKeyWordGroup()
{
}

void WKeyWordGroup::init()
{
	try
	{
		//���ԭ����
		ui.text_keyWord->clear();

		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);


		//��ȡ�ؼ���

		//����Ƿ��������
		auto child_test = value.get_child_optional(L"KeyWord");

		if (!child_test)
		{
			value.add_child(L"KeyWord", boost::property_tree::wptree(L""));
		}

		boost::property_tree::wptree child = value.get_child(L"KeyWord");


		QString	temp_keyWord;
		for (auto temp : child)
		{
			QString temp_str(QString::fromStdWString(temp.second.data().c_str()));

			temp_keyWord += temp_str + "\n";
		}

		ui.text_keyWord->setPlainText(temp_keyWord);

		//��ȡ��ѡ��
		child_test = value.get_child_optional(L"Main");

		if (!child_test)
		{
			value.add_child(L"Main", boost::property_tree::wptree(L""));
		}

		bool temp_streng = value.get<bool>(L"Main.Streng", false);

		ui.check_streng->setChecked(temp_streng);

	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡjson�쳣"), QMessageBox::Ok);
		return;
	}

	return;
}

void WKeyWordGroup::write()
{
	try
	{

		QString line;
		boost::property_tree::wptree value;

		json::read_json(appFile + "conf.json", value);

		//����ؼ����б�
		auto child = value.get_child_optional(L"KeyWord");
		if (!child)
		{
			value.add_child(L"KeyWord", boost::property_tree::wptree(L""));
			child = value.get_child_optional(L"KeyWord");
		}
		else
		{
			child.value().clear();
		}


		QString nameStr = ui.text_keyWord->toPlainText();
		nameStr.replace(" ", "");
		nameStr.replace("\t", "");
		nameStr.replace("\"", "");
		QStringList nameList = nameStr.split("\n");

		boost::property_tree::wptree temp;
		for (auto name : nameList)
		{
			if (name.isEmpty())
				continue;

			temp.put<wstring>(L"", name.toStdWString());
			child.value().push_back(make_pair(L"", temp));

		}

		//���渴ѡ������
		child = value.get_child_optional(L"Main");
		if (!child)
		{
			value.add_child(L"Main", boost::property_tree::wptree(L""));
			child = value.get_child_optional(L"Main");
		}

		child.value().put<bool>(L"Streng", ui.check_streng->isChecked());

		write_json(appFile + "conf.json", value);

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
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("д��json�쳣"), QMessageBox::Ok);
		return;
	}
}

void WKeyWordGroup::onSave()
{
	write();
	QMessageBox::information(NULL, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("����ɹ�"), QMessageBox::Ok);
}


//�����ѡ���¼�
void WKeyWordGroup::onCheck()
{
	write();
}