#pragma once
#include <Windows.h>

#include "../resource.h"
#include "json.hpp"

#include "appInf.h"

#include <string>
#include <tchar.h>
using namespace std;

extern string appFile;
extern HMODULE g_hModule;


class FreeResFile
{

public:

	//监测开启软件
	static bool oneStart()
	{
		try
		{
			bool one = true;
			boost::property_tree::wptree value;

			//检查是否为第一次启动
			if (json::read_json(appFile + "conf.json", value))
			{
				wstring version;
				version = value.get<wstring>(L"Main.AppVersion", L"");

				if (version == _T(VERSION))
				{
					one = false;
				}


				if (one == false)
				{
					return true;
				}

			}

			//如果为第一次启动
			if (one)
			{
				Sleep(500);
				int ret = freeFileAll();
				if (ret == false)
					return false;


				auto child = value.get_child_optional(L"Main");
				if (!child)
				{
					value.add_child(L"Main", boost::property_tree::wptree(L""));
				}

				value.put<wstring>(L"Main.AppVersion", _T(VERSION));
				json::write_json(appFile + "conf.json", value);
			}
			return true;
		}
		catch (exception & e)
		{
			MessageBoxA(NULL, e.what(), "安装失败", MB_OK);
			return false;
		}
		catch (...)
		{
			MessageBoxA(NULL, "未知异常", "安装失败", MB_OK);
			return false;
		}
	}

	//释放所有文件
	static bool freeFileAll()
	{

		//mysql
		if (myFreeFile(IDR_DLL1, L"DLL", L"bin/libcrypto-1_1.dll") == false)
			return false;

		if (myFreeFile(IDR_DLL2, L"DLL", L"bin/libssl-1_1.dll") == false)
			return false;

		if (myFreeFile(IDR_DLL3, L"DLL", L"bin/mysqlcppconn-7-vs14.dll") == false)
			return false;

		if (myFreeFile(IDR_DLL10, L"DLL", L"bin/MySql.dll") == false)
			return false;

		//curl
		if (myFreeFile(IDR_DLL11, L"DLL", L"bin/libcurl.dll") == false)
			return false;

		//QT
		_wmkdir(L".\\platforms");
		if (myFreeFile(IDR_DLL8, L"DLL", L"platforms/qwindows.dll") == false)
			return false;

		_wmkdir(L".\\sqldrivers");
		if (myFreeFile(IDR_DLL9, L"DLL", L"sqldrivers/qsqlite.dll") == false)
			return false;



		if (myFreeFile(IDR_DLL4, L"DLL", L"bin/Qt5Core.dll") == false)
			return false;

		if (myFreeFile(IDR_DLL5, L"DLL", L"bin/Qt5Gui.dll") == false)
			return false;

		if (myFreeFile(IDR_DLL6, L"DLL", L"bin/Qt5Sql.dll") == false)
			return false;

		if (myFreeFile(IDR_DLL7, L"DLL", L"bin/Qt5Widgets.dll") == false)
			return false;

		//界面
		if (myFreeFile(IDR_EXE1, L"EXE", L"MarketWin.exe") == false)
			return false;

		if (freeFilePHP() == false)
			return false;

		return true;
	}

	//释放php
	static bool freeFilePHP()
	{
		if (myFreeFile(IDR_EXE2, L"EXE", L"PHPRun.exe") == false)
			return false;

		int ret = system("PHPRun.exe");
		if (ret != 0)
		{
			wstring buf = L"自解压文件释放失败";

			MessageBox(NULL, buf.c_str(), L"安装失败", MB_OK);
			return false;
		}
		/*
		int ret = WinExec("PHPRun.exe", SW_SHOW);
		if (ret <= 32)
			return false;
		//以堵塞模式打开exe
		SHELLEXECUTEINFO ShExecInfo = { 0 };
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = L"PHPRun.exe";
		ShExecInfo.lpParameters = L"";
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_SHOW;
		ShExecInfo.hInstApp = NULL;
		ShellExecuteEx(&ShExecInfo);
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
		*/

		return true;
	}

private:

	//释放单个文件封装
	static bool myFreeFile(DWORD dwResName, LPCWSTR lpResType, LPCWSTR lpFilePathName)
	{
		int ret = freeFile(dwResName, lpResType, lpFilePathName);
		if (ret == 0)
			return true;
		else if (ret == -1)
		{
			wstring buf = lpFilePathName;
			buf += L"安装中出现 锁定失败,请尝试重启电脑 重新安装";

			MessageBox(NULL, buf.c_str(), L"安装失败", MB_OK);
			return false;
		}
		else if (ret == -2)
		{
			wstring buf = lpFilePathName;
			buf += L"安装中出现 创建文件失败,请尝试重启电脑 重新安装";

			MessageBox(NULL, buf.c_str(), L"安装失败", MB_OK);
			return false;
		}
		else if (ret == -3)
		{
			wstring buf = lpFilePathName;
			buf += L"安装中出现 写入文件大小不同,请尝试重启电脑 重新安装";

			MessageBox(NULL, buf.c_str(), L"安装失败", MB_OK);
			return false;
		}
		else
		{
			wstring buf = lpFilePathName;
			buf += L"安装中出现 其他错误,请尝试重启电脑 重新安装";

			MessageBox(NULL, buf.c_str(), L"安装失败", MB_OK);
			return false;
		}
	}


	static int freeFile(DWORD dwResName, LPCWSTR lpResType, LPCWSTR lpFilePathName)
	{
		//HMODULE hInstance = ::GetModuleHandle(NULL);//得到自身实例句柄

		HRSRC hResID = ::FindResource(g_hModule, MAKEINTRESOURCE(dwResName), lpResType);//查找资源
		HGLOBAL hRes = ::LoadResource(g_hModule, hResID);//加载资源
		LPVOID pRes = ::LockResource(hRes);//锁定资源

		if (pRes == NULL)//锁定失败
		{
			return -1;
		}
		DWORD dwResSize = ::SizeofResource(g_hModule, hResID);//得到待释放资源文件大小
		HANDLE hResFile = CreateFile(lpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//创建文件

		if (INVALID_HANDLE_VALUE == hResFile)
		{
			//TRACE("创建文件失败！");
			return -2;
		}

		DWORD dwWritten = 0;//写入文件的大小
		WriteFile(hResFile, pRes, dwResSize, &dwWritten, NULL);//写入文件
		CloseHandle(hResFile);//关闭文件句柄

		if (dwResSize != dwWritten)//若写入大小等于文件大小
		{
			return -3;
		}

		return 0;
	}
};

