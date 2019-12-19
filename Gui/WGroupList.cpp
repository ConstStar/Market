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

	//创建
	m_model = new QStandardItemModel;

	read_data();

	connect(ui.button_add, SIGNAL(clicked()), this, SLOT(buttonAddGroup()));
	connect(ui.tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
	connect(ui.checkBox, SIGNAL(clicked()), this, SLOT(onCheck()));
}

WGroupList::~WGroupList()
{
}

//关闭事件
void WGroupList::closeEvent(QCloseEvent* event)
{
	write_data();

	m_model->clear();
	delete m_model;
}

//读取数据
bool WGroupList::read_data()
{
	try
	{
		//清空原数据
		m_model->clear();

		//设置列头
		m_model->setColumnCount(3);
		m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("#"));
		m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("群名称"));
		m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("群号码"));

		//设置列宽
		ui.tableView->setModel(m_model);
		ui.tableView->setColumnWidth(0, 50);
		ui.tableView->setColumnWidth(1, 190);
		ui.tableView->setColumnWidth(2, 100);
		ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);//自适应单元格长度

		//设置样式
		ui.tableView->setFocusPolicy(Qt::NoFocus);
		ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
		ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

		//ui.tableView->installEventFilter(this);

		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//读取复选框
		auto child_test = value.get_child_optional(L"Main");

		if (!child_test)
		{
			value.add_child(L"Main", boost::property_tree::wptree(L""));
		}

		bool temp_checkBox = value.get<bool>(L"Main.GroupListType", false);

		ui.checkBox->setChecked(temp_checkBox);

		if (temp_checkBox)
		{
			ui.label_zt->setText(QString::fromLocal8Bit("<html><head/><body><p><span style=\"color:#FF0000;\">过滤群模式，只监控选中的群除外的群号码，包括新加的群</span></p></body></html>"));
		}
		else
		{
			ui.label_zt->setText(QString::fromLocal8Bit("<html><head/><body><p><span style=\"color:#0000FF;\">监控群模式，只监控选中的群号码</span></p></body></html>"));
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

		//放置其他群
		for (auto GroupId : WinGroupList)
		{
			//排除已经开启的群
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

//写入数据
bool WGroupList::write_data()
{
	try
	{
		boost::property_tree::wptree child_temp;
		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//检查是否有子类，没有则创建一个
		auto child = value.get_child_optional(L"GroupList");
		if (!child)
		{
			value.add_child(L"GroupList", boost::property_tree::wptree(L""));
		}

		//清空原有数据
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

		//保存复选框设置
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

//手动添加群
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

//点击列表复选框事件
void WGroupList::onTableClicked(const QModelIndex& m)
{
	if (m.column() == 0)
	{
		auto t = m_model->item(m.row())->checkState();
		m_model->item(m.row())->setCheckState((t == Qt::Checked) ? Qt::Unchecked : Qt::Checked);

		write_data();
	}
}

//复选框
void WGroupList::onCheck()
{
	write_data();

	if (ui.checkBox->isChecked())
	{
		ui.label_zt->setText(QString::fromLocal8Bit("<html><head/><body><p><span style=\"color:#FF0000;\">当前为过滤群模式，只监控选中的群除外的群号码，包括新加的群</span></p></body></html>"));
	}
	else
	{
		ui.label_zt->setText(QString::fromLocal8Bit("<html><head/><body><p><span style=\"color:#0000FF;\">当前为监控群模式，只监控选中的群号码</span></p></body></html>"));
	}
}