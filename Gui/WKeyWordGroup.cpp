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

	//����
	m_model = new QStandardItemModel;

	m_contextMenu = new QMenu;
	m_contextMenu->addAction(QString::fromLocal8Bit("ɾ��"), this, SLOT(onDelete()));


	init();

	connect(ui.button_add, SIGNAL(clicked()), this, SLOT(onAdd()));
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
		ui.list_keyWord->clear();

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

		for (auto temp : child)
		{
			QString temp_str(QString::fromStdWString(temp.second.data().c_str()));

			addList(temp_str);
		}

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

		boost::property_tree::wptree temp;
		for (int i = 0; i < ui.list_keyWord->count(); i++)
		{
			line = ui.list_keyWord->item(i)->text();

			temp.put<wstring>(L"", line.toStdWString());
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

//���
void WKeyWordGroup::addList(QString str)
{
	QListWidgetItem* item = new QListWidgetItem;
	item->setText(str);                     //�����б�����ı�
	ui.list_keyWord->addItem(item);
}

void WKeyWordGroup::contextMenuEvent(QContextMenuEvent* event)
{
	m_contextMenu->exec(QCursor::pos()); // �˵����ֵ�λ��Ϊ��ǰ����λ��
}

void WKeyWordGroup::onAdd()
{
	if (ui.edit_keyWord->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ؼ��ʲ���Ϊ��"), QMessageBox::Ok);
		return;
	}

	QString str = ui.edit_keyWord->text();
	addList(str);

	ui.edit_keyWord->clear();
	write();
}

//���ɾ���˵�
void WKeyWordGroup::onDelete()
{
	int row = ui.list_keyWord->currentIndex().row();
	if (row >= 0)
	{
		QListWidgetItem* item = ui.list_keyWord->takeItem(row);
		ui.list_keyWord->removeItemWidget(item);

		delete item;
	}

	write();
	//ui.list_keyWord->itemDelegateForRow(ui.list_keyWord->currentIndex().row());//���ݵ�ǰ������ڵ���������λ��,ɾ��һ��
}

//�����ѡ���¼�
void WKeyWordGroup::onCheck()
{
	write();
}