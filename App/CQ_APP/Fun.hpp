#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>

#include <boost/atomic.hpp>

#include <string>
#include <map>

#include <codecvt>

#include <sqlite3/sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <email/phpSendEmail.hpp>
#include <CQSDK.h>

#include "json.hpp"
#include "appVer.h"

#include "Pipe.hpp"


using namespace std;

#define SQLITE_PATHNAME "log.db"

Pipe WinPipe;//界面互通


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
		, isVerifyKey(false)
		, verifyKey("")
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

	bool isVerifyKey;
	string verifyKey;

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

	long long sleep;
	int dayNum;
};



////验证群
//class GroupOk
//{
//	void check(long long groupId)
//	{
//
//
//
//
//	}
//
//
//
//
//};


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
class Mylogger : public CQ::Logger
{
public:

	Mylogger(const char* name) : m_name(name), Logger(name)//, m_db(SQLITE_PATHNAME, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
	{

		//sqlite3* logdb;
		//sqlite3_open("log.db", &m_db);
	/*	if (m_db == NULL)
		{
			Warning("日志数据库打开失败");
		}*/
		//char* error = NULL;

	/*	sqlite3_exec(logdb, "CREATE TABLE log (Time DATETIME,QQId INT (15),GroupId INT (15),Type CHAR (20),Word TEXT);", NULL, NULL, &error);

		if (error != NULL)
		{
			m_error = "日志初始化失败: ";
			m_error += error;
			Warning((m_error).c_str());
		}*/


		//sqlite3_exec(logdb, "DELETE FROM log;", NULL, NULL, &error);
		//sqlite3_close(logdb);
	}

	//数据库日志
	void sqlLog(long long GroupId, long long QQId, const char* type, const char* word)
	{

		//删除无用的日志
		delDaySqlLog();

		string temp_word(word);
		replace_all_distinct(temp_word, "'", "''");
		replace_all_distinct(temp_word, "/", "//");
		replace_all_distinct(temp_word, "[", "/[");
		replace_all_distinct(temp_word, "]", "/]");
		replace_all_distinct(temp_word, "%", "/%");
		replace_all_distinct(temp_word, "&", "/&");
		replace_all_distinct(temp_word, "_", "/_");
		replace_all_distinct(temp_word, "(", "/(");
		replace_all_distinct(temp_word, ")", "/)");


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
		if (temp_word.size() > 150)
		{
			temp_word[150] = 0;
			temp_word += "...(大于150字)";
			//OutputDebugStringA(("#1#" + temp_word).c_str());
		}

		ss << "');";

		sqlExec(ss.str().c_str());

	}

	//错误信息处理
	void myError(string type, string error)
	{
		string buf = type + " 原因:" + error;
		Info(buf.c_str());
		Warning(buf.c_str());
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

		if (srcSize > 40480)
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

	void Warning(string msg)
	{
		Logger::Warning(msg);
	}

	void delDaySqlLog()
	{
		sqlExec("DELETE FROM log WHERE time < datetime('now','start of day','0 day');");
		//sqlite3_exec(m_db, "DELETE FROM log WHERE time < datetime('now','start of day','0 day');", NULL, NULL, &m_error);
		//m_db.exec("DELETE FROM log WHERE time < datetime('now','start of day','0 day');");
	}

	string getError()
	{
		return m_error;
	}

private:
	//执行sql语句
	void sqlExec(const char* sql)
		try
	{
		/*static int count = 0;

		count++;
		if (m_db == NULL)
		{
			testLog(string() + "数据库异常: 数据库已被关闭");
			return;
		}

		bool flag = false;*/

		Logger::Info(sql);
		string buf;
		buf += "\n";
		buf += StrChange::ConvertAnsiToUtf8(sql);
		buf += "\n";

		WinPipe.WriteData(buf);

		//for (int i = 0; i < 30; i++)
		//{

		//	int ret = sqlite3_exec(m_db, StrChange::ConvertAnsiToUtf8(sql), NULL, NULL, &m_error);
		//	if (ret == SQLITE_OK)
		//	{
		//		flag = true;
		//		break;
		//	}
		//	else
		//	{
		//		Sleep(200);
		//	}

		//}

		//if (flag == false)
		//	testLog(string() + "数据库异常: " + ((m_error == NULL) ? "NULL" : m_error));

		//if (count >= 100)
		//{
		//	count = 0;
		//	sqlExec("DELETE FROM log WHERE time < datetime('now','localtime','-10 minute');");
		//}
		//if (count % 20 == 0)
		//{
		//	sqlExec("delete from log where(select count(*) from log) > 200;");
		//}
		//try
		//{
		//	int ret = m_db.exec(ConvertAnsiToUtf8(sql));

		//	if (!ret)
		//	{
		//		m_error = "SQL语句: ";
		//		m_error += sql;
		//		m_error += "\n错误信息: ";
		//		m_error += getSqlError();

		//		//Info("SQLite操作异常");
		//		testLog(("SQLite操作错误 内容:\n" + m_error).c_str());
		//		//OutputDebugStringA(("#2#" + temp_word).c_str());
		//	}
		//}
		//catch (SQLite::Exception & e)
		//{
		//	m_error = "SQL语句: ";
		//	m_error += sql;
		//	m_error += "\n异常信息: ";
		//	m_error += UTF8ToANSI(e.what());
		//	m_error += "\n错误信息: ";
		//	m_error += getSqlError();

		//	testLog(("SQLite操作异常 内容:\n" + m_error).c_str());
		//}
		//catch (...)
		//{
		//	m_error = "SQL语句: ";
		//	m_error += sql;
		//	m_error += "\n异常信息: ";
		//	m_error += "未知";
		//	m_error += "\n错误信息: ";
		//	m_error += getSqlError();

		//	testLog(("SQLite操作异常 内容:\n" + m_error).c_str());
		//}



	}
	catch (PipeException & e)
	{
		m_error = e.what();

		string inf = "数据库错误: ";
		inf += e.what();
		testLog(inf);
	}

	//获取sql错误信息
	string getSqlError()
	{
		//string buf = m_db.getErrorMsg();
		//return UTF8ToANSI(buf);

		return UTF8ToANSI(getError());
	}



	std::wstring UTF8ToUnicode(const std::string& str)
	{
		std::wstring ret;
		try {
			std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
			ret = wcv.from_bytes(str);
		}
		catch (const std::exception & e) {
			//std::cerr << e.what() << std::endl;
		}
		return ret;
	}

	std::string UnicodeToANSI(const std::wstring& wstr)
	{
		string result;
		//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
		int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
		char* buffer = new char[len + 1];
		//宽字节编码转换成多字节编码  
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
		buffer[len] = '\0';
		//删除缓冲区并返回值  
		result.append(buffer);
		delete[] buffer;
		return result;
	}

	std::string UTF8ToANSI(const std::string str)
	{
		return UnicodeToANSI(UTF8ToUnicode(str));
	}



	// 字符串替换
	void replace_all_distinct(string& str, string old_value, string new_value)
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



private:
	string m_name;
	//sqlite3* m_db;
	string m_error;
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
};

//发送邮箱
class SendEmail
{
public:

	//构造
	SendEmail(long long GroupId, long long QQId, string type) :m_GroupId(GroupId), m_QQId(QQId), m_type(type)
	{
	}

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
	bool isVerify(phpSendEmail& email);

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
#include "mysql.hpp"

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
Mylogger logger("懒人引流");

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
		vector<CONF_EMAIL> temp_emailList;

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
		vector<CONF_WORD> temp_wordList;

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

		g_otherSet.isVerifyKey = value.get<bool>(L"Main.IsVerifyKey", false);

		g_otherSet.smtpSleep = value.get<int>(L"Main.SmtpSleep", 0);
		g_otherSet.oneQQDayMax = value.get<int>(L"Main.OneQQDayMax", 0);
		g_otherSet.oneQQSleep = value.get<int>(L"Main.OneQQSleep", 0);


		g_otherSet.oneGroupTime = value.get<int>(L"Main.OneGroupTime", 0);
		g_otherSet.oneGroupEmail = value.get<int>(L"Main.OneGroupEmail", 0);

		g_otherSet.keyWordMsgSize = value.get<int>(L"Main.KeyWordMsgSize", 0);


		g_otherSet.verifyEmail = OperateStr::wstring2string(value.get<wstring>(L"Main.VerifyEmail", L""));
		g_otherSet.verifyPasswd = OperateStr::wstring2string(value.get<wstring>(L"Main.VerifyPasswd", L""));

		g_otherSet.verifyKey = OperateStr::wstring2string(value.get<wstring>(L"Main.VerifyKey", L""));

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
		temp_json.put<wstring>(L"Version", OperateStr::string2wstring(APP_version));



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

		//WinExec("MarketWin.exe MarketWin", SW_SHOW);

		//关闭原来的界面
		string closeWin = "/*close*/";
		WinPipe.WriteData(closeWin);


		WinPipe.initServer(L"MarketWin.exe", L" MarketWin");

	}
	catch (exception & e)
	{
		logger.myError("创建界面数据错误", e.what());
		return false;
	}
	catch (PipeException & e)
	{
		MessageBoxA(NULL, e.what().c_str(), "界面错误", MB_OK);
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
		temp_json.put<wstring>(L"Version", OperateStr::string2wstring(APP_version));


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
try
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


	auto QQInf = CQ::getStrangerInfo(m_QQId);
	auto GroupInf = CQ::getGroupList();


	logger.testLog("准备发送");
	//准备发送
	//logger.sqlLog(m_GroupId, m_QQId, m_type.c_str(), "测试：准备发送");
	logger.sqlLog(m_GroupId, m_QQId, m_type.c_str(), (string("QQ名称:") + QQInf.nick + " 群名称:" + GroupInf[m_GroupId] + " 将会发送一封邮件").c_str());


	if (isOk() == false)
	{
		return;
	}

	if (getSendData() == false)
	{
		return;
	}

	logger.testLog("计数加一");
	//计数加一
	countFinish(m_smtp.email, 1);


	//构造日志字符串
	stringstream log;
	log << "使用邮箱:" << m_smtp.email.c_str() << " 发送内容标题:" << m_word.title.c_str();

	string temp_word(m_word.word);
	string temp_title(m_word.title);
	string temp_name(m_word.name);

	logger.testLog("变量替换");
	MsgValue(temp_word);
	MsgValue(temp_title);
	MsgValue(temp_name);

	logger.testLog("构造发送");
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

	logger.testLog("开始验证");
	if (isVerify(email) == false)
	{
		//计数减一
		countFinish(m_smtp.email, -1);
		return;
	}

	logger.testLog("开始发送");
	//发送邮件
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

	//记录邮箱延时时间
	long long smtpSleep = time(NULL);
	g_emailLimit[m_smtp.email].sleep = smtpSleep;

	logger.testLog("发送成功");
	logger.sqlLog(m_GroupId, m_QQId, "发送成功", (log.str() + " 返回信息:" + email.getInf()).c_str());

}
catch (exception & e)
{
	logger.Info(string("“发送邮件” 出现崩溃已被阻止 原因:") + e.what());
	logger.testLog(string("发送邮件异常 原因: ") + e.what());
}
catch (...)
{
	logger.Info("“发送邮件” 出现崩溃已被阻止 原因:未知");
	logger.testLog("发送邮件异常 原因未知");
}


//消息变量
void SendEmail::MsgValue(std::string& str)
try
{
	//获取当前时间
	SYSTEMTIME sys;
	GetLocalTime(&sys);

	char date[20];
	char time[20];
	char Week[20];

	sprintf(date, "%4d年%02d月%02d日", sys.wYear, sys.wMonth, sys.wDay);
	sprintf(time, "%02d时%02d分%02d秒", sys.wHour, sys.wMinute, sys.wSecond/*sys.wMilliseconds*/);

	switch (sys.wDayOfWeek)
	{
	case 0:sprintf(Week, "星期天"); break;
	case 1:sprintf(Week, "星期一"); break;
	case 2:sprintf(Week, "星期二"); break;
	case 3:sprintf(Week, "星期三"); break;
	case 4:sprintf(Week, "星期四"); break;
	case 5:sprintf(Week, "星期五"); break;
	case 6:sprintf(Week, "星期六"); break;
	default:
		break;
	}
	//sprintf(Week, "星期%d", sys.wDayOfWeek);

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


	/*
		auto memberList = CQ::getGroupMemberList(m_GroupId);
		CQ::GroupMemberInfo QQGroupInf;

		for (auto temp : memberList)
		{
			if (temp.QQID == m_QQId)
			{
				QQGroupInf = temp;
				break;
			}

		}
	*/

	auto QQInf = CQ::getStrangerInfo(m_QQId);
	auto GroupInf = CQ::getGroupList();

	//触发的QQ名称
	replace_all_distinct(str, "{QQ名称}", QQInf.nick);

	//触发的QQ名片
//	replace_all_distinct(str, "{群名片}", QQGroupInf.名片);
	replace_all_distinct(str, "{群名片}", "");

	//触发的群名称
	replace_all_distinct(str, "{群名称}", GroupInf[m_GroupId]);

	//地区
//	replace_all_distinct(str, "{地区}", QQGroupInf.地区);
	replace_all_distinct(str, "{地区}", "");

	//性别
	string sex;
	if (QQInf.sex == 0)
		sex = "男";
	else if (QQInf.sex == 1)
		sex = "女";

	replace_all_distinct(str, "{性别}", sex);

	//年龄
	replace_all_distinct(str, "{年龄}", to_string(QQInf.age));

	//随机数变量
	replace_all_random(str);


}
catch (exception & e)
{
	logger.Info(string("“构造变量” 出现崩溃已被阻止 原因:") + e.what());
	logger.testLog(string("构造变量异常 原因: ") + e.what());
}
catch (...)
{
	logger.Info("“构造变量” 出现崩溃已被阻止 原因:未知");
	logger.testLog("构造变量异常 原因未知");
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

	long long smtpSleep = time(NULL);

	if (g_otherSet.smtpSleep > smtpSleep - g_emailLimit[m_smtp.email].sleep)
	{
		logger.sqlLog(m_GroupId, m_QQId, "发送失败", "邮箱账号已达到发送隔间限制");
		return false;
	}

	//获取发送邮箱内容
	m_word = getWord();

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
bool SendEmail::isVerify(phpSendEmail& email)
{
	if (g_otherSet.isVerifyKey)
	{
		if (g_otherSet.verifyKey.empty())
		{
			logger.sqlLog(m_GroupId, m_QQId, "发送失败", "开启了第三方验证邮箱，但未设置key");
			return false;
		}
		stringstream html;

		/*
		httplib::Client cli("www.mail-verifier.com", 80);

		string tempTarget="/do/api/?key=" + g_otherSet.verifyKey + "&verify=" + to_string(m_QQId) + "@qq.com";
		auto res = cli.Get(tempTarget.c_str());

		if (!res || res->status != 200)
		{
			//出错
			logger.sqlLog(m_GroupId, m_QQId, "发送失败", "第三方验证邮箱时 出现网络异常");
		}
		else
		{

			wstringstream html;
			html << OperateStr::string2wstring(res->body);



		}
		*/


		namespace beast = boost::beast;     // from <boost/beast.hpp>
		namespace http = beast::http;       // from <boost/beast/http.hpp>
		namespace net = boost::asio;        // from <boost/asio.hpp>
		using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>
		try
		{

			auto const host = "www.mail-verifier.com";
			auto const port = "80";


			string tempTarget = "/do/api/?key=" + g_otherSet.verifyKey + "&verify=" + to_string(m_QQId) + "@qq.com";
			//tempTarget = StrChange::Unicode2Utf8(tempTarget.c_str());

			auto const target = tempTarget.c_str();
			int version = 10;//10:11

			// The io_context is required for all I/O
			net::io_context ioc;

			// These objects perform our I/O
			tcp::resolver resolver(ioc);
			beast::tcp_stream stream(ioc);

			// Look up the domain name
			auto const results = resolver.resolve(host, port);

			// Make the connection on the IP address we get from a lookup
			stream.connect(results);

			// Set up an HTTP GET request message
			http::request<http::string_body> req{ http::verb::get, target, version };
			req.set(http::field::host, host);
			req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
			// Send the HTTP request to the remote host
			http::write(stream, req);

			// This buffer is used for reading and must be persisted
			beast::flat_buffer buffer;

			// Declare a container to hold the response
			http::response<http::string_body> res;

			// Receive the HTTP response
			http::read(stream, buffer, res);

			// Write the message to standard out
			//std::cout << res << std::endl;
			html << res.body();

			// Gracefully close the socket
			beast::error_code ec;
			stream.socket().shutdown(tcp::socket::shutdown_both, ec);

			// not_connected happens sometimes
			// so don't bother reporting it.
			//
			if (ec && ec != beast::errc::not_connected)
				throw beast::system_error{ ec };
			if (res.result_int() != 200)
			{
				logger.sqlLog(m_GroupId, m_QQId, "发送失败", ("第三方验证邮箱时 出现网络异常 状态码异常" + to_string(res.result_int())).c_str());
				return false;
			}
			// If we get here then the connection is closed gracefully
		}
		catch (std::exception const& e)
		{
			//std::cerr << "Error: " << e.what() << std::endl;
			logger.sqlLog(m_GroupId, m_QQId, "发送失败", (std::string() + "第三方验证邮箱时 出现网络异常 " + e.what()).c_str());

			return false;
		}

		//验证返回码
		try
		{
			//string json = substring(buf, "window.getTimelineService =", "}catch(e){}");
			boost::property_tree::ptree root;
			boost::property_tree::read_json(html, root);

			int code = root.get<int>("code", -7);
			if (code == 1)
				return true;
			else
			{
				if (code == 0)
					logger.sqlLog(m_GroupId, m_QQId, "发送失败", "验证邮箱 此账号未开通邮箱");
				else if (code == -1)
					logger.sqlLog(m_GroupId, m_QQId, "发送失败", "验证邮箱 并非正确的邮箱格式");
				else if (code == -2)
					logger.sqlLog(m_GroupId, m_QQId, "发送失败", "验证邮箱 链接失败请重试");
				else if (code == -3)
					logger.sqlLog(m_GroupId, m_QQId, "发送失败", "验证邮箱 剩余次数用完了，请及时充值");
				else if (code == -4)
					logger.sqlLog(m_GroupId, m_QQId, "发送失败", "验证邮箱 请求KEY不存在");
				else if (code == -5)
					logger.sqlLog(m_GroupId, m_QQId, "发送失败", "验证邮箱 我们无法确定此电子邮件的状态");
				else if (code == -6)
					logger.sqlLog(m_GroupId, m_QQId, "发送失败", "验证邮箱 超出并发限制");
				else if (code == -7)
					logger.sqlLog(m_GroupId, m_QQId, "发送失败", "验证邮箱 解析json失败");

				return false;
			}
		}
		catch (exception & e)
		{
			logger.sqlLog(m_GroupId, m_QQId, "发送失败", (std::string() + "第三方验证邮箱时 获取第三方数据异常 " + e.what()).c_str());
			logger.testLog("第三方验证json解析异常: " + html.str());
			return false;
		}
		catch (...)
		{
			logger.sqlLog(m_GroupId, m_QQId, "发送失败", "第三方验证邮箱时 获取第三方数据异常 未知原因");
			return false;
		}


		return true;

	}
	else
	{
		if (g_otherSet.verifyEmail.empty() || g_otherSet.verifyPasswd.empty())
		{
			logger.sqlLog(m_GroupId, m_QQId, "发送失败", "验证邮箱未设置，请先到系统设置中设置验证邮箱");
			return false;
		}

		if (email.verify() == false)
		{
			string error = email.getInf();

			//只取第一行
			for (size_t i = 0; i < error.size(); i++)
			{
				if (error[i] == '\n')
				{
					error[i] = 0;
					break;
				}
			}

			//计数减一
			countFinish(m_smtp.email, -1);
			logger.sqlLog(m_GroupId, m_QQId, "发送失败", (string("未开通邮箱 ") + error).c_str());

			return false;
		}

		return true;
	}

	return true;
}

//修改统计数量   今发和累发
void SendEmail::countFinish(string& email, int num)
{
	//char* errmsg;
	//sqlite3_exec(logdb, ConvertAnsiToUtf8(""), NULL, NULL, &errmsg);

	//更新时间
	Conf::updataTime();

	//计数自增
	g_otherSet.countDay += num;
	g_otherSet.countAll += num;
	g_emailLimit[email].dayNum += num;
	g_oneGroup[m_GroupId] += num;

	/*if (g_otherSet.countDay < 0)
	{
		g_otherSet.countDay = 0;
	}

	if (g_emailLimit[email].dayNum < 0)
	{
		g_emailLimit[email].dayNum = 0;
	}*/

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
				SendEmail a(m_fromGroup, m_fromQQ, "触发关键词");
				a.send();
			}
		}
	}


	return true;
}
