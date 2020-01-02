#pragma once
#include <string>
#include <map>

#include "myData.hpp"
#include "json.hpp"

#include "sqlite3.h"

#include <CQLogger.h>

#include "appInf.h"

using namespace std;

//邮箱
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

//单个邮箱限制变量
struct EMAIL_LIMIT
{
	EMAIL_LIMIT()
		:sleep(0)
		, dayNum(0)
	{}

	int dayNum;
	long long sleep;
};

//发送内容
struct CONF_WORD
{
	string name;
	string title;
	string word;
};

//其他配置
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

	//设置类
	bool groupListType;
	bool useHtml;
	bool addFriend;
	bool addGroupInto;
	bool quitGroupSend;
	bool streng;//关键词强力检测

	int smtpSleep;//邮箱发送延时
	int oneQQDayMax;//单个QQ每日发送数量限制
	int oneQQSleep;//单个QQ发送延时

	//在多少秒内最多发送多少封邮件
	int oneGroupTime;
	int oneGroupEmail;

	int keyWordMsgSize;//消息内容最大字数限制

	//秘钥类
	string key;
	string computerId;
	string key_exceedDateTime;

	//统计类
	string conutDate;
	int countDay;
	int countAll;

	//验证邮箱可用性
	string verifyEmail;
	string verifyPasswd;

	//软件是否允许运行
	bool appRun;
};

//单个QQ限制变量
struct QQ_LIMIT
{
	QQ_LIMIT()
		:sleep(0)
		, dayNum(0)
	{}

	int sleep;
	int dayNum;
};

//字符串处理
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

//日志类
class MyLogger : public CQ::Logger
{
public:

	MyLogger(const char* name) :Logger(name)
	{
		m_name = name;


		sqlite3_open("log.db", &m_logdb);

		char* error = NULL;
		sqlite3_exec(m_logdb, "CREATE TABLE log (Time DATETIME,QQId INT (15),GroupId INT (15),Type CHAR (20),Word TEXT);", NULL, NULL, &error);

		//删除原来的数据
		sqlite3_exec(m_logdb, "DELETE FROM log;", NULL, NULL, &error);

	}

	//数据库日志
	void sqlLog(long long GroupId, long long QQId, const char* type, const char* word)
	{

		//删除无用的日志
		delSqlLog();

		//构造sql语句
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
			Info("SQLite操作异常");
		}
	}

	//错误信息处理
	void myError(string type, string error)
	{
		string buf = type + " 原因:" + error;
		Info(buf.c_str());
		sqlLog(0, 0, "系统", buf.c_str());
	}


	//测试
	void testLog(string str)
	{
		// 基于当前系统的当前日期/时间
		time_t now = time(0);

		// 把 now 转换为字符串形式
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

	//重写info
	void Info(string msg)
	{
		this->sqlLog(0, 0, "系统", msg.c_str());
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


//获取机器码
extern bool GetComputerId(std::string& id, std::string& error);


//配置读取
class Conf
{
public:

	//初始化
	static void initConf();

	//秘钥对比
	static void keyFun();

	//更新时间
	static void updataTime();

	//读取统计次数
	static bool read_count();

	//读取全部配置
	static void readConfAll();

	//更新统计次数
	static void updataCount();


	static void wait();

	static void signal();

	//添加监控群
	static void write_groupListadd(long long groupId);

private:

	//初始化全部定时读取
	static void initConfTime();

	//检查更新
	static bool update();

	//初始化群
	static void initGroup();

	//读取关键词
	static void read_keyWord();


	//读取邮箱列表
	static bool read_emailList();


	//读取内容列表
	static bool read_wordList();


	//读取监控群
	static bool read_groupList();


	//读取其他配置
	static bool read_Other();


	static void waitUpdate();

};

//打开界面
class OpenWin
{
public:
	//打开验证秘钥界面
	static void openKeyWin();

	//打开设置窗口
	static bool openWin();

	//打开检查更新界面
	static bool update();


	static void close();

	static void remove();
};

//发送邮箱
class SendEmail
{
public:

	//构造
	SendEmail(long long GroupId, long long QQId, string type) :m_GroupId(GroupId), m_QQId(QQId), m_type(type)
	{}

	//发送邮件
	void send();

public:

	//消息变量
	void MsgValue(std::string& str);

	//字符串替换
	void replace_all_distinct(string& str, string old_value, string new_value);

	//随机数变量替换
	void replace_all_random(string& str);

	//获取发送内容与邮箱
	bool getSendData();

	//判断是否满足条件
	bool isOk();

	//检测接受QQ是否满足条件  接受不大于限制次数  不在未开通QQ邮箱列表中
	bool isQQList();

	bool isGroup();

	//验证邮箱可用性
	bool isVerify();

	//修改统计数量   今发和累发
	void countFinish(string& email, int num);


public:
	long long m_QQId;
	long long m_GroupId;
	string m_type;

	CONF_EMAIL m_smtp;
	CONF_WORD m_word;
};

//关键词监测
class KeyWordMsg
{
public:
	KeyWordMsg(long long fromGroup, long long fromQQ, string msg) :m_fromGroup(fromGroup), m_fromQQ(fromQQ), m_msg(msg)
	{
		m_wmsg = OperateStr::string2wstring(msg);

	}

	//关键词监测
	bool KeyWordFun();

private:
	long long m_fromGroup;
	long long m_fromQQ;
	string m_msg;
	wstring m_wmsg;
};







/****************************************************

					实现部分

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

//配置文件路径
std::string appFile;


/*配置项*/
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

//日志
MyLogger logger("广传引流");

int g_updataConf = 0;


//初始化
void Conf::initConf()
{
	//检查系统更新
	update();

	//读取统计次数
	read_count();

	//读取全部配置
	readConfAll();

	//开启定时读取配置线程
	initConfTime();

	//更新时间
	updataTime();

	//初始化群配置
	initGroup();
}

//秘钥对比
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
		logger.myError("读取其他设置错误", e.what());

		g_otherSet.appRun = false;
	}
	catch (...)
	{
		logger.myError("读取其他设置错误", "未知原因");

		g_otherSet.appRun = false;
	}

	//获取机器码
	string error;
	if (g_otherSet.computerId.empty())
		if (GetComputerId(g_otherSet.computerId, error) == false)
		{
			MessageBoxA(NULL, error.c_str(), "获取机器码错误", MB_OK);
			MessageBoxA(NULL, "请尝试重启酷Q或重启计算机", "获取机器码错误", MB_OK);
			return;
		}

	logger.Info(("机器码:" + g_otherSet.computerId).c_str());


	//检查秘钥是否为空 如果为空开始设置秘钥
	if (g_otherSet.key.empty())
	{
		g_otherSet.appRun = false;

		MessageBox(NULL, L"请设置您的秘钥", L"秘钥为空", MB_OK);

		//打开秘钥设置界面
		OpenWin::openKeyWin();
		return;
	}

	int ret = MySqlKey::keyComp(g_otherSet.key, g_otherSet.key_exceedDateTime, g_otherSet.computerId);

	if (ret == 0)
	{
		logger.Info("秘钥通过");
		g_otherSet.appRun = true;
		return;
	}
	else if (ret == 1)
	{
		g_otherSet.appRun = false;
		MessageBox(NULL, (L"秘钥已过期 到期时间" + OperateStr::string2wstring(g_otherSet.key_exceedDateTime)).c_str(), L"验证失败", MB_OK);
		OpenWin::openKeyWin();
	}
	else if (ret == 2)
	{
		g_otherSet.appRun = false;

		MessageBox(NULL, L"机器码不匹配", L"验证失败", MB_OK);
		OpenWin::openKeyWin();
	}
	else if (ret == 3)
	{
		g_otherSet.appRun = false;
		MessageBox(NULL, L"无效的秘钥", L"验证失败", MB_OK);
		OpenWin::openKeyWin();
	}
	else if (ret == -1)
	{
		g_otherSet.appRun = false;
		MessageBox(NULL, L"秘钥验证异常，请检查网络是否通畅", L"验证失败", MB_OK);
		OpenWin::openKeyWin();
	}

	MessageBox(NULL, L"请重启酷Q 重新验证秘钥", L"重启", MB_OK);
}


//读取所有配置
void Conf::readConfAll()
{
	read_keyWord();
	read_emailList();
	read_wordList();
	read_groupList();
	read_Other();
}


//更新统计信息
void Conf::updataCount()
{
	try
	{
		wait();
		//写入全局统计
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


		//写入邮箱发送次数统计
		//检测是否有这个子
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
		logger.myError("写入统计次数错误", e.what());
		return;
	}
	catch (...)
	{
		logger.myError("写入统计次数错误", "未知原因");
		return;
	}
}


//更新时间
void Conf::updataTime()
{
	//更新时间
	stringstream ss;
	time_t t;
	struct tm* lt;
	time(&t);//获取Unix时间戳。
	lt = localtime(&t);//转为时间结构。
	ss << lt->tm_year + 1900 << "-" << lt->tm_mon + 1 << "-" << lt->tm_mday;

	if (g_otherSet.conutDate != ss.str())
	{
		g_otherSet.conutDate = ss.str();
		g_otherSet.countDay = 0;


		//清除变量中的邮箱次数统计
		for (auto it = g_emailLimit.begin(); it != g_emailLimit.end(); it++)
		{
			it->second.dayNum = 0;
		}

		//清空QQ统计列表
		g_QQList.clear();


		wait();
		//清除json邮箱次数的统计
		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//检测是否有这个子节点 如果有则清空
		auto child_test = value.get_child_optional(L"EmailCountDay");
		if (!child_test)
			value.add_child(L"EmailCountDay", boost::property_tree::wptree(L""));
		else
			child_test.value().clear();

		//检测是否有main节点
		auto child_test2 = value.get_child_optional(L"Main");
		if (!child_test2)
			value.add_child(L"Main", boost::property_tree::wptree(L""));

		//放置今发
		value.put<int>(L"Main.CountDay", 0);
		value.put<wstring>(L"Main.CountDate", OperateStr::string2wstring(g_otherSet.conutDate));

		json::write_json(appFile + "conf.json", value);
		signal();

		logger.sqlLog(0, 0, "系统", ("时间更新为" + g_otherSet.conutDate).c_str());
	}
}

//读取统计次数
bool Conf::read_count()
{
	try
	{
		//读取全局次数统计
		boost::property_tree::wptree value;
		read_json(appFile + "conf.json", value);
		g_otherSet.countDay = value.get<int>(L"Main.CountDay", 0);
		g_otherSet.countAll = value.get<int>(L"Main.CountAll", 0);
		g_otherSet.conutDate = OperateStr::wstring2string(value.get<wstring>(L"Main.CountDate", L""));

		//读取邮箱列表次数
		//检测是否有这个子
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
		logger.myError("读取次数统计错误", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("读取次数统计错误", "未知原因");
		return false;
	}

	return true;
}


//初始化全部定时读取
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

//检查更新
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


//读取关键词
void Conf::read_keyWord()
{
	try
	{
		vector<wstring> temp_keyWord;

		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);


		//读取关键词

		//检测是否有这个子
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

//读取邮箱列表
bool Conf::read_emailList()
{
	try
	{
		myVector<CONF_EMAIL> temp_emailList;

		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//检测是否有这个子
		auto child_test = value.get_child_optional(L"SmtpList");

		if (!child_test)
		{
			value.add_child(L"SmtpList", boost::property_tree::wptree(L""));
		}

		boost::property_tree::wptree child = value.get_child(L"SmtpList");

		for (auto temp : child)
		{
			//获取数据
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
		logger.myError("读取邮箱列表失败", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("读取邮箱列表失败", "未知原因");
		return false;
	}

	return true;
}


//读取内容列表
bool Conf::read_wordList()
{
	try
	{
		myVector<CONF_WORD> temp_wordList;

		boost::property_tree::wptree value;
		json::read_json(appFile + "conf.json", value);

		//检测是否有这个子
		auto child_test = value.get_child_optional(L"WordList");

		if (!child_test)
		{
			value.add_child(L"WordList", boost::property_tree::wptree(L""));
		}

		boost::property_tree::wptree child = value.get_child(L"WordList");

		for (auto temp : child)
		{
			//获取数据
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
		logger.myError("读取内容列表错误", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("读取内容列表错误", "未知原因");
		return false;
	}

	return true;
}


//读取监控群
bool Conf::read_groupList()
{
	try
	{
		json::json2vector_longlong(appFile + "conf.json", L"GroupList", g_groupList);

	}
	catch (exception & e)
	{
		logger.myError("读取内容列表错误", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("读取内容列表错误", "未知原因");
		return false;
	}

	return true;
}


//读取其他配置
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
		logger.myError("读取其他设置错误", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("读取其他设置错误", "未知原因");
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
		logger.myError("读取内容列表错误", e.what());
	}
	catch (...)
	{
		logger.myError("读取内容列表错误", "未知原因");
	}

	signal();
}


//打开验证秘钥界面
void OpenWin::openKeyWin()
{
	try
	{
		string error;

		if (g_otherSet.computerId.empty())
		{
			if (GetComputerId(g_otherSet.computerId, error) == false)
			{
				MessageBoxA(NULL, error.c_str(), "获取机器码错误", MB_OK);
				return;
			}
		}


		boost::property_tree::wptree temp_json;

		//放置文件目录
		temp_json.put<wstring>(L"AppFile", OperateStr::string2wstring(appFile));

		//放置机器码
		temp_json.put<wstring>(L"ComputerId", OperateStr::string2wstring(g_otherSet.computerId));

		//放置key
		temp_json.put<wstring>(L"Key", OperateStr::string2wstring(g_otherSet.key));


		//转换为字符串
		json::write_json("win.tmp", temp_json);

		WinExec("MarketWin.exe MarketKey", SW_SHOW);


	}
	catch (exception & e)
	{
		logger.myError("创建界面数据错误", e.what());
		return;
	}
	catch (...)
	{
		logger.myError("创建界面数据错误", "未知原因");
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

//打开设置窗口
bool OpenWin::openWin()
{
	try
	{
		//获取当前登录的账号
		wstring myQQ = to_wstring(CQ::getLoginQQ());

		//获取机器码
		string error;
		if (g_otherSet.computerId.empty())
		{
			if (GetComputerId(g_otherSet.computerId, error) == false)
			{
				MessageBoxA(NULL, error.c_str(), "获取机器码错误", MB_OK);
				return false;
			}
		}

		//开始json
		boost::property_tree::wptree temp_json;

		//放置文件目录
		temp_json.put<wstring>(L"AppFile", OperateStr::string2wstring(appFile));

		//放置机器码
		temp_json.put<wstring>(L"ComputerId", OperateStr::string2wstring(g_otherSet.computerId));

		//放置key
		temp_json.put<wstring>(L"Key", OperateStr::string2wstring(g_otherSet.key));

		//放置到期时间
		temp_json.put<wstring>(L"ExceedDateTime", OperateStr::string2wstring(g_otherSet.key_exceedDateTime));

		//放置版本号
		temp_json.put<wstring>(L"Version", OperateStr::string2wstring(VERSION));



		//放置邮箱列表
		boost::property_tree::wptree temp_child;
		temp_json.add_child(L"GroupList", boost::property_tree::wptree(L""));
		auto GroupList = CQ::getGroupList();

		for (auto temp : GroupList)
		{
			temp_child.put<wstring>(L"Name", OperateStr::string2wstring(temp.second));

			temp_json.get_child(L"GroupList").push_back(make_pair(to_wstring(temp.first), temp_child));
		}

		//转换为字符串
		json::write_json("win.tmp", temp_json);

		WinExec("MarketWin.exe MarketWin", SW_SHOW);

	}
	catch (exception & e)
	{
		logger.myError("创建界面数据错误", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("创建界面数据错误", "未知原因");
		return false;
	}

	return true;
}

//打开检查更新界面
bool OpenWin::update()
{
	try
	{
		//获取当前登录的账号
		wstring myQQ = to_wstring(CQ::getLoginQQ());

		//开始json
		boost::property_tree::wptree temp_json;

		//放置文件目录
		temp_json.put<wstring>(L"AppFile", OperateStr::string2wstring(appFile));

		//放置版本号
		temp_json.put<wstring>(L"Version", OperateStr::string2wstring(VERSION));


		//转换为字符串
		json::write_json("win.tmp", temp_json);

		WinExec("MarketWin.exe MarketUpdate", SW_SHOW);

	}
	catch (exception & e)
	{
		logger.myError("创建检查更新界面数据错误", e.what());
		return false;
	}
	catch (...)
	{
		logger.myError("创建检查更新界面数据错误", "未知原因");
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


//发送邮件
void SendEmail::send()
{
	if (g_otherSet.groupListType)
	{
		//检查是为过滤
		if (find(g_groupList.begin(), g_groupList.end(), m_GroupId) != g_groupList.end())
		{
			return;
		}
	}
	else
	{
		//检查是为监控群
		if (find(g_groupList.begin(), g_groupList.end(), m_GroupId) == g_groupList.end())
		{
			return;
		}
	}


	logger.testLog("准备发送");
	auto QQInf = CQ::getStrangerInfo(m_QQId, true);
	auto GroupInf = CQ::getGroupList();

	//准备发送
	logger.sqlLog(m_GroupId, m_QQId, m_type.c_str(), (string("QQ名称:") + QQInf.nick + " 群名称:" + GroupInf[m_GroupId] + " 将会发送一封邮件").c_str());


	if (isOk() == false)
	{
		return;
	}

	if (getSendData() == false)
	{
		return;
	}


	//计数加一
	countFinish(m_smtp.email, 1);


	//构造日志字符串
	stringstream log;
	log << "使用邮箱:" << m_smtp.email.c_str() << " 发送内容标题:" << m_word.title.c_str();

	logger.testLog("准备发送2");
	string temp_word(m_word.word);
	string temp_title(m_word.title);
	string temp_name(m_word.name);

	MsgValue(temp_word);
	MsgValue(temp_title);
	MsgValue(temp_name);


	logger.testLog("变量构造完成");


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

		//只取第一行
		for (int i = 0; i < error.size(); i++)
		{
			if (error[i] == '\n')
			{
				error[i] = 0;
				break;
			}
		}

		//计数减一
		countFinish(m_smtp.email, -1);
		logger.sqlLog(m_GroupId, m_QQId, "发送失败", (string("未开通邮箱 ") + error + log.str()).c_str());

		return;
	}

	logger.testLog("邮箱验证完成");
	//发送邮件
	//if (email.SendMail() == false)
	if (email.send() == false)
	{

		string error = email.getInf();
		if (error.empty())
		{
			error = "未知原因";
		}

		//只取第一行
		for (int i = 0; i < error.size(); i++)
		{
			if (error[i] == '\n')
			{
				error[i] = 0;
				break;
			}
		}

		//计数减一
		countFinish(m_smtp.email, -1);
		logger.sqlLog(m_GroupId, m_QQId, "发送失败", (string("发送错误 ") + error + log.str()).c_str());

		return;
	}

	logger.sqlLog(m_GroupId, m_QQId, "发送成功", (log.str() + " 返回信息:" + email.getInf()).c_str());

	logger.testLog("发送完成");
}


//消息变量
void SendEmail::MsgValue(std::string& str)
{
	//获取当前时间
	SYSTEMTIME sys;
	GetLocalTime(&sys);

	char date[20];
	char time[20];
	char Week[20];

	sprintf(date, "%4d年%02d月%02d日", sys.wYear, sys.wMonth, sys.wDay);
	sprintf(time, "%02d:%02d:%02d.%03d", sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	sprintf(Week, "星期%d", sys.wDayOfWeek);

	//日期
	replace_all_distinct(str, "{日期}", date);

	//时间
	replace_all_distinct(str, "{时间}", time);

	//星期
	replace_all_distinct(str, "{星期}", Week);

	//触发的QQ号码
	replace_all_distinct(str, "{QQ号码}", to_string(m_QQId));

	//群号码
	replace_all_distinct(str, "{群号码}", to_string(m_GroupId));


	auto QQInf = CQ::getGroupMemberInfo(m_GroupId, m_QQId, true);
	auto GroupInf = CQ::getGroupList();
	//触发的QQ名称
	replace_all_distinct(str, "{QQ名称}", QQInf.昵称);

	//触发的QQ名片
	replace_all_distinct(str, "{群名片}", QQInf.名片);

	//触发的群名称
	replace_all_distinct(str, "{群名称}", GroupInf[m_GroupId]);

	//地区
	replace_all_distinct(str, "{地区}", QQInf.地区);

	//性别
	string sex;
	if (QQInf.性别 == 0)
		sex = "男";
	else if (QQInf.性别 == 1)
		sex = "女";

	replace_all_distinct(str, "{性别}", sex);

	//年龄
	replace_all_distinct(str, "{年龄}", to_string(QQInf.年龄));

	//随机数变量
	replace_all_random(str);


}

//字符串替换
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


//字符串替换
void SendEmail::replace_all_random(string& str)
{
	srand(time(NULL));
	//随机数字
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{随机数字}", pos)) != string::npos)
		{
			//随机数字
			char num = rand() % 10 + 48;
			str.replace(pos, string("{随机数字}").length(), string(1, num));
		}
		else { break; }
	}

	//随机符号
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{随机符号}", pos)) != string::npos)
		{	//随机符号
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
			str.replace(pos, string("{随机符号}").length(), string(1, symbol));
		}
		else { break; }
	}

	//随机大写字母
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{随机大写字母}", pos)) != string::npos)
		{
			//随机大写字母
			char capital = rand() % 26 + 65;
			str.replace(pos, string("{随机大写字母}").length(), string(1, capital));
		}
		else { break; }
	}

	//随机小写字母
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = str.find("{随机小写字母}", pos)) != string::npos)
		{
			//随机小写字母
			char lowercase = rand() % 26 + 97;
			str.replace(pos, string("{随机小写字母}").length(), string(1, lowercase));
		}
		else { break; }
	}



	//return str;
}

//获取发送内容与邮箱
bool SendEmail::getSendData()
{
	logger.testLog("开始获取内容");
	//更新时间
	Conf::updataTime();

	//获取发送邮箱账号
	for (int i = 0; true; ++i)
	{
		if (i > g_emailList.size())
		{
			logger.sqlLog(m_GroupId, m_QQId, "发送失败", "全部邮箱已达到日限");
			return false;
		}

		m_smtp = getEmail();

		if (g_emailLimit[m_smtp.email].dayNum < m_smtp.dayMax || m_smtp.dayMax == 0)
		{
			break;
		}
	}

	logger.testLog("end 获取发送邮箱账号");
	long long smtpSleep = time(NULL);

	if (g_otherSet.smtpSleep > smtpSleep - g_emailLimit[m_smtp.email].sleep)
	{
		logger.sqlLog(m_GroupId, m_QQId, "发送失败", "邮箱账号已达到发送隔间限制");
		return false;
	}

	g_emailLimit[m_smtp.email].sleep = smtpSleep;

	//获取发送邮箱内容
	m_word = getWord();

	logger.testLog("end 获取发送邮箱内容");
	return true;
}

//判断是否满足条件
bool SendEmail::isOk()
{
	//检查邮箱列表和消息列表是否为空
	if (g_emailList.empty() || g_wordList.empty())
	{
		logger.sqlLog(m_GroupId, m_QQId, "发送失败", "邮箱列表或消息内容为空");
		return false;
	}

	//检查接受QQ是否满足发送条件
	if (isQQList() == false)
	{
		return false;
	}

	//检查群是否满足发送条件
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


//检测是否满足群
bool SendEmail::isGroup()
{
	if (g_otherSet.oneGroupEmail != 0 && g_oneGroup[m_GroupId] > g_otherSet.oneGroupEmail)
	{
		string inf;
		inf = "此群在" + to_string(g_otherSet.oneGroupTime) + "秒内发送邮件超过" + to_string(g_otherSet.oneGroupEmail) + "封";

		logger.sqlLog(m_GroupId, m_QQId, "发送失败", inf.c_str());
		return false;
	}

	return true;
}

//检测接受QQ是否满足条件  接受不大于限制次数  不在未开通QQ邮箱列表中
bool SendEmail::isQQList()
{
	long long QQSleep = time(NULL);

	if (g_otherSet.oneQQDayMax != 0 && g_QQList[m_QQId].dayNum > g_otherSet.oneQQDayMax)
	{
		logger.sqlLog(m_GroupId, m_QQId, "发送失败", "此QQ已达到单个QQ发送日限");
		return false;
	}
	if (g_otherSet.oneQQSleep != 0 && g_otherSet.oneQQSleep > QQSleep - g_QQList[m_QQId].sleep)
	{
		logger.sqlLog(m_GroupId, m_QQId, "发送失败", "此QQ未达到单个QQ发送间隔");
		return false;
	}

	g_QQList[m_QQId].dayNum += 1;
	g_QQList[m_QQId].sleep = QQSleep;
	return true;
}

//验证邮箱可用性
bool SendEmail::isVerify()
{
	if (g_otherSet.verifyEmail.empty() || g_otherSet.verifyPasswd.empty())
	{
		logger.sqlLog(m_GroupId, m_QQId, "发送失败", "验证邮箱未设置，请先到系统设置中设置验证邮箱");
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
		logger.sqlLog(m_GroupId, m_QQId, "发送失败", ("邮箱未注册 " + email.getInf()).c_str());
		return false;
	}
	else
	{
		logger.sqlLog(m_GroupId, m_QQId, "发送失败", ("验证邮箱可用性时出现异常 " + email.getInf()).c_str());
		return false;
	}*/


	//return false;
	return true;
}

//修改统计数量   今发和累发
void SendEmail::countFinish(string& email, int num)
{
	char* errmsg;
	//sqlite3_exec(logdb, ConvertAnsiToUtf8(""), NULL, NULL, &errmsg);

	//更新时间
	Conf::updataTime();

	//计数自增
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

	//更新统计次数
	Conf::updataCount();
}

//关键词监测
bool KeyWordMsg::KeyWordFun()
{

	if (g_otherSet.keyWordMsgSize != 0 && m_wmsg.size() > g_otherSet.keyWordMsgSize)
	{
		return false;
	}


	//普通关键词检测
	for (auto KeyWord_one : g_keyWord)
	{
		if (m_wmsg.find(KeyWord_one) != std::wstring::npos)
		{
			logger.testLog("触发普通关键词检测");

			SendEmail a(m_fromGroup, m_fromQQ, "触发关键词");
			a.send();

			return true;
		}
	}

	//强力检测
	if (g_otherSet.streng)
	{

		for (auto KeyWord_one : g_keyWord)
		{
			//记录关键词字数与匹配数
			int temp_num = KeyWord_one.size(), temp_num_find = 0;

			//判断消息和关键词是否为空
			if (KeyWord_one.empty() || m_wmsg.empty())
			{
				return false;
			}

			//开始强力检测   逐个字对比
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


			//触发强力检测后
			if (temp_num_find >= temp_num)
			{
				logger.testLog("触发强力关键词检测");

				SendEmail a(m_fromGroup, m_fromQQ, "触发关键词");
				a.send();
			}
		}
	}
}
