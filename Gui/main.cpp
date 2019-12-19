#include "MarketWin.h"
#include "MarketKey.h"
#include "MarketUpdate.h"

#include <QtWidgets/QApplication>
#include <qmessagebox.h>
#include <qstylefactory.h>
#include <qfile.h>

#include "json.hpp"

#include <sstream>
#include <string>
#include <map>

using namespace std;

bool get_mainData(wstring strMapName);
bool get_keyData();
bool get_Update(wstring strMapName);


string appFile="D:\\用户文档\\桌面\\桌面整理\\酷Q\\data\\app\\cn.xiaoxiaoge.Market\\";
map<long long, wstring> WinGroupList;

string local_computer;
string version;
string key;
string exceedDateTime;

int main(int argc, char* argv[])
{

	QApplication::setStyle(QStyleFactory::create("Fusion"));

	QApplication a(argc, argv);
	QFile qss(":/moren.qss");
	qss.open(QFile::ReadOnly);
	a.setStyleSheet(qss.readAll());
	qss.close();

#ifndef _DEBUG


	if (argc < 2)
	{
		return -1;
	}

	if (!strcmp(argv[1], "MarketWin"))
	{

		if (get_mainData(L"MarketWin") == false)
			return 0;

#endif // 0

		MarketWin w;
		w.show();

		return a.exec();
#ifndef _DEBUG



	}
	else if (!strcmp(argv[1], "MarketKey"))
	{
		if (!get_keyData())
		{
			exit(0);
		}

		MarketKey w;
		w.show();

		return a.exec();

	}
	else if (!strcmp(argv[1], "MarketUpdate"))
	{

		if (get_Update(L"MarketUpdate") == false)
		{
			exit(0);
		}
		MarketUpdate w;
		w.runApp();

		return a.exec();

	}
	return -2;
#endif // 0
}

//读取文件全部内容
string readFileAll(const char* file)
{
	std::ifstream in(file);
	std::ostringstream tmp;
	tmp << in.rdbuf();
	return tmp.str();
}


bool get_mainData(wstring strMapName)
{
	try
	{
#if 0
		string temp_buf;
		string error;

		//读取共享内存
		//wstring strMapName(L"MarketWin");                // 内存映射对象名称
		LPVOID pBuffer;                                    // 共享内存指针

		// 首先试图打开一个命名的内存映射文件对象  
		HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName.c_str());
		if (NULL == hMap)
		{
			throw exception("插件互通内存读取失败");
		}
		else
		{
			//打开成功，映射对象的一个视图，得到指向共享内存的指针，显示出里面的数据
			pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			temp_buf = (const char*)pBuffer;
		}
		::UnmapViewOfFile(pBuffer);
#endif
		string temp_buf = readFileAll("win.tmp");

		remove("./win.tmp");

		boost::property_tree::wptree temp_json;

		//解析json字符串
		wstringstream temp_ss(OperateStr::string2wstring(temp_buf));
		boost::property_tree::read_json(temp_ss, temp_json);

		//读取文件路径
		wstring wAppFile = temp_json.get<wstring>(L"AppFile");
		appFile = OperateStr::wstring2string(wAppFile);

		//读取机器码
		wstring wComputerId = temp_json.get<wstring>(L"ComputerId", L"");
		local_computer = OperateStr::wstring2string(wComputerId);

		//读取key
		wstring wKey = temp_json.get<wstring>(L"Key", L"");
		key = OperateStr::wstring2string(wKey);

		//读取到期时间
		wstring wExceedDateTime = temp_json.get<wstring>(L"ExceedDateTime", L"");
		exceedDateTime = OperateStr::wstring2string(wExceedDateTime);

		//读取版本号
		wstring wVersion = temp_json.get<wstring>(L"Version", L"");
		version = OperateStr::wstring2string(wVersion);


		//读取群列表
		auto groupList_json = temp_json.get_child_optional(L"GroupList");
		if (groupList_json)
		{
			for (auto temp : groupList_json.value())
			{
				wstring id = temp.first.c_str();
				wstring name = temp.second.get<wstring>(L"Name");
				WinGroupList[_wtoll(id.c_str())] = name;
			}

		}

		//监测是否为空
		if (appFile.empty())
		{
			throw exception("数据路径为空");
		}

	}
	catch (exception & e)
	{
		MessageBoxA(NULL, e.what(), "主界面 互通错误", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("互通错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return false;
	}
	catch (...)
	{
		MessageBoxA(NULL, "读取数据异常", "主界面 互通错误", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("互通错误"), QString::fromLocal8Bit("读取数据异常"), QMessageBox::Ok);
		return false;
	}

	return true;
}

bool get_keyData()
{
	try
	{
#if 0
		string temp_buf;
		string error;

		//读取共享内存
		wstring strMapName(L"MarketKey");                // 内存映射对象名称
		LPVOID pBuffer;                                    // 共享内存指针

		// 首先试图打开一个命名的内存映射文件对象  
		HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName.c_str());
		if (NULL == hMap)
		{
			throw exception("插件互通内存读取失败");
		}
		else
		{
			//打开成功，映射对象的一个视图，得到指向共享内存的指针，显示出里面的数据
			pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			temp_buf = (const char*)pBuffer;
		}
		::UnmapViewOfFile(pBuffer);
#endif

		string temp_buf = readFileAll("win.tmp");
		remove("./win.tmp");

		boost::property_tree::wptree temp_json;

		//解析json字符串
		wstringstream temp_ss(OperateStr::string2wstring(temp_buf));
		boost::property_tree::read_json(temp_ss, temp_json);

		//读取文件路径
		wstring wAppFile = temp_json.get<wstring>(L"AppFile", L"");
		appFile = OperateStr::wstring2string(wAppFile);

		//读取机器码
		wstring wComputerId = temp_json.get<wstring>(L"ComputerId", L"");
		local_computer = OperateStr::wstring2string(wComputerId);

		//读取key
		wstring wKey = temp_json.get<wstring>(L"Key", L"");
		key = OperateStr::wstring2string(wKey);


		//监测是否为空
		if (appFile.empty())
		{
			throw exception("数据路径为空");
		}

		//监测是否为空
		if (wComputerId.empty())
		{
			throw exception("数据路径为空");
		}
	}
	catch (exception & e)
	{
		MessageBoxA(NULL, e.what(), "秘钥 互通错误", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("互通错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return false;
	}
	catch (...)
	{
		MessageBoxA(NULL, "读取数据异常", "秘钥 互通错误", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("互通错误"), QString::fromLocal8Bit("读取数据异常"), QMessageBox::Ok);
		return false;
	}

	return true;
}

bool get_Update(wstring strMapName)
{
	try
	{

#if 0
		string temp_buf;
		string error;

		//读取共享内存
		//wstring strMapName(L"MarketWin");                // 内存映射对象名称
		LPVOID pBuffer;                                    // 共享内存指针

		// 首先试图打开一个命名的内存映射文件对象  
		HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName.c_str());
		if (NULL == hMap)
		{
			throw exception("插件互通内存读取失败");
		}
		else
		{
			//打开成功，映射对象的一个视图，得到指向共享内存的指针，显示出里面的数据
			pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			temp_buf = (const char*)pBuffer;
		}
		::UnmapViewOfFile(pBuffer);

#endif

		string temp_buf = readFileAll("win.tmp");
		remove("./win.tmp");


		boost::property_tree::wptree temp_json;

		//解析json字符串
		wstringstream temp_ss(OperateStr::string2wstring(temp_buf));
		boost::property_tree::read_json(temp_ss, temp_json);

		//读取文件路径
		wstring wAppFile = temp_json.get<wstring>(L"AppFile");
		appFile = OperateStr::wstring2string(wAppFile);

		//读取版本号
		wstring wVersion = temp_json.get<wstring>(L"Version", L"");
		version = OperateStr::wstring2string(wVersion);

		//监测是否为空
		if (appFile.empty())
		{
			throw exception("数据路径为空");
		}

	}
	catch (exception & e)
	{
		MessageBoxA(NULL, e.what(), "检查更新 互通错误", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("互通错误"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "错误", MB_OK);
		return false;
	}
	catch (...)
	{
		MessageBoxA(NULL, "读取数据异常", "检查更新 互通错误", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("互通错误"), QString::fromLocal8Bit("读取数据异常"), QMessageBox::Ok);
		return false;
	}

	return true;
}