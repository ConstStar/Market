#include "WGroupList.h"

#include <qmessagebox.h>

#include "json.hpp"

#include <map>

using namespace std;

extern map<long long, wstring> WinGroupList;
extern string appFile;


WGroupList::WGroupList(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//����
	m_model = new QStandardItemModel;

	read_data();

	connect(ui.button_add, SIGNAL(clicked()), this, SLOT(buttonAddGroup()));
	connect(ui.tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
	connect(ui.checkBox, SIGNAL(clicked()), this, SLOT(onCheck()));
}

WGroupList::~WGroupList()
{
}

//�ر��¼�
void WGroupList::closeEvent(QCloseEvent* event)
{
	write_data();

	m_model->clear();
	delete m_model;
}

//��ȡ����
bool WGroupList::read_data()
{
	try
	{
		//���ԭ����
		m_model->clear();

		//������ͷ
		m_model->setColumnCount(3);
		m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("#"));
		m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("Ⱥ����"));
		m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("Ⱥ����"));

		//�����п�
		ui.tableView->setModel(m_model);
		ui.tableView->setColumnWidth(0, 50);
		ui.tableView->setColumnWidth(1, 190);
		ui.tableView->setColumnWidth(2, 100);
		ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);//����Ӧ��Ԫ�񳤶�

		//������ʽ
		ui.tableView->setFocusPolicy(Qt::NoFocus);
		ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
		ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

		//ui.tableView->installEventFilter(this);

		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//��ȡ��ѡ��
		auto child_test = value.get_child_optional(L"Main");

		if (!child_test)
		{
			value.add_child(L"Main", boost::property_tree::wptree(L""));
		}

		bool temp_checkBox = value.get<bool>(L"Main.GroupListType", false);

		ui.checkBox->setChecked(temp_checkBox);

		if (temp_checkBox)
		{
			ui.label_zt->setText(QString::fromLocal8Bit("<html><head/><body><p><span style=\"color:#FF0000;\">����Ⱥģʽ��ֻ���ѡ�е�Ⱥ�����Ⱥ���룬�����¼ӵ�Ⱥ</span></p></body></html>"));
		}
		else
		{
			ui.label_zt->setText(QString::fromLocal8Bit("<html><head/><body><p><span style=\"color:#0000FF;\">���Ⱥģʽ��ֻ���ѡ�е�Ⱥ����</span></p></body></html>"));
		}


		vector<long long> GroupList;
		json::json2vector_longlong(appFile + "conf.json", L"GroupList", GroupList);


		for (auto GroupId : GroupList)
		{
			int index = m_model->rowCount();
			auto p = new QStandardItem();
			p->setCheckState(Qt::Checked);

			m_model->setItem(index, 0, p);
			m_model->setItem(index, 1, new QStandardItem(QString::fromStdWString(WinGroupList[GroupId])));
			m_model->setItem(index, 2, new QStandardItem(QString::fromStdString(to_string(GroupId))));

		}

		//��������Ⱥ
		for (auto GroupId : WinGroupList)
		{
			//�ų��Ѿ�������Ⱥ
			if (std::find(GroupList.begin(), GroupList.end(), GroupId.first) != GroupList.end())
			{
				//MessageBox(CString(to_string(it.first).c_str()));  //for test
				continue;
			}

			int index = m_model->rowCount();
			auto p = new QStandardItem();
			p->setCheckState(Qt::Unchecked);

			m_model->setItem(index, 0, p);
			m_model->setItem(index, 1, new QStandardItem(QString::fromStdWString(GroupId.second)));
			m_model->setItem(index, 2, new QStandardItem(QString::fromStdString(to_string(GroupId.first))));
		}


		m_model->sort(0);
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

//д������
bool WGroupList::write_data()
{
	try
	{
		boost::property_tree::wptree child_temp;
		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//����Ƿ������࣬û���򴴽�һ��
		auto child = value.get_child_optional(L"GroupList");
		if (!child)
		{
			value.add_child(L"GroupList", boost::property_tree::wptree(L""));
		}

		//���ԭ������
		value.get_child(L"GroupList").clear();


		for (int i = 0; i < m_model->rowCount() ; i++)
		{
			if (m_model->item(i)->checkState()==Qt::Checked)
			{
				child_temp.clear();

				child_temp.put<long long>(L"", m_model->item(i,2)->text().toLongLong());

				value.get_child(L"GroupList").push_back(make_pair(L"", child_temp));
			}
		}

		//���渴ѡ������
		child = value.get_child_optional(L"Main");
		if (!child)
		{
			value.add_child(L"Main", boost::property_tree::wptree(L""));
			child = value.get_child_optional(L"Main");
		}
		child.value().put<bool>(L"GroupListType", ui.checkBox->isChecked());

		json::write_json(appFile + "conf.json", value);

		Conf::makeUpdate();
		//std::wstringstream s2;
		//write_json(s2, value);

		//MessageBox(s2.str().c_str()); //for test

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

//�ֶ����Ⱥ
void WGroupList::buttonAddGroup()
{
	int index = m_model->rowCount();

	auto p = new QStandardItem();
	p->setCheckState(Qt::Checked);

	m_model->setItem(index, 0, p);
	m_model->setItem(index, 2, new QStandardItem(ui.edit_groupId->text()));
	write_data();
	read_data();

}

//����б�ѡ���¼�
void WGroupList::onTableClicked(const QModelIndex& m)
{
	if (m.column() == 0)
	{
		auto t = m_model->item(m.row())->checkState();
		m_model->item(m.row())->setCheckState((t == Qt::Checked) ? Qt::Unchecked : Qt::Checked);

		write_data();
	}
}

//��ѡ��
void WGroupList::onCheck()
{
	write_data();

	if (ui.checkBox->isChecked())
	{
		ui.label_zt->setText(QString::fromLocal8Bit("<html><head/><body><p><span style=\"color:#FF0000;\">��ǰΪ����Ⱥģʽ��ֻ���ѡ�е�Ⱥ�����Ⱥ���룬�����¼ӵ�Ⱥ</span></p></body></html>"));
	}
	else
	{
		ui.label_zt->setText(QString::fromLocal8Bit("<html><head/><body><p><span style=\"color:#0000FF;\">��ǰΪ���Ⱥģʽ��ֻ���ѡ�е�Ⱥ����</span></p></body></html>"));
	}
}