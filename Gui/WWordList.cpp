#include "WWordList.h"
#include "WWordLook.h"

#include <qmessagebox.h>

#include "json.hpp"


extern string appFile;

WWordList::WWordList(QWidget* parent)
	: QWidget(parent)
	, m_modelIndex(0)
	, m_editRow(-1)
{
	ui.setupUi(this);

	//����
	m_model = new QStandardItemModel;

	m_contextMenu = new QMenu;
	m_contextMenu->addAction(QString::fromLocal8Bit("�༭"), this, SLOT(onEdit()));
	m_contextMenu->addAction(QString::fromLocal8Bit("ɾ��"), this, SLOT(onDelete()));

	readLastWrod();
	read_data();

	connect(ui.button_add, SIGNAL(clicked()), this, SLOT(buttonAddList()));
	connect(ui.button_look, SIGNAL(clicked()), this, SLOT(onLook()));
	connect(ui.tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));

}

WWordList::~WWordList()
{
}

// �ر��¼�
void WWordList::closeEvent(QCloseEvent* event)
{
	saveLastWrod();
	write_data();

	m_model->clear();
	delete m_model;
}

//��ȡ�ϴ����������
void WWordList::readLastWrod()
{
	try
	{
		boost::property_tree::wptree value;

		read_json(appFile + "conf.json", value);
	
		QString temp_name(QString::fromStdWString(value.get<wstring>(L"Win.WWordList_LastName", L"").c_str()));
		QString temp_title(QString::fromStdWString(value.get<wstring>(L"Win.WWordList_LastTitle", L"").c_str()));
		QString temp_word(QString::fromStdWString(value.get<wstring>(L"Win.WWordList_LastWord", L"").c_str()));

		ui.edit_name->setText(temp_name);
		ui.edit_title->setText(temp_title);
		ui.text_word->setPlainText(temp_word);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit((string("WWordList�����ϴ���������� ") + e.what()).c_str()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡjson�쳣--WWordList��ȡ�ϴ����������"), QMessageBox::Ok);
		return;
	}
}

//�����ϴ����������
void WWordList::saveLastWrod()
{
	try
	{
		boost::property_tree::wptree value;
		read_json(appFile + "conf.json", value);

		//����Ƿ���� �������򴴽�һ��
		auto child = value.get_child_optional(L"Win");
		if (!child)
		{
			value.add_child(L"Win", boost::property_tree::wptree(L""));
			child = value.get_child_optional(L"Win");
		}

		child.value().put<wstring>(L"WWordList_LastName", ui.edit_name->text().toStdWString());
		child.value().put<wstring>(L"WWordList_LastTitle", ui.edit_title->text().toStdWString());
		child.value().put<wstring>(L"WWordList_LastWord", ui.text_word->toPlainText().toStdWString());

		json::write_json(appFile + "conf.json", value);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit((string("WWordList�����ϴ���������� ") + e.what()).c_str()), QMessageBox::Ok);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("д��json�쳣--WWordList�����ϴ����������"), QMessageBox::Ok);
		return;
	}
}


//����б�
void WWordList::addList(QString& name, QString& title, QString& word)
{
	addList(name, title, word, QString().number(m_modelIndex + 1), true);
}

//����б�
void WWordList::addList(QString& name, QString& title, QString& word, QString id, bool s)
{
	//m_model->setItem(m_modelIndex, 0, new QStandardItem(id));

	auto p = new QStandardItem();
	p->setEditable(false);
	p->setCheckState(s ? Qt::Checked : Qt::Unchecked);
	m_model->setItem(m_modelIndex, 0, p);

	m_model->setItem(m_modelIndex, 1, new QStandardItem(title));
	m_model->setItem(m_modelIndex, 2, new QStandardItem(word));
	//m_model->setItem(m_modelIndex, 3, new QStandardItem(file));
	m_model->setItem(m_modelIndex, 3, new QStandardItem(name));

	m_modelIndex = m_model->rowCount();
}

//�༭�б�
void WWordList::editList(QString& name, QString& title, QString& word)
{
	if (m_editRow == -1)
		return;

	m_model->itemFromIndex(m_model->index(m_editRow, 1))->setText(title);
	m_model->itemFromIndex(m_model->index(m_editRow, 2))->setText(word);
	//m_model->itemFromIndex(m_model->index(m_editRow, 3))->setText(file);
	m_model->itemFromIndex(m_model->index(m_editRow, 3))->setText(name);

	m_editRow = -1;
}

//ɾ���б�
void WWordList::delList(int id)
{
	m_model->removeRow(id);
	m_modelIndex = m_model->rowCount();
}

//д������
bool WWordList::write_data()
{
	try
	{
		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		auto child = value.get_child_optional(L"WordList");

		if (!child)
		{
			value.add_child(L"WordList", boost::property_tree::wptree(L""));
		}
		value.get_child(L"WordList").clear();


		boost::property_tree::wptree child_temp;

		for (int i = 0; i < m_model->rowCount(); i++)
		{

			child_temp.clear();

			wstring id(to_wstring(i + 1));

			QString temp_title = m_model->itemFromIndex(m_model->index(i, 1))->text();
			QString temp_word = m_model->itemFromIndex(m_model->index(i, 2))->text();
			//QString temp_file = m_model->itemFromIndex(m_model->index(i, 3))->text();
			QString temp_name = m_model->itemFromIndex(m_model->index(i, 3))->text();

			auto t = m_model->item(i)->checkState();
			child_temp.put<bool>(L"Switch", (t == Qt::Checked));
			child_temp.put<wstring>(L"Title", temp_title.toStdWString());
			child_temp.put<wstring>(L"Word", temp_word.toStdWString());
			//child_temp.put<wstring>(L"File", temp_file.toStdWString());
			child_temp.put<wstring>(L"Name", temp_name.toStdWString());

			value.get_child(L"WordList").push_back(make_pair(id, child_temp));

		}
		json::write_json(appFile + "conf.json", value);

		Conf::makeUpdate();

		//std::wstringstream s2;
		//write_json(s2, value);

		//QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromStdWString(s2.str()), QMessageBox::Ok); //for test

	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return false;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(" д��json�쳣"), QMessageBox::Ok);
		return false;
	}
	return true;
}

//��ȡ����
bool WWordList::read_data()
{
	try
	{
		//���ԭ����
		m_model->clear();

		//������ͷ
		m_model->setColumnCount(4);
		m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("#"));
		m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("����"));
		m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("����"));
		//m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("����"));
		m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("����"));

		//�����п�
		ui.tableView->setModel(m_model);
		ui.tableView->setColumnWidth(0, 30);
		ui.tableView->setColumnWidth(1, 220);
		ui.tableView->setColumnWidth(2, 170);
		//ui.tableView->setColumnWidth(3, 170);
		ui.tableView->setColumnWidth(3, 150);
		ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);//����Ӧ��Ԫ�񳤶�

		//������ʽ
	/*ui.tableView->setFocusPolicy(Qt::NoFocus);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);*/

		ui.tableView->installEventFilter(this);


		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//����Ƿ��������
		auto child_test = value.get_child_optional(L"WordList");

		if (!child_test)
		{
			value.add_child(L"WordList", boost::property_tree::wptree(L""));
		}

		boost::property_tree::wptree child = value.get_child(L"WordList");

		for (auto temp : child)
		{
			//��ȡ����
			bool s = temp.second.get<bool>(L"Switch", false);

			QString id_temp(QString::fromStdWString(temp.first.c_str()));
			QString temp_name(QString::fromStdWString(temp.second.get<std::wstring>(L"Name").c_str()));
			QString temp_title(QString::fromStdWString(temp.second.get<std::wstring>(L"Title").c_str()));
			QString temp_word(QString::fromStdWString(temp.second.get<std::wstring>(L"Word").c_str()));
			//QString temp_file;//(QString::fromStdWString(temp.second.get<std::wstring>(L"File").c_str()));

			addList(temp_name, temp_title, temp_word, id_temp, s);
		}

	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		return false;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡjson�쳣"), QMessageBox::Ok);
		return false;
	}

	return true;
}


//�����Ӱ�ť
void WWordList::buttonAddList()
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
	

	QString temp_title = ui.edit_title->text();
	QString temp_word = ui.text_word->toPlainText();
	//QString temp_file = ui.edit_file->text();
	QString temp_name = ui.edit_name->text();

	if (ui.button_add->text() == QString::fromLocal8Bit("���"))
	{
		addList(temp_name, temp_title, temp_word);
	}
	else
	{
		editList(temp_name, temp_title, temp_word);
		ui.button_add->setText(QString::fromLocal8Bit("���"));
	}

	write_data();
}

//����б�ѡ���¼�
void WWordList::onTableClicked(const QModelIndex& m)
{
	if (m.column() == 0)
	{
		auto t = m_model->item(m.row())->checkState();
		m_model->item(m.row())->setCheckState((t == Qt::Checked) ? Qt::Unchecked : Qt::Checked);

		write_data();
	}
}


bool WWordList::eventFilter(QObject* obj, QEvent* evt)
{
	if (obj == ui.tableView && evt->type() == QEvent::ContextMenu)
	{
		if (ui.tableView->currentIndex().isValid() == true)
		{
			m_contextMenu->exec(cursor().pos());           //�ڵ�ǰ���λ�������в˵�menu����
		}
	}
	return QWidget::eventFilter(obj, evt);
}

//���ɾ���˵�
void WWordList::onDelete()
{
	int delRow = ui.tableView->currentIndex().row();
	delList(delRow);//���ݵ�ǰ������ڵ���������λ��,ɾ��һ��

	write_data();


	if (m_editRow > delRow)
	{
		m_editRow--;
		ui.button_add->setText(QString::fromLocal8Bit("�޸� #") + to_string(m_editRow + 1).c_str());
	}
	else if (m_editRow == delRow)
	{
		m_editRow = -1;
		ui.button_add->setText(QString::fromLocal8Bit("���"));
	}
}

//����༭�˵�
void WWordList::onEdit()
{
	//��ȡ�޸���
	m_editRow = ui.tableView->currentIndex().row();

	//��ȡ�޸�����
	QString temp_title = m_model->itemFromIndex(m_model->index(m_editRow, 1))->text();
	QString temp_word = m_model->itemFromIndex(m_model->index(m_editRow, 2))->text();
	//QString temp_file = m_model->itemFromIndex(m_model->index(m_editRow, 3))->text();
	QString temp_name = m_model->itemFromIndex(m_model->index(m_editRow, 3))->text();

	ui.edit_title->setText(temp_title);
	ui.text_word->setPlainText(temp_word);
	//ui.edit_file=setText(temp_file);
	ui.edit_name->setText(temp_name);

	//�޸İ�ť����
	ui.button_add->setText(QString::fromLocal8Bit("�޸� #") + to_string(m_editRow + 1).c_str());
}

//Ч�����
void WWordList::onLook()
{
	WWordLook* a = new WWordLook(ui.text_word->toPlainText());
	a->show();

}