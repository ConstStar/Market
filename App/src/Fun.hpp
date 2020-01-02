#pragma once
#include <string>
#include <map>

#include "myData.hpp"
#include "json.hpp"

#include "sqlite3.h"

#include <CQLogger.h>

#include "appInf.h"

using namespace std;

//����
struct CONF_EMAIL
{
	CONF_EMAIL()
		:dayMax(0)
		, port(25)
		, ssl(false)
	{}


	string id;
	string smtp;
	string email;
	string passwd;
	int port;
	int dayMax;
	bool ssl;
};

//�����������Ʊ���
struct EMAIL_LIMIT
{
	EMAIL_LIMIT()
		:sleep(0)
		, dayNum(0)
	{}

	int dayNum;
	long long sleep;
};

//��������
struct CONF_WORD
{
	string name;
	string title;
	string word;
};

//��������
struct CONF_OTHER
{
	CONF_OTHER()
		:groupListType(false)
		, useHtml(false)
		, addFriend(false)
		, addGroupInto(false)
		, quitGroupSend(false)
		, key("")
		, computerId("")
		, key_exceedDateTime("")
		, conutDate("")
		, countDay(0)
		, countAll(0)
		, verifyEmail("")
		, verifyPasswd("")
		, smtpSleep(0)
		, appRun(false)
		, streng(false)
		, oneQQDayMax(0)
		, oneQQSleep(0)
		, oneGroupTime(0)
		, oneGroupEmail(0)
		, keyWordMsgSize(0)
	{}

	//������
	bool groupListType;
	bool useHtml;
	bool addFriend;
	bool addGroupInto;
	bool quitGroupSend;
	bool streng;//�ؼ���ǿ�����

	int smtpSleep;//���䷢����ʱ
	int oneQQDayMax;//����QQÿ�շ�����������
	int oneQQSleep;//����QQ������ʱ

	//�ڶ���������෢�Ͷ��ٷ��ʼ�
	int oneGroupTime;
	int oneGroupEmail;

	int keyWordMsgSize;//��Ϣ���������������

	//��Կ��
	string key;
	string computerId;
	string key_exceedDateTime;

	//ͳ����
	string conutDate;
	int countDay;
	int countAll;

	//��֤���������
	string verifyEmail;
	string verifyPasswd;

	//����Ƿ���������
	bool appRun;
};

//����QQ���Ʊ���
struct QQ_LIMIT
{
	QQ_LIMIT()
		:sleep(0)
		, dayNum(0)
	{}

	int sleep;
	int dayNum;
};

//�ַ�������
class StrChange
{
public:
	static char* Unicode2Utf8(const char* unicode)
	{
		int len;
		len = WideCharToMultiByte(CP_UTF8, 0, (const wchar_t*)unicode, -1, NULL, 0, NULL, NULL);
		char* szUtf8 = (char*)malloc(len + 1);
		memset(szUtf8, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, (const wchar_t*)unicode, -1, szUtf8, len, NULL, NULL);
		return szUtf8;
	}

	static char* Ansi2Unicode(const char* str)
	{
		int dwUnicodeLen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
		if (!dwUnicodeLen)
		{
			return _strdup(str);
		}
		size_t num = dwUnicodeLen * sizeof(wchar_t);
		wchar_t* pwText = (wchar_t*)malloc(num);
		memset(pwText, 0, num);
		MultiByteToWideChar(CP_ACP, 0, str, -1, pwText, dwUnicodeLen);
		return (char*)pwText;
	}

	static char* ConvertAnsiToUtf8(const char* str)
	{
		char* unicode = Ansi2Unicode(str);
		char* utf8 = Unicode2Utf8(unicode);
		free(unicode);
		return utf8;
	}
};

//��־��
class MyLogger : public CQ::Logger
{
public:

	MyLogger(const char* name) :Logger(name)
	{
		m_name = name;


		sqlite3_open("log.db", &m_logdb);

		char* error = NULL;
		sqlite3_exec(m_logdb, "CREATE TABLE log (Time DATETIME,QQId INT (15),GroupId INT (15),Type CHAR (20),Word TEXT);", NULL, NULL, &error);

		//ɾ��ԭ��������
		sqlite3_exec(m_logdb, "DELETE FROM log;", NULL, NULL, &error);

	}

	//���ݿ���־
	void sqlLog(long long GroupId, long long QQId, const char* type, const char* word)
	{

		//ɾ�����õ���־
		delSqlLog();

		//����sql���
		stringstream ss;
		ss << "INSERT INTO log (Time, QQId, GroupId, Type, Word) VALUES (datetime(CURRENT_TIMESTAMP,'localtime'),'";
		ss << QQId;
		ss << "', '";
		ss << GroupId;
		ss << "','";
		ss << type;
		ss << "','";
		ss << word;
		ss << "');";

		int ret = sqlite3_exec(m_logdb, StrChange::ConvertAnsiToUtf8(ss.str().c_str()), NULL, NULL, &m_error);
		if (ret != SQLITE_OK)
		{
			Info("SQLite�����쳣");
		}
	}

	//������Ϣ����
	void myError(string type, string error)
	{
		string buf = type + " ԭ��:" + error;
		Info(buf.c_str());
		sqlLog(0, 0, "ϵͳ", buf.c_str());
	}


	//����
	void testLog(string str)
	{
		// ���ڵ�ǰϵͳ�ĵ�ǰ����/ʱ��
		time_t now = time(0);

		// �� now ת��Ϊ�ַ�����ʽ
		char* dt = ctime(&now);

		ofstream file;
		size_t srcSize = 0;

		ifstream fsRead("test.log", ios::in | ios::binary);
		if (fsRead.good())
		{
			fsRead.seekg(0, fsRead.end);
			srcSize = fsRead.tellg();
			fsRead.close();
		}

		if (srcSize > 20480)
		{
			file.open("test.log", ios::out);
		}
		else
		{
			file.open("test.log", ios::app);
		}


		if (file.good())
		{
			file << dt;
			file << str << endl << endl;
			file.close();
		}
	}

	//��дinfo
	void Info(string msg)
	{
		this->sqlLog(0, 0, "ϵͳ", msg.c_str());
		Logger::Info(msg);
	}

	void delSqlLog()
	{
		sqlite3_exec(m_logdb, "DELETE FROM log WHERE time < datetime('now','start of day','0 day');", NULL, NULL, &m_error);
	}

	string getSqlLogError()
	{
		if (m_error == NULL)
		{
			return "NULL";
		}

		return m_error;
	}

	~MyLogger()
	{
		sqlite3_close(m_logdb);
	}

private:
	string m_name;
	sqlite3* m_logdb;
	char* m_error;
};


//��ȡ������
extern bool GetComputerId(std::string& id, std::string& error);


//���ö�ȡ
class Conf
{
public:

	//��ʼ��
	static void initConf();

	//��Կ�Ա�
	static void keyFun();

	//����ʱ��
	static void updataTime();

	//��ȡͳ�ƴ���
	static bool read_count();

	//��ȡȫ������
	static void readConfAll();

	//����ͳ�ƴ���
	static void updataCount();


	static void wait();

	static void signal();

	//��Ӽ��Ⱥ
	static void write_groupListadd(long long groupId);

private:

	//��ʼ��ȫ����ʱ��ȡ
	static void initConfTime();

	//������
	static bool update();

	//��ʼ��Ⱥ
	static void initGroup();

	//��ȡ�ؼ���
	static void read_keyWord();


	//��ȡ�����б�
	static bool read_emailList();


	//��ȡ�����б�
	static bool read_wordList();


	//��ȡ���Ⱥ
	static bool read_groupList();


	//��ȡ��������
	static bool read_Other();


	static void waitUpdate();

};

//�򿪽���
class OpenWin
{
public:
	//����֤��Կ����
	static void openKeyWin();

	//�����ô���
	static bool openWin();

	//�򿪼����½���
	static bool update();


	static void close();

	static void remove();
};

//��������
class SendEmail
{
public:

	//����
	SendEmail(long long GroupId, long long QQId, string type) :m_GroupId(GroupId), m_QQId(QQId), m_type(type)
	{}

	//�����ʼ�
	void send();

public:

	//��Ϣ����
	void MsgValue(std::string& str);

	//�ַ����滻
	void replace_all_distinct(string& str, string old_value, string new_value);

	//����������滻
	void replace_all_random(string& str);

	//��ȡ��������������
	bool getSendData();

	//�ж��Ƿ���������
	bool isOk();

	//������QQ�Ƿ���������  ���ܲ��������ƴ���  ����δ��ͨQQ�����б���
	bool isQQList();

	bool isGroup();

	//��֤���������
	bool isVerify();

	//�޸�ͳ������   �񷢺��۷�
	void countFinish(string& email, int num);


public:
	long long m_QQId;
	long long m_GroupId;
	string m_type;

	CONF_EMAIL m_smtp;
	CONF_WORD m_word;
};

//�ؼ��ʼ��
class KeyWordMsg
{
public:
	KeyWordMsg(long long fromGroup, long long fromQQ, string msg) :m_fromGroup(fromGroup), m_fromQQ(fromQQ), m_msg(msg)
	{
		m_wmsg = OperateStr::string2wstring(msg);

	}

	//�ؼ��ʼ��
	bool KeyWordFun();

private:
	long long m_fromGroup;
	long long m_fromQQ;
	string m_msg;
	wstring m_wmsg;
};







/****************************************************

					ʵ�ֲ���

*****************************************************/




#include "FreeResFile.hpp"
//#include "Email.h"
//#include "SmtpEmail.h"
#include <email/phpSendEmail.hpp>
#include "mysql.hpp"

#include <CQAPI.h>
#include <CQAPI_EX.h>

#include <iostream>
#include <strstream>
#include <sstream>
#include <thread>
#include <tchar.h>

#include <Windows.h>
#include <ShellAPI.h>

using namespace std;

//�����ļ�·��
std::string appFile;


/*������*/
/*****************************************/
CONF_OTHER g_otherSet;
vector<CONF_EMAIL> g_emailList;
vector<CONF_WORD> g_wordList;
vector<long long> g_groupList;
vector<wstring> g_keyWord;

map<std::string, EMAIL_LIMIT> g_emailLimit;
map<long long, QQ_LIMIT> g_QQList;

map<long long, int> g_oneGroup;
/*****************************************/
string phpPath(".\\PHPRun");
string phpFile(".\\PHPRun\\Core\\php.exe");
string sendFile(".\\PHPRun\\Send.php");
string verifyFile(".\\PHPRun\\Verify.php");

//��־
MyLogger logger("�㴫����");

int g_updataConf = 0;


//��ʼ��
void Conf::initConf()
{
	//���ϵͳ����
	update();

	//��ȡͳ�ƴ���
	read_count();

	//��ȡȫ������
	readConfAll();

	//������ʱ��ȡ�����߳�
	initConfTime();

	//����ʱ��
	updataTime();

	//��ʼ��Ⱥ����
	initGroup();
}

//��Կ�Ա�
void Conf::keyFun()
{
	try
	{
		boost::property_tree::wptree value;

		read_json(appFile + "conf.json", value);
		g_otherSet.key = OperateStr::wstring2string(value.get<wstring>(L"Main.Key", L""));

	}
	catch (exception & e)
	{
		logger.myError("��ȡ�������ô���", e.what());

		g_otherSet.appRun = false;
	}
	catch (...)
	{
		logger.myError("��ȡ�������ô���", "δ֪ԭ��");

		g_otherSet.appRun = false;
	}

	//��ȡ������
	string error;
	if (g_otherSet.computerId.empty())
		if (GetComputerId(g_otherSet.computerId, error) == false)
		{
			MessageBoxA(NULL, error.c_str(), "��ȡ���������", MB_OK);
			MessageBoxA(NULL, "�볢��������Q�����������", "��ȡ���������", MB_OK);
			return;
		}

	logger.Info(("������:" + g_otherSet.computerId).c_str());


	//�����Կ�Ƿ�Ϊ�� ���Ϊ�տ�ʼ������Կ
	if (g_otherSet.key.empty())
	{
		g_otherSet.appRun = false;

		MessageBox(NULL, L"������������Կ", L"��ԿΪ��", MB_OK);

		//����Կ���ý���
		OpenWin::openKeyWin();
		return;
	}

	int ret = MySqlKey::keyComp(g_otherSet.key, g_otherSet.key_exceedDateTime, g_otherSet.computerId);

	if (ret == 0)
	{
		logger.Info("��Կͨ��");
		g_otherSet.appRun = true;
		return;
	}
	else if (ret == 1)
	{
		g_otherSet.appRun = false;
		MessageBox(NULL, (L"��Կ�ѹ��� ����ʱ��" + OperateStr::string2wstring(g_otherSet.key_exceedDateTime)).c_str(), L"��֤ʧ��", MB_OK);
		OpenWin::openKeyWin();
	}
	else if (ret == 2)
	{
		g_otherSet.appRun = false;

		MessageBox(NULL, L"�����벻ƥ��", L"��֤ʧ��", MB_OK);
		OpenWin::openKeyWin();
	}
	else if (ret == 3)
	{
		g_otherSet.appRun = false;
		MessageBox(NULL, L"��Ч����Կ", L"��֤ʧ��", MB_OK);
		OpenWin::openKeyWin();
	}
	else if (ret == -1)
	{
		g_otherSet.appRun = false;
		MessageBox(NULL, L"��Կ��֤�쳣�����������Ƿ�ͨ��", L"��֤ʧ��", MB_OK);
		OpenWin::openKeyWin();
	}

	MessageBox(NULL, L"��������Q ������֤��Կ", L"����", MB_OK);
}


//��ȡ��������
void Conf::readConfAll()
{
	read_keyWord();
	read_emailList();
	read_wordList();
	read_groupList();
	read_Other();
}


//����ͳ����Ϣ
void Conf::updataCount()
{
	try
	{
		wait();
		//д��ȫ��ͳ��
		boost::property_tree::wptree value;
		read_json(appFile + "conf.json", value);

		auto child_main = value.get_child_optional(L"Main");

		if (!child_main)
		{
			value.add_child(L"Main", boost::property_tree::wptree(L""));
			child_main = value.get_child_optional(L"Main");
		}


		child_main.value().put<int>(L"CountDay", g_otherSet.countDay);
		child_main.value().put<int>(L"CountAll", g_otherSet.countAll);
		//child_main.value().put<wstring>(L"CountDate", OperateStr::string2wstring(g_otherSet.conutDate));


		//д�����䷢�ʹ���ͳ��
		//����Ƿ��������
		auto child_test = value.get_child_optional(L"EmailCountDay");

		if (!child_test)
		{
			value.add_child(L"EmailCountDay", boost::property_tree::wptree(L""));
		}

		child_test.value().clear();
		boost::property_tree::wptree child_temp;
		for (auto temp : g_emailLimit)
		{
			child_temp.clear();

			child_temp.put<int>(L"DayCount", temp.second.dayNum);

			value.get_child(L"EmailCountDay").push_back(make_pair(OperateStr::string2wstring(temp.first), child_temp));
		}

		json::write_json(appFile + "conf.json", value);
		signal();

	}
	catch (exception & e)
	{
		logger.myError("д��ͳ�ƴ�������", e.what());
		return;
	}
	catch (...)
	{
		logger.myError("д��ͳ�ƴ�������", "δ֪ԭ��");
		return;
	}
}


//����ʱ��
void Conf::updataTime()
{
	//����ʱ��
	stringstream ss;
	time_t t;
	struct tm* lt;
	time(&t);//��ȡUnixʱ�����
	lt = localtime(&t);//תΪʱ��ṹ��
	ss << lt->tm_year + 1900 << "-" << lt->tm_mon + 1 << "-" << lt->tm_mday;

	if (g_otherSet.conutDate != ss.str())
	{
		g_otherSet.conutDate = ss.str();
		g_otherSet.countDay = 0;


		//��������е��������ͳ��
		for (auto it = g_emailLimit.begin(); it != g_emailLimit.end(); it++)
		{
			it->second.dayNum = 0;
		}

		//���QQͳ���б�
		g_QQList.clear();


		wait();
		//���json���������ͳ��
		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//����Ƿ�������ӽڵ� ����������
		auto child_test = value.get_child_optional(L"EmailCountDay");
		if (!child_test)
			value.add_child(L"EmailCountDay", boost::property_tree::wptree(L""));
		else
			child_test.value().clear();

		//����Ƿ���main�ڵ�
		auto child_test2 = value.get_child_optional(L"Main");
		if (!child_test2)
			value.add_child(L"Main", boost::property_tree::wptree(L""));

		//���ý�
		value.put<int>(L"Main.CountDay", 0);
		value.put<wstring>(L"Main.CountDate", OperateStr::string2wstring(g_otherSet.conutDate));

		json::write_json(appFile + "conf.json", value);
		signal();

		logger.sqlLog(0, 0, "ϵͳ", ("ʱ�����Ϊ" + g_otherSet.conutDate).c_str());
	}
}

//��ȡͳ�ƴ���
bool Conf::read_count()
{
	try
	{
		//��ȡȫ�ִ���ͳ��
		boost::property_tree::wptree value;
		read_json(appFile + "conf.json", value);
		g_otherSet.countDay = value.get<int>(L"Main.CountDay", 0);
		g_otherSet.countAll = value.get<int>(L"Main.CountAll", 0);
		g_otherSet.conutDate = OperateStr::wstring2string(value.get<wstring>(L"Main.CountDate", L""));

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
			g_emailLimit[email].dayNum = temp.second.get<int>(L"DayCount", 0);
		}

	}
	catch (exception & e)
	{
		logger.myError("��ȡ����ͳ�ƴ���", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("��ȡ����ͳ�ƴ���", "δ֪ԭ��");
		return false;
	}

	return true;
}


//��ʼ��ȫ����ʱ��ȡ
void Conf::initConfTime()
{
	thread* pKeyWord = new thread([]
		{
			while (true)
			{
				waitUpdate();
				wait();

				read_keyWord();
				read_emailList();
				read_wordList();
				read_groupList();
				read_Other();

				signal();
			}
		}
	);

	pKeyWord->detach();
}

void Conf::initGroup()
{
	auto ph = new std::thread([]
		{
			while (true)
			{
				if (g_otherSet.oneGroupTime)
				{
					g_oneGroup.clear();
				}

				Sleep(g_otherSet.oneGroupTime * 1000);
			}

		});

}

//������
bool Conf::update()
{
	thread* ph = new thread(OpenWin::update);

	return true;
}


void Conf::wait()
{
	while (g_updataConf < 0)
	{
		Sleep(10);
	}
	g_updataConf--;
}

void Conf::signal()
{
	g_updataConf++;
}

void Conf::waitUpdate()
{
	while (true)
	{
		ifstream file(appFile + "update.tmp", ios::in);
		if (file.is_open())
		{
			file.close();
			remove((appFile + "update.tmp").c_str());
			break;
		}

		Sleep(1000 * 3);
	}
}


//��ȡ�ؼ���
void Conf::read_keyWord()
{
	try
	{
		vector<wstring> temp_keyWord;

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
			temp_keyWord.push_back(temp.second.data());
		}

		g_keyWord = temp_keyWord;
	}
	catch (...)
	{
		return;
	}
}

//��ȡ�����б�
bool Conf::read_emailList()
{
	try
	{
		myVector<CONF_EMAIL> temp_emailList;

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
			bool s = temp.second.get<bool>(L"Switch", false);
			if (s)
			{
				CONF_EMAIL temp_email;

				temp_email.id = OperateStr::wstring2string(temp.first);

				temp_email.smtp = OperateStr::wstring2string(temp.second.get<std::wstring>(L"Smtp"));
				temp_email.email = OperateStr::wstring2string(temp.second.get<std::wstring>(L"Email"));
				temp_email.passwd = OperateStr::wstring2string(temp.second.get<std::wstring>(L"Passwd"));

				temp_email.port = temp.second.get<int>(L"Port");
				temp_email.dayMax = temp.second.get<int>(L"DayMax");
				temp_email.ssl = temp.second.get<bool>(L"SSL", false);

				temp_emailList.push_back(temp_email);
			}
		}

		g_emailList = temp_emailList;
	}
	catch (exception & e)
	{
		logger.myError("��ȡ�����б�ʧ��", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("��ȡ�����б�ʧ��", "δ֪ԭ��");
		return false;
	}

	return true;
}


//��ȡ�����б�
bool Conf::read_wordList()
{
	try
	{
		myVector<CONF_WORD> temp_wordList;

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
			if (s)
			{
				CONF_WORD temp_word;
				temp_word.name = OperateStr::wstring2string(temp.second.get<std::wstring>(L"Name"));
				temp_word.title = OperateStr::wstring2string(temp.second.get<std::wstring>(L"Title"));
				temp_word.word = OperateStr::wstring2string(temp.second.get<std::wstring>(L"Word"));
				//QString file_temp(QString::fromStdWString(temp.second.get<std::wstring>(L"File").c_str()));

				temp_wordList.push_back(temp_word);
			}
		}
		g_wordList = temp_wordList;
	}
	catch (exception & e)
	{
		logger.myError("��ȡ�����б����", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("��ȡ�����б����", "δ֪ԭ��");
		return false;
	}

	return true;
}


//��ȡ���Ⱥ
bool Conf::read_groupList()
{
	try
	{
		json::json2vector_longlong(appFile + "conf.json", L"GroupList", g_groupList);

	}
	catch (exception & e)
	{
		logger.myError("��ȡ�����б����", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("��ȡ�����б����", "δ֪ԭ��");
		return false;
	}

	return true;
}


//��ȡ��������
bool Conf::read_Other()
{
	try
	{
		boost::property_tree::wptree value;

		read_json(appFile + "conf.json", value);
		g_otherSet.groupListType = value.get<bool>(L"Main.GroupListType", false);
		g_otherSet.useHtml = value.get<bool>(L"Main.UseHtml", false);
		g_otherSet.addFriend = value.get<bool>(L"Main.AddFriend", false);
		g_otherSet.addGroupInto = value.get<bool>(L"Main.AddGroupInto", false);
		g_otherSet.quitGroupSend = value.get<bool>(L"Main.QuitGroupSend", false);
		g_otherSet.streng = value.get<bool>(L"Main.Streng", false);

		g_otherSet.smtpSleep = value.get<int>(L"Main.SmtpSleep", 0);
		g_otherSet.oneQQDayMax = value.get<int>(L"Main.OneQQDayMax", 0);
		g_otherSet.oneQQSleep = value.get<int>(L"Main.OneQQSleep", 0);


		g_otherSet.oneGroupTime = value.get<int>(L"Main.OneGroupTime", 0);
		g_otherSet.oneGroupEmail = value.get<int>(L"Main.OneGroupEmail", 0);

		g_otherSet.keyWordMsgSize = value.get<int>(L"Main.KeyWordMsgSize", 0);


		g_otherSet.verifyEmail = OperateStr::wstring2string(value.get<wstring>(L"Main.VerifyEmail", L""));
		g_otherSet.verifyPasswd = OperateStr::wstring2string(value.get<wstring>(L"Main.VerifyPasswd", L""));

	}
	catch (exception & e)
	{
		logger.myError("��ȡ�������ô���", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("��ȡ�������ô���", "δ֪ԭ��");
		return false;
	}

	return true;
}


void Conf::write_groupListadd(long long groupId)
{
	wait();
	try
	{
		g_groupList.push_back(groupId);
		json::vector2json_longlong(appFile + "conf.json", L"GroupList", g_groupList);
	}
	catch (exception & e)
	{
		logger.myError("��ȡ�����б����", e.what());
	}
	catch (...)
	{
		logger.myError("��ȡ�����б����", "δ֪ԭ��");
	}

	signal();
}


//����֤��Կ����
void OpenWin::openKeyWin()
{
	try
	{
		string error;

		if (g_otherSet.computerId.empty())
		{
			if (GetComputerId(g_otherSet.computerId, error) == false)
			{
				MessageBoxA(NULL, error.c_str(), "��ȡ���������", MB_OK);
				return;
			}
		}


		boost::property_tree::wptree temp_json;

		//�����ļ�Ŀ¼
		temp_json.put<wstring>(L"AppFile", OperateStr::string2wstring(appFile));

		//���û�����
		temp_json.put<wstring>(L"ComputerId", OperateStr::string2wstring(g_otherSet.computerId));

		//����key
		temp_json.put<wstring>(L"Key", OperateStr::string2wstring(g_otherSet.key));


		//ת��Ϊ�ַ���
		json::write_json("win.tmp", temp_json);

		WinExec("MarketWin.exe MarketKey", SW_SHOW);


	}
	catch (exception & e)
	{
		logger.myError("�����������ݴ���", e.what());
		return;
	}
	catch (...)
	{
		logger.myError("�����������ݴ���", "δ֪ԭ��");
		return;
	}

}

void OpenWin::close()
{
	fstream file("closeWin.tmp", ios::out);
	file.close();

	auto ph = new std::thread([]
		{
			Sleep(1000);
			remove();
		});
}

void OpenWin::remove()
{
	::remove("closeWin.tmp");
}

//�����ô���
bool OpenWin::openWin()
{
	try
	{
		//��ȡ��ǰ��¼���˺�
		wstring myQQ = to_wstring(CQ::getLoginQQ());

		//��ȡ������
		string error;
		if (g_otherSet.computerId.empty())
		{
			if (GetComputerId(g_otherSet.computerId, error) == false)
			{
				MessageBoxA(NULL, error.c_str(), "��ȡ���������", MB_OK);
				return false;
			}
		}

		//��ʼjson
		boost::property_tree::wptree temp_json;

		//�����ļ�Ŀ¼
		temp_json.put<wstring>(L"AppFile", OperateStr::string2wstring(appFile));

		//���û�����
		temp_json.put<wstring>(L"ComputerId", OperateStr::string2wstring(g_otherSet.computerId));

		//����key
		temp_json.put<wstring>(L"Key", OperateStr::string2wstring(g_otherSet.key));

		//���õ���ʱ��
		temp_json.put<wstring>(L"ExceedDateTime", OperateStr::string2wstring(g_otherSet.key_exceedDateTime));

		//���ð汾��
		temp_json.put<wstring>(L"Version", OperateStr::string2wstring(VERSION));



		//���������б�
		boost::property_tree::wptree temp_child;
		temp_json.add_child(L"GroupList", boost::property_tree::wptree(L""));
		auto GroupList = CQ::getGroupList();

		for (auto temp : GroupList)
		{
			temp_child.put<wstring>(L"Name", OperateStr::string2wstring(temp.second));

			temp_json.get_child(L"GroupList").push_back(make_pair(to_wstring(temp.first), temp_child));
		}

		//ת��Ϊ�ַ���
		json::write_json("win.tmp", temp_json);

		WinExec("MarketWin.exe MarketWin", SW_SHOW);

	}
	catch (exception & e)
	{
		logger.myError("�����������ݴ���", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("�����������ݴ���", "δ֪ԭ��");
		return false;
	}

	return true;
}

//�򿪼����½���
bool OpenWin::update()
{
	try
	{
		//��ȡ��ǰ��¼���˺�
		wstring myQQ = to_wstring(CQ::getLoginQQ());

		//��ʼjson
		boost::property_tree::wptree temp_json;

		//�����ļ�Ŀ¼
		temp_json.put<wstring>(L"AppFile", OperateStr::string2wstring(appFile));

		//���ð汾��
		temp_json.put<wstring>(L"Version", OperateStr::string2wstring(VERSION));


		//ת��Ϊ�ַ���
		json::write_json("win.tmp", temp_json);

		WinExec("MarketWin.exe MarketUpdate", SW_SHOW);

	}
	catch (exception & e)
	{
		logger.myError("���������½������ݴ���", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("���������½������ݴ���", "δ֪ԭ��");
		return false;
	}

	return true;
}



CONF_EMAIL getEmail()
{
	static int index;

	index++;
	if (index >= g_emailList.size())
	{
		index = 0;
	}

	return g_emailList.at(index);

}

CONF_WORD getWord()
{
	static int index;


	index++;
	if (index >= g_wordList.size())
	{
		index = 0;
	}

	return g_wordList.at(index);

}


//�����ʼ�
void SendEmail::send()
{
	if (g_otherSet.groupListType)
	{
		//�����Ϊ����
		if (find(g_groupList.begin(), g_groupList.end(), m_GroupId) != g_groupList.end())
		{
			return;
		}
	}
	else
	{
		//�����Ϊ���Ⱥ
		if (find(g_groupList.begin(), g_groupList.end(), m_GroupId) == g_groupList.end())
		{
			return;
		}
	}


	logger.testLog("׼������");
	auto QQInf = CQ::getStrangerInfo(m_QQId, true);
	auto GroupInf = CQ::getGroupList();

	//׼������
	logger.sqlLog(m_GroupId, m_QQId, m_type.c_str(), (string("QQ����:") + QQInf.nick + " Ⱥ����:" + GroupInf[m_GroupId] + " ���ᷢ��һ���ʼ�").c_str());


	if (isOk() == false)
	{
		return;
	}

	if (getSendData() == false)
	{
		return;
	}


	//������һ
	countFinish(m_smtp.email, 1);


	//������־�ַ���
	stringstream log;
	log << "ʹ������:" << m_smtp.email.c_str() << " �������ݱ���:" << m_word.title.c_str();

	logger.testLog("׼������2");
	string temp_word(m_word.word);
	string temp_title(m_word.title);
	string temp_name(m_word.name);

	MsgValue(temp_word);
	MsgValue(temp_title);
	MsgValue(temp_name);


	logger.testLog("�����������");


	phpSendEmail email
	(
		phpPath,
		phpFile,
		sendFile,
		verifyFile,
		g_otherSet.verifyEmail,
		g_otherSet.verifyPasswd,
		m_smtp.smtp,
		m_smtp.ssl,
		to_string(m_smtp.port),
		m_smtp.email,
		m_smtp.passwd,
		g_otherSet.useHtml,
		to_string(m_QQId) + "@qq.com",
		temp_name,
		temp_title,
		temp_word
	);

	if (email.verify() == false)
	{
		string error = email.getInf();

		//ֻȡ��һ��
		for (int i = 0; i < error.size(); i++)
		{
			if (error[i] == '\n')
			{
				error[i] = 0;
				break;
			}
		}

		//������һ
		countFinish(m_smtp.email, -1);
		logger.sqlLog(m_GroupId, m_QQId, "����ʧ��", (string("δ��ͨ���� ") + error + log.str()).c_str());

		return;
	}

	logger.testLog("������֤���");
	//�����ʼ�
	//if (email.SendMail() == false)
	if (email.send() == false)
	{

		string error = email.getInf();
		if (error.empty())
		{
			error = "δ֪ԭ��";
		}

		//ֻȡ��һ��
		for (int i = 0; i < error.size(); i++)
		{
			if (error[i] == '\n')
			{
				error[i] = 0;
				break;
			}
		}

		//������һ
		countFinish(m_smtp.email, -1);
		logger.sqlLog(m_GroupId, m_QQId, "����ʧ��", (string("���ʹ��� ") + error + log.str()).c_str());

		return;
	}

	logger.sqlLog(m_GroupId, m_QQId, "���ͳɹ�", (log.str() + " ������Ϣ:" + email.getInf()).c_str());

	logger.testLog("�������");
}


//��Ϣ����
void SendEmail::MsgValue(std::string& str)
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
	replace_all_distinct(str, "{QQ����}", to_string(m_QQId));

	//Ⱥ����
	replace_all_distinct(str, "{Ⱥ����}", to_string(m_GroupId));


	auto QQInf = CQ::getGroupMemberInfo(m_GroupId, m_QQId, true);
	auto GroupInf = CQ::getGroupList();
	//������QQ����
	replace_all_distinct(str, "{QQ����}", QQInf.�ǳ�);

	//������QQ��Ƭ
	replace_all_distinct(str, "{Ⱥ��Ƭ}", QQInf.��Ƭ);

	//������Ⱥ����
	replace_all_distinct(str, "{Ⱥ����}", GroupInf[m_GroupId]);

	//����
	replace_all_distinct(str, "{����}", QQInf.����);

	//�Ա�
	string sex;
	if (QQInf.�Ա� == 0)
		sex = "��";
	else if (QQInf.�Ա� == 1)
		sex = "Ů";

	replace_all_distinct(str, "{�Ա�}", sex);

	//����
	replace_all_distinct(str, "{����}", to_string(QQInf.����));

	//���������
	replace_all_random(str);


}

//�ַ����滻
void SendEmail::replace_all_distinct(string& str, string old_value, string new_value)
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
void SendEmail::replace_all_random(string& str)
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

//��ȡ��������������
bool SendEmail::getSendData()
{
	logger.testLog("��ʼ��ȡ����");
	//����ʱ��
	Conf::updataTime();

	//��ȡ���������˺�
	for (int i = 0; true; ++i)
	{
		if (i > g_emailList.size())
		{
			logger.sqlLog(m_GroupId, m_QQId, "����ʧ��", "ȫ�������Ѵﵽ����");
			return false;
		}

		m_smtp = getEmail();

		if (g_emailLimit[m_smtp.email].dayNum < m_smtp.dayMax || m_smtp.dayMax == 0)
		{
			break;
		}
	}

	logger.testLog("end ��ȡ���������˺�");
	long long smtpSleep = time(NULL);

	if (g_otherSet.smtpSleep > smtpSleep - g_emailLimit[m_smtp.email].sleep)
	{
		logger.sqlLog(m_GroupId, m_QQId, "����ʧ��", "�����˺��Ѵﵽ���͸�������");
		return false;
	}

	g_emailLimit[m_smtp.email].sleep = smtpSleep;

	//��ȡ������������
	m_word = getWord();

	logger.testLog("end ��ȡ������������");
	return true;
}

//�ж��Ƿ���������
bool SendEmail::isOk()
{
	//��������б����Ϣ�б��Ƿ�Ϊ��
	if (g_emailList.empty() || g_wordList.empty())
	{
		logger.sqlLog(m_GroupId, m_QQId, "����ʧ��", "�����б����Ϣ����Ϊ��");
		return false;
	}

	//������QQ�Ƿ����㷢������
	if (isQQList() == false)
	{
		return false;
	}

	//���Ⱥ�Ƿ����㷢������
	if (isGroup() == false)
	{
		return false;
	}

	if (isVerify() == false)
	{
		return false;
	}

	return true;
}


//����Ƿ�����Ⱥ
bool SendEmail::isGroup()
{
	if (g_otherSet.oneGroupEmail != 0 && g_oneGroup[m_GroupId] > g_otherSet.oneGroupEmail)
	{
		string inf;
		inf = "��Ⱥ��" + to_string(g_otherSet.oneGroupTime) + "���ڷ����ʼ�����" + to_string(g_otherSet.oneGroupEmail) + "��";

		logger.sqlLog(m_GroupId, m_QQId, "����ʧ��", inf.c_str());
		return false;
	}

	return true;
}

//������QQ�Ƿ���������  ���ܲ��������ƴ���  ����δ��ͨQQ�����б���
bool SendEmail::isQQList()
{
	long long QQSleep = time(NULL);

	if (g_otherSet.oneQQDayMax != 0 && g_QQList[m_QQId].dayNum > g_otherSet.oneQQDayMax)
	{
		logger.sqlLog(m_GroupId, m_QQId, "����ʧ��", "��QQ�Ѵﵽ����QQ��������");
		return false;
	}
	if (g_otherSet.oneQQSleep != 0 && g_otherSet.oneQQSleep > QQSleep - g_QQList[m_QQId].sleep)
	{
		logger.sqlLog(m_GroupId, m_QQId, "����ʧ��", "��QQδ�ﵽ����QQ���ͼ��");
		return false;
	}

	g_QQList[m_QQId].dayNum += 1;
	g_QQList[m_QQId].sleep = QQSleep;
	return true;
}

//��֤���������
bool SendEmail::isVerify()
{
	if (g_otherSet.verifyEmail.empty() || g_otherSet.verifyPasswd.empty())
	{
		logger.sqlLog(m_GroupId, m_QQId, "����ʧ��", "��֤����δ���ã����ȵ�ϵͳ������������֤����");
		return false;
	}

	/*Csmtp email(25, "smtp.qq.com", g_otherSet.verifyEmail, g_otherSet.verifyPasswd, "verify");
	email.setTarget(to_string(m_QQId) + "@qq.com");

	int ret = email.verify();

	if (ret == 0)
	{
		return true;
	}
	else if (ret == 1)
	{
		logger.sqlLog(m_GroupId, m_QQId, "����ʧ��", ("����δע�� " + email.getInf()).c_str());
		return false;
	}
	else
	{
		logger.sqlLog(m_GroupId, m_QQId, "����ʧ��", ("��֤���������ʱ�����쳣 " + email.getInf()).c_str());
		return false;
	}*/


	//return false;
	return true;
}

//�޸�ͳ������   �񷢺��۷�
void SendEmail::countFinish(string& email, int num)
{
	char* errmsg;
	//sqlite3_exec(logdb, ConvertAnsiToUtf8(""), NULL, NULL, &errmsg);

	//����ʱ��
	Conf::updataTime();

	//��������
	g_otherSet.countDay += num;
	g_otherSet.countAll += num;
	g_emailLimit[email].dayNum += num;
	g_oneGroup[m_GroupId] += num;

	if (g_otherSet.countDay < 0)
	{
		g_otherSet.countDay = 0;
	}

	if (g_emailLimit[email].dayNum < 0)
	{
		g_emailLimit[email].dayNum = 0;
	}

	//����ͳ�ƴ���
	Conf::updataCount();
}

//�ؼ��ʼ��
bool KeyWordMsg::KeyWordFun()
{

	if (g_otherSet.keyWordMsgSize != 0 && m_wmsg.size() > g_otherSet.keyWordMsgSize)
	{
		return false;
	}


	//��ͨ�ؼ��ʼ��
	for (auto KeyWord_one : g_keyWord)
	{
		if (m_wmsg.find(KeyWord_one) != std::wstring::npos)
		{
			logger.testLog("������ͨ�ؼ��ʼ��");

			SendEmail a(m_fromGroup, m_fromQQ, "�����ؼ���");
			a.send();

			return true;
		}
	}

	//ǿ�����
	if (g_otherSet.streng)
	{

		for (auto KeyWord_one : g_keyWord)
		{
			//��¼�ؼ���������ƥ����
			int temp_num = KeyWord_one.size(), temp_num_find = 0;

			//�ж���Ϣ�͹ؼ����Ƿ�Ϊ��
			if (KeyWord_one.empty() || m_wmsg.empty())
			{
				return false;
			}

			//��ʼǿ�����   ����ֶԱ�
			for (auto keyc : KeyWord_one)
			{
				for (auto msgc : m_wmsg)
				{
					if (keyc == msgc)
					{
						temp_num_find++;
						break;
					}
				}
			}


			//����ǿ������
			if (temp_num_find >= temp_num)
			{
				logger.testLog("����ǿ���ؼ��ʼ��");

				SendEmail a(m_fromGroup, m_fromQQ, "�����ؼ���");
				a.send();
			}
		}
	}
}
