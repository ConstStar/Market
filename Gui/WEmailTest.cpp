#include "WEmailTest.h"
#include <qmessagebox.h>
#include <qclipboard.h>
#include <qtconcurrentrun.h>

#include <email/phpSendEmail.hpp>
#include "json.hpp"

using namespace std;

extern string appFile;

OTHER_CONF otherCfg;

string phpPath(".\\PHPRun");
string phpFile(".\\PHPRun\\Core\\php.exe");
string sendFile(".\\PHPRun\\Send.php");
string verifyFile(".\\PHPRun\\Verify.php");

WEmailTest::WEmailTest(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//����
	m_model = new QStandardItemModel;

	readLastWrod();
	read_emailList();
	read_wordList();

	////����ֻ����������
	//QValidator* validator = new QIntValidator(0, 999999999999, this);
	//ui.edit_verifyEmail->setValidator(validator);

	connect(ui.button_test, SIGNAL(clicked()), this, SLOT(onTest()));
	connect(ui.button_verify, SIGNAL(clicked()), this, SLOT(onVerify()));
	connect(ui.tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
	connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(slotRowDoubleClicked(const QModelIndex&)));
}

WEmailTest::~WEmailTest()
{
}

//�ر��¼�
void WEmailTest::closeEvent(QCloseEvent* event)
{

	saveLastWrod();

}

//�����ϴ����������
void WEmailTest::saveLastWrod()
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

		wstring test = ui.edit_putEmail->text().toStdWString();
		wstring verify = ui.edit_verifyEmail->text().toStdWString();

		child.value().put<wstring>(L"WEmailTest_LastGetEmail", test);
		child.value().put<wstring>(L"WEmailTest_LastVerify", verify);

		json::write_json(appFile + "conf.json", value);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit((string("WEmailTest�����ϴ���������� ") + e.what()).c_str()), QMessageBox::Ok);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("д��json�쳣--WEmailTest�����ϴ����������"), QMessageBox::Ok);
		return;
	}
}

//��ȡ�����������
void WEmailTest::readLastWrod()
{
	try
	{
		boost::property_tree::wptree value;

		read_json(appFile + "conf.json", value);

		QString temp_lastGetEmail = QString::fromStdWString(value.get<wstring>(L"Win.WEmailTest_LastGetEmail", L""));
		QString temp_lastVerify = QString::fromStdWString(value.get<wstring>(L"Win.WEmailTest_LastVerify", L""));

		ui.edit_putEmail->setText(temp_lastGetEmail);
		ui.edit_verifyEmail->setText(temp_lastVerify);
	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit((string("WEmailTest�����ϴ���������� ") + e.what()).c_str()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡjson�쳣--WEmailTest��ȡ�ϴ����������"), QMessageBox::Ok);
		return;
	}
}


//��ȡ��������
bool WEmailTest::get_otherConf()
{
	try
	{
		boost::property_tree::wptree value;

		read_json(appFile + "conf.json", value);
		otherCfg.useHtml = value.get<bool>(L"Main.UseHtml", false);

		otherCfg.verifyEmail = OperateStr::wstring2string(value.get<wstring>(L"Main.VerifyEmail", L""));
		otherCfg.verifyPasswd = OperateStr::wstring2string(value.get<wstring>(L"Main.VerifyPasswd", L""));

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

//��ȡ�����б�
bool WEmailTest::read_emailList()
{
	try
	{
		//���ԭ����
		m_model->clear();

		//������ͷ
		m_model->setColumnCount(7);
		m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("#"));
		m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("����"));
		m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("״̬"));
		m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("����"));
		m_model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("SMTP"));
		m_model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("�˿�"));
		m_model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("SSL"));

		//�����п�
		ui.tableView->setModel(m_model);
		ui.tableView->setColumnWidth(0, 30);
		ui.tableView->setColumnWidth(1, 170);
		ui.tableView->setColumnWidth(2, 200);
		ui.tableView->setColumnWidth(3, 150);
		ui.tableView->setColumnWidth(4, 140);
		ui.tableView->setColumnWidth(5, 40);
		ui.tableView->setColumnWidth(6, 40);

		//ui.tableView->resizeRowsToContents();//����Ӧ�����ı�
		ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);//����Ӧ��Ԫ�񳤶�

		//������ʽ
		ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


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
			QString temp_smtp(QString::fromStdWString(temp.second.get<std::wstring>(L"Smtp").c_str()));
			QString temp_email(QString::fromStdWString(temp.second.get<std::wstring>(L"Email").c_str()));
			QString temp_passwd(QString::fromStdWString(temp.second.get<std::wstring>(L"Passwd").c_str()));

			QString temp_port(QString::fromStdWString(to_wstring(temp.second.get<int>(L"Port")).c_str()));

			bool temp_ssl = temp.second.get<bool>(L"SSL");

			auto p = new QStandardItem();


			int m_modelIndex = m_model->rowCount();

			p->setEditable(false);
			p->setCheckState(Qt::Unchecked);
			m_model->setItem(m_modelIndex, 0, p);


			m_model->setItem(m_modelIndex, 1, new QStandardItem(temp_email));
			m_model->setItem(m_modelIndex, 2, new QStandardItem());
			m_model->setItem(m_modelIndex, 3, new QStandardItem(temp_passwd));
			m_model->setItem(m_modelIndex, 4, new QStandardItem(temp_smtp));
			m_model->setItem(m_modelIndex, 5, new QStandardItem(temp_port));

			if (temp_ssl)
				m_model->setItem(m_modelIndex, 6, new QStandardItem(QString::fromLocal8Bit("��")));
			else
				m_model->setItem(m_modelIndex, 6, new QStandardItem(""));

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

//��ȡ�����б�
bool WEmailTest::read_wordList()
{
	try
	{
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
			QString title_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Title").c_str()));

			ui.combo_word->addItem(title_temp);
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

//�����ʼ���Ͱ�ť��
void WEmailTest::onTest()
{
	ui.button_test->setText(QString::fromLocal8Bit("���ڲ�����..."));
	ui.button_test->setEnabled(false);
	ui.button_test->update();

	//QFuture < void > future = QtConcurrent::run([&]() {
	try
	{
		string name;
		string title;
		string word;
		string putEmail;
		//string file;

		//��ȡ��������
		get_otherConf();

		//������Ϣ������
		putEmail = ui.edit_putEmail->text().toStdString();

		//��ȡ��������
		if (!get_word(ui.combo_word->currentIndex() + 1, name, title, word))
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡ��������ʧ��"), QMessageBox::Ok);
			ui.button_test->setText(QString::fromLocal8Bit("���Դ���"));
			ui.button_test->setEnabled(true);
			return;
		}

		MsgValue(word);
		MsgValue(title);
		MsgValue(name);

		for (int i = 0; i < m_model->rowCount(); i++)
		{
			if (m_model->item(i)->checkState() == Qt::Checked)
			{
				m_model->itemFromIndex(m_model->index(i, 2))->setText(QString::fromLocal8Bit("׼������"));
			}
		}

		ui.tableView->resizeRowsToContents();//����Ӧ�����ı�

		//��ʼ���������б�
		for (int i = 0; i < m_model->rowCount(); i++)
		{
			QCoreApplication::processEvents();

			if (m_model->item(i)->checkState() == Qt::Checked)
			{
				m_model->itemFromIndex(m_model->index(i, 2))->setText(QString::fromLocal8Bit("���ڷ���"));
				ui.tableView->update(m_model->index(i, 2));


				string emailText = m_model->item(i, 1)->text().toLocal8Bit();
				string passwd = m_model->item(i, 3)->text().toLocal8Bit();
				string smtp = m_model->item(i, 4)->text().toLocal8Bit();
				string port = m_model->item(i, 5)->text().toLocal8Bit();
				bool ssl = !(m_model->item(i, 6)->text().isEmpty());

				phpSendEmail email(
					phpPath,
					phpFile,
					sendFile,
					smtp,
					ssl,
					port,
					emailText,
					passwd,
					putEmail,
					name,
					title,
					word
				);

				/*���ø�ʽ*/

				//����html��ʽ
				email.setIsHtml(otherCfg.useHtml);


				QCoreApplication::processEvents();
				bool ret = email.send();
				QCoreApplication::processEvents();

				if (ret)
				{
					//string error = email.getInf();
					//m_model->itemFromIndex(m_model->index(i, 2))->setText(QString::fromLocal8Bit("���ͳɹ� ������Ϣ:") + QString::fromLocal8Bit(error.c_str()));
					m_model->itemFromIndex(m_model->index(i, 2))->setText(QString::fromLocal8Bit("���ͳɹ�"));
					ui.tableView->update(m_model->index(i, 2));
				}
				else
				{
					string error = email.getInf();

					if (error.empty())
					{
						error = "δ֪ԭ��";
					}

					//�޸���ʾ����
					m_model->itemFromIndex(m_model->index(i, 2))->setText(QString::fromLocal8Bit("����ʧ�� ������Ϣ:") + QString::fromLocal8Bit(error.c_str()));
					ui.tableView->update(m_model->index(i, 2));
				}

			}
			ui.tableView->resizeRowsToContents();//����Ӧ�����ı�
		}
		ui.button_test->setText(QString::fromLocal8Bit("�������"));
		ui.button_test->setEnabled(true);

	}
	catch (exception & e)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		ui.button_test->setText(QString::fromLocal8Bit("���Դ���"));
		ui.button_test->setEnabled(true);
		return;
	}
	catch (...)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȡjson�쳣"), QMessageBox::Ok);

		ui.button_test->setText(QString::fromLocal8Bit("���Դ���"));
		ui.button_test->setEnabled(true);
		return;
	}
	//});
}

//��ȡ����
bool WEmailTest::get_word(int id, string& name, string& title, string& word)
{

	try
	{
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
			QString id_temp(QString::fromStdWString(temp.first.c_str()));

			if (id_temp.toInt() == id)
			{
				string name_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Name")).toLocal8Bit());
				string title_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Title")).toLocal8Bit());
				string word_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"Word")).toLocal8Bit());
				//string file_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"File")).toLocal8Bit());

				name = name_temp;
				title = title_temp;
				word = word_temp;

				/*	for (auto one : word_temp)
					{
						if (one == '\n')
						{
							word += "\r\n";
						}
						else
						{
							word += one;
						}
					}*/


					//file = file_temp;

				return true;
			}

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


	return false;
}

//����б�ѡ���¼�
void WEmailTest::onTableClicked(const QModelIndex& m)
{
	if (m.column() == 0)
	{
		auto t = m_model->item(m.row())->checkState();
		m_model->item(m.row())->setCheckState((t == Qt::Checked) ? Qt::Unchecked : Qt::Checked);
	}
}

//��֤QQ�Ƿ�ͨ����
void WEmailTest::onVerify()
{
	//��ȡ��������
	get_otherConf();

	if (otherCfg.verifyEmail.empty())
	{
		QMessageBox::information(NULL, "δ����", "��֤����δ���ã�����ϵͳ������������֤����");
		return;
	}

	ui.button_verify->setText(QString::fromLocal8Bit("������֤��..."));
	ui.button_verify->setEnabled(false);

	//QFuture < void > future = QtConcurrent::run([&]() {

	phpSendEmail email(phpPath, phpFile, verifyFile, otherCfg.verifyEmail, otherCfg.verifyPasswd, ui.edit_verifyEmail->text().toStdString() + "@qq.com");

	QCoreApplication::processEvents();
	int ret = email.verify();
	QCoreApplication::processEvents();
	if (ret)
	{
		QMessageBox* box = new QMessageBox(
			QMessageBox::Information,
			QString::fromLocal8Bit("�ѿ�ͨ"),
			QString::fromLocal8Bit(("�Է��ѿ�ͨ���� ������Ϣ:" + email.getInf()).c_str()),
			QMessageBox::Ok);
		box->show();
		ui.button_verify->setText(QString::fromLocal8Bit("�������ѿ�ͨ"));
	}
	else
	{
		QMessageBox* box = new QMessageBox(
			QMessageBox::Information,
			QString::fromLocal8Bit("δ��ͨ"),
			QString::fromLocal8Bit(("�Է�δ��ͨ���� ������Ϣ:" + email.getInf()).c_str()),
			QMessageBox::Ok);
		box->show();
		ui.button_verify->setText(QString::fromLocal8Bit("������δ��ͨ"));
	}

	ui.button_verify->setEnabled(true);
	//		});


}

//˫���¼�
void WEmailTest::slotRowDoubleClicked(const QModelIndex& w)
{
	QString buf = w.data().toString();

	//���Ƶ����а�
	QClipboard* board = QApplication::clipboard();
	board->setText(buf);

	//��ʾ����
	ui.label_state->clear();
	ui.label_state->setText(QString::fromLocal8Bit("(�Ѹ��Ƶ����а�)"));

	//��ʱ�����ʾ����
	QFuture < void > future = QtConcurrent::run([&]()
		{
			Sleep(5000);
			ui.label_state->clear();
			ui.label_state->setText(QString::fromLocal8Bit("(˫������)"));
		}
	);

}


//��Ϣ����
void WEmailTest::MsgValue(string& str)
{
	//��ȡ��ǰʱ��
	SYSTEMTIME sys;
	GetLocalTime(&sys);

	char date[20];
	char time[20];
	char Week[20];

	sprintf(date, "%4d��%02d��%02d��", sys.wYear, sys.wMonth, sys.wDay);
	sprintf(time, "%02d:%02d:%02d.%03d", sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	sprintf(Week, "����%d", sys.wDayOfWeek);

	//����
	replace_all_distinct(str, "{����}", date);

	//ʱ��
	replace_all_distinct(str, "{ʱ��}", time);

	//����
	replace_all_distinct(str, "{����}", Week);

	//������QQ����
	replace_all_distinct(str, "{QQ����}", to_string(12345678));

	//Ⱥ����
	replace_all_distinct(str, "{Ⱥ����}", to_string(87654321));

	//������QQ����
	replace_all_distinct(str, "{QQ����}", "�ǳ�");

	//������QQ��Ƭ
	//replace_all_distinct(str, "{Ⱥ��Ƭ}", "��Ƭ");

	//������Ⱥ����
	replace_all_distinct(str, "{Ⱥ����}", "Ⱥ����");


	//����
	//replace_all_distinct(str, "{����}", "����");


	replace_all_distinct(str, "{�Ա�}", "��");

	//����
	replace_all_distinct(str, "{����}", "18");

	//���������
	replace_all_random(str);


}

//�ַ����滻
void WEmailTest::replace_all_distinct(string& str, string old_value, string new_value)
{
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length())
	{
		if ((pos = str.find(old_value, pos)) != string::npos)
		{
			str.replace(pos, old_value.length(), new_value);
		}
		else { break; }
	}
	//return str;
}

//�ַ����滻
void WEmailTest::replace_all_random(string& str)
{
	srand(time(NULL));
	//�������
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{�������}", pos)) != string::npos)
		{
			//�������
			char num = rand() % 10 + 48;
			str.replace(pos, string("{�������}").length(), string(1, num));
		}
		else { break; }
	}

	//�������
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{�������}", pos)) != string::npos)
		{	//�������
			char symbol = rand() % 32 + 1;
			if (symbol <= 15)
			{
				symbol = 15 - symbol;
				symbol += 33;
			}
			else if (symbol <= 22)
			{
				symbol = 22 - symbol;
				symbol += 58;
			}
			else if (symbol <= 28)
			{
				symbol = 28 - symbol;
				symbol += 91;
			}
			else if (symbol <= 32)
			{
				symbol = 32 - symbol;
				symbol += 123;
			}
			else
			{
				symbol = '!';
			}
			str.replace(pos, string("{�������}").length(), string(1, symbol));
		}
		else { break; }
	}

	//�����д��ĸ
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{�����д��ĸ}", pos)) != string::npos)
		{
			//�����д��ĸ
			char capital = rand() % 26 + 65;
			str.replace(pos, string("{�����д��ĸ}").length(), string(1, capital));
		}
		else { break; }
	}

	//���Сд��ĸ
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{���Сд��ĸ}", pos)) != string::npos)
		{
			//���Сд��ĸ
			char lowercase = rand() % 26 + 97;
			str.replace(pos, string("{���Сд��ĸ}").length(), string(1, lowercase));
		}
		else { break; }
	}



	//return str;
}
