#include "WEmailList.h"

#include "json.hpp"

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qdir.h>

extern string appFile;

WEmailList::WEmailList(QWidget* parent)
	: QWidget(parent)
	, m_modelIndex(0)
{
	ui.setupUi(this);

	//����
	m_model = new QStandardItemModel;

	m_contextMenu = new QMenu;
	m_contextMenu->addAction(QString::fromLocal8Bit("ɾ��"), this, SLOT(onDelete()));

	readLastWrod();
	read_data();

	connect(ui.button_add, SIGNAL(clicked()), this, SLOT(buttonAddList()));
	connect(ui.button_fromFile, SIGNAL(clicked()), this, SLOT(onFromFile()));
	connect(ui.button_outFile, SIGNAL(clicked()), this, SLOT(onOutFile()));
	connect(ui.tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
	//connect(ui.tableView, SIGNAL(dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)), this, SLOT(onTableUpdata(const QModelIndex & topLeft, const QModelIndex & bottomRight)));
}

WEmailList::~WEmailList()
{
	
}

//�ر��¼�
void WEmailList::closeEvent(QCloseEvent* event)
{
	saveLastWrod();
	write_data();

	m_model->clear();
	delete m_model;
}

//��ȡ�ϴ����������
void WEmailList::readLastWrod()
{
	try
	{
		boost::property_tree::wptree value;

		read_json(appFile + "conf.json", value);

		QString temp_email(QString::fromStdWString(value.get<wstring>(L"Win.WEmailList_LastEmail", L"").c_str()));
		QString temp_passwd(QString::fromStdWString(value.get<wstring>(L"Win.WEmailList_LastPasswd", L"").c_str()));
		QString temp_smtp(QString::fromStdWString(value.get<wstring>(L"Win.WEmailList_LastSmtp", L"").c_str()));

		QString temp_port(QString::fromStdWString(to_wstring(value.get<int>(L"Win.WEmailList_LastPort", 0)).c_str()));
		QString temp_dayMax(QString::fromStdWString(to_wstring(value.get<int>(L"Win.WEmailList_LastDayMax", 0)).c_str()));

		bool temp_ssl(value.get<bool>(L"Win.WEmailList_LastSSL", false));

		ui.edit_email->setText(temp_email);
		ui.edit_passwd->setText(temp_passwd);
		ui.edit_smtp->setText(temp_smtp);
		ui.edit_port->setText(temp_port);
		ui.edit_dayMax->setText(temp_dayMax);

		ui.check_ssl->setChecked(temp_ssl);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit((string("WEmailList�����ϴ���������� ") + e.what()).c_str()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡjson�쳣--WEmailList��ȡ�ϴ����������"), QMessageBox::Ok);
		return;
	}
}

//�����ϴ����������
void WEmailList::saveLastWrod()
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
	

		child.value().put<wstring>(L"WEmailList_LastEmail", ui.edit_email->text().toStdWString());
		child.value().put<wstring>(L"WEmailList_LastPasswd", ui.edit_passwd->text().toStdWString());
		child.value().put<wstring>(L"WEmailList_LastSmtp", ui.edit_smtp->text().toStdWString());

		child.value().put<int>(L"WEmailList_LastPort", ui.edit_port->text().toInt());
		child.value().put<int>(L"WEmailList_LastDayMax", ui.edit_dayMax->text().toInt());

		child.value().put<bool>(L"WEmailList_LastSSL", ui.check_ssl->isChecked());

		json::write_json(appFile + "conf.json", value);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit((string("WEmailList�����ϴ���������� ") + e.what()).c_str()), QMessageBox::Ok);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("д��json�쳣--WEmailList�����ϴ����������"), QMessageBox::Ok);
		return;
	}
}

// д������
bool WEmailList::write_data()
{
	try
	{
		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		auto child = value.get_child_optional(L"SmtpList");

		if (!child)
		{
			value.add_child(L"SmtpList", boost::property_tree::wptree(L""));
		}
		value.get_child(L"SmtpList").clear();


		boost::property_tree::wptree child_temp;

		for (int i = 0; i < m_model->rowCount(); i++)
		{
			child_temp.clear();

			wstring id(to_wstring(i + 1));



			QString email = m_model->itemFromIndex(m_model->index(i, 1))->text();
			QString passwd = m_model->itemFromIndex(m_model->index(i, 2))->text();
			QString max = m_model->itemFromIndex(m_model->index(i, 4))->text();
			QString smtp = m_model->itemFromIndex(m_model->index(i, 5))->text();
			QString prot = m_model->itemFromIndex(m_model->index(i, 6))->text();
			bool ssl = !(m_model->itemFromIndex(m_model->index(i, 7))->text().isEmpty());

			auto t = m_model->item(i)->checkState();
			child_temp.put<bool>(L"Switch", (t == Qt::Checked));
			child_temp.put<wstring>(L"Smtp", smtp.toStdWString());
			child_temp.put<wstring>(L"Email", email.toStdWString());
			child_temp.put<wstring>(L"Passwd", passwd.toStdWString());
			child_temp.put<int>(L"Port", prot.toInt());
			child_temp.put<int>(L"DayMax", max.toInt());
			child_temp.put<bool>(L"SSL", ssl);

			value.get_child(L"SmtpList").push_back(make_pair(id, child_temp));

		}
		json::write_json(appFile + "conf.json", value);

		Conf::makeUpdate();
		/*	std::wstringstream s2;
			write_json(s2, value);

			MessageBox(s2.str().c_str());*/ //for test

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
bool WEmailList::read_data()
{
	try
	{
		//���ԭ����
		m_model->clear();

		//������ͷ
		m_model->setColumnCount(8);
		m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("#"));
		m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("����"));
		m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("����"));
		m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("��"));
		m_model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("����"));
		m_model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("SMTP"));
		m_model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("�˿�"));
		m_model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("ssl"));

		//�����п�
		ui.tableView->setModel(m_model);
		ui.tableView->setColumnWidth(0, 30);
		ui.tableView->setColumnWidth(1, 200);
		ui.tableView->setColumnWidth(2, 200);
		ui.tableView->setColumnWidth(3, 60);
		ui.tableView->setColumnWidth(4, 60);
		ui.tableView->setColumnWidth(5, 150);
		ui.tableView->setColumnWidth(6, 60);
		ui.tableView->setColumnWidth(7, 60);

		ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);//����Ӧ��Ԫ�񳤶�
		ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);//����Ӧ��Ԫ�񳤶�
		//������ʽ
		/*ui.tableView->setFocusPolicy(Qt::NoFocus);
		ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
		ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);*/

		ui.tableView->installEventFilter(this);

		//��ȡ����ͳ��
		readCount();

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
			bool Switch = temp.second.get<bool>(L"Switch", false);

			QString temp_id(QString::fromStdWString(temp.first.c_str()));
			QString temp_smtp(QString::fromStdWString(temp.second.get<std::wstring>(L"Smtp", L"��ȡ����").c_str()));
			QString temp_email(QString::fromStdWString(temp.second.get<std::wstring>(L"Email", L"��ȡ����").c_str()));
			QString temp_passwd(QString::fromStdWString(temp.second.get<std::wstring>(L"Passwd", L"��ȡ����").c_str()));

			QString temp_port(QString::fromStdWString(to_wstring(temp.second.get<int>(L"Port", 25)).c_str()));
			bool temp_ssl(temp.second.get<bool>(L"SSL", false));
			QString temp_dayMax(QString::fromStdWString(to_wstring(temp.second.get<int>(L"DayMax", 0)).c_str()));
			QString temp_dayNum(to_string(emailDayNum[temp_email.toStdString()]).c_str());

			addList(temp_email, temp_passwd, temp_dayMax, temp_dayNum, temp_port, temp_ssl, temp_smtp, temp_id, Switch);
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

//��ȡͳ��
bool WEmailList::readCount()
{
	try
	{
		//��ȡȫ�ִ���ͳ��
		boost::property_tree::wptree value;
		read_json(appFile + "conf.json", value);

		//��ȡ�����б����
		//����Ƿ��������
		auto child_test = value.get_child_optional(L"EmailCountDay");

		if (!child_test)
		{
			value.add_child(L"EmailCountDay", boost::property_tree::wptree(L""));
		}

		boost::property_tree::wptree child = value.get_child(L"EmailCountDay");

		for (auto temp : child)
		{
			string email = OperateStr::wstring2string(temp.first);
			emailDayNum[email] = temp.second.get<int>(L"DayCount", 0);
		}

	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("��ȡ����ͳ�ƴ���"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return false;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("��ȡ����ͳ�ƴ���"), QString::fromLocal8Bit("��ȡjson�쳣"), QMessageBox::Ok);
		return false;
	}
}

//����б�
void WEmailList::addList(QString& email, QString& passwd, QString& adyMax, QString& port, bool ssl, QString& smtp)
{
	addList(email, passwd, adyMax, QString("0"), port, ssl, smtp, QString().number(m_modelIndex + 1), true);
}

//����б�
void WEmailList::addList(QString& email, QString& passwd, QString& adyMax, QString dayNum, QString& port, bool ssl, QString& smtp, QString id, bool s)
{

	//m_model->setItem(m_modelIndex, 0, new QStandardItem(id));
	auto p = new QStandardItem();

	p->setEditable(false);
	p->setCheckState(s ? Qt::Checked : Qt::Unchecked);
	m_model->setItem(m_modelIndex, 0, p);


	m_model->setItem(m_modelIndex, 1, new QStandardItem(email));
	m_model->setItem(m_modelIndex, 2, new QStandardItem(passwd));
	m_model->setItem(m_modelIndex, 3, new QStandardItem(dayNum));
	m_model->setItem(m_modelIndex, 4, new QStandardItem(adyMax));
	m_model->setItem(m_modelIndex, 5, new QStandardItem(smtp));
	m_model->setItem(m_modelIndex, 6, new QStandardItem(port));

	if (ssl)
		m_model->setItem(m_modelIndex, 7, new QStandardItem(QString::fromLocal8Bit("��")));
	else
		m_model->setItem(m_modelIndex, 7, new QStandardItem(""));

	m_modelIndex = m_model->rowCount();
}


void WEmailList::delList(int id)
{
	m_model->removeRow(id);
	m_modelIndex = m_model->rowCount();
}

//�����Ӱ�ť
void WEmailList::buttonAddList()
{
	if (ui.edit_email->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�����˺Ų���Ϊ��"), QMessageBox::Ok);
		return;
	}
	else if (ui.edit_passwd->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������벻��Ϊ��"), QMessageBox::Ok);
		return;
	}
	else if (ui.edit_smtp->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����smtp����Ϊ��"), QMessageBox::Ok);
		return;
	}
	else if (ui.edit_port->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����˿ڲ���Ϊ��"), QMessageBox::Ok);
		return;
	}


	QString adyMax = ui.edit_dayMax->text();
	QString email = ui.edit_email->text();
	QString passwd = ui.edit_passwd->text();
	QString port = ui.edit_port->text();
	QString smtp = ui.edit_smtp->text();
	bool ssl = ui.check_ssl->isChecked();

	addList(email, passwd, adyMax, port, ssl, smtp);

	write_data();

	/*
	ui.edit_dayMax->clear();
	ui.edit_email->clear();
	ui.edit_passwd->clear();
	ui.edit_port->clear();
	ui.edit_smtp->clear();
	ui.check_ssl->setChecked(false);
	*/
}

//����б�ѡ���¼�
void WEmailList::onTableClicked(const QModelIndex& m)
{
	if (m.column() == 0)
	{
		auto t = m_model->item(m.row())->checkState();
		m_model->item(m.row())->setCheckState((t == Qt::Checked) ? Qt::Unchecked : Qt::Checked);

		write_data();
	}
}


bool WEmailList::eventFilter(QObject* obj, QEvent* evt)
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
void WEmailList::onDelete()
{
	int delRow = ui.tableView->currentIndex().row();

	delList(delRow);//���ݵ�ǰ������ڵ���������λ��,ɾ��һ��

	write_data();

}

//���ļ��ﵼ��
void WEmailList::onFromFile()
{
	try
	{
		QString curPath = QDir::currentPath();//��ȡϵͳ��ǰĿ¼
		QString dlgTitle = QString::fromLocal8Bit("��һ���ļ�"); //�Ի������
		QString filter = QString::fromLocal8Bit("�����ļ�(*.*)"); //�ļ�������
		QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
		if (aFileName.isEmpty())
			return;

		fstream file(aFileName.toLocal8Bit().toStdString());

		if (!file.good())
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("ʧ��"), QString::fromLocal8Bit("�ļ���ʧ�� ") + aFileName);
			return;
		}

		char buf[10240];


		QString temp_email;
		QString temp_passwd;
		QString temp_adyMax;
		QString temp_port;
		QString temp_smtp;
		bool temp_ssl = false;
		while (file.getline(buf, 10240))
		{
			if (strlen(buf) == 0)
				continue;

			if (!strstr(buf, "----"))
			{
				throw exception("��ʽ���� û���ҵ��ָ���----");
			}
			else
			{
				int len = strlen("----");


				char temp_buf[10240];
				strcpy(temp_buf, buf);
				char* p = strstr(temp_buf, "----");
				if (p == NULL)
					throw exception("��ʽ����");
				*p = '\0';
				temp_email = temp_buf;

				strcpy(temp_buf, p + len);
				p = strstr(temp_buf, "----");
				if (p == NULL)
					throw exception("��ʽ����");
				*p = 0;
				temp_passwd = temp_buf;

				strcpy(temp_buf, p + len);
				p = strstr(temp_buf, "----");
				if (p == NULL)
					throw exception("��ʽ����");
				*p = 0;
				temp_smtp = temp_buf;

				strcpy(temp_buf, p + len);
				p = strstr(temp_buf, "----");
				if (p == NULL)
					throw exception("��ʽ����");
				*p = 0;
				temp_port = temp_buf;

				strcpy(temp_buf, p + len);
				p = strstr(temp_buf, "----");
				if (p == NULL)
				{
					temp_ssl = !strcmp(temp_buf, "true");
				}
				else
				{
					*p = 0;
					temp_ssl = !strcmp(temp_buf, "true");


					strcpy(temp_buf, p + len);
					temp_adyMax = temp_buf;
				}
			}


			if (temp_email.isEmpty() || temp_passwd.isEmpty() || temp_smtp.isEmpty() | temp_port.isEmpty())
			{
				throw exception("��ʽ����");
			}

			addList(temp_email, temp_passwd, temp_adyMax, temp_port, temp_ssl, temp_smtp);
		}


		QMessageBox::information(NULL, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("�������"), QMessageBox::Ok);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return;
	}
}

//���ļ�����
void WEmailList::onOutFile()
{
	QString filename = QFileDialog::getSaveFileName(this,

		QString::fromLocal8Bit("��������"),

		"",

		tr("*.txt")); //ѡ��·��

	if (filename.isEmpty())
	{
		return;
	}

	ofstream file(filename.toLocal8Bit(), ios::out);

	if (!file.good())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("ʧ��"), QString::fromLocal8Bit("�ļ�����ʧ��"));
		return;
	}

	for (int i = 0; i < m_model->rowCount(); i++)
	{
		string email = m_model->itemFromIndex(m_model->index(i, 1))->text().toLocal8Bit();
		string passwd = m_model->itemFromIndex(m_model->index(i, 2))->text().toLocal8Bit();
		string max = m_model->itemFromIndex(m_model->index(i, 4))->text().toLocal8Bit();
		string smtp = m_model->itemFromIndex(m_model->index(i, 5))->text().toLocal8Bit();
		string prot = m_model->itemFromIndex(m_model->index(i, 6))->text().toLocal8Bit();
		string ssl = !(m_model->itemFromIndex(m_model->index(i, 7))->text().isEmpty()) ? "true" : "false";

		file << email << "----" << passwd << "----" << smtp << "----" << prot << "----" << ssl << "----" << max << endl;
	}

	file.close();
	
	QMessageBox::information(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������"));
}

////�б����ݸ����¼�
//void WEmailList::onTableUpdata(const QModelIndex& topLeft, const QModelIndex& bottomRight)
//{
//	write_data();
//	QMessageBox::warning(NULL, QString::fromLocal8Bit("444"), QString::fromLocal8Bit("66666"), QMessageBox::Ok);
//
//
//}
