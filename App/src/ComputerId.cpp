#pragma once
#define _WIN32_DCOM

#include <windows.h>

#include <iostream>
#include <string>
#include <time.h>
#include <direct.h>

#include "MD5.h"

#include <comdef.h>
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
using namespace std;

typedef struct UserInfo_t
{
	char CpuID[20];                    //CPU序列号
	char BaseBoardID[256];         //主板ID
	char BaseBoardMake[256];         //主板型号
	char ComputerMake[256];         //电脑型号
	char SystemDiskID[256];        //系统所在硬盘的序列号
	char BIOSID[20];                   //BIOS序列号
	char MacAddress[20];             //MAC地址
}UserInfo;


void Trims(char* data)           //去掉字符串中的空格
{
	int i = -1, j = 0;
	int ch = ' ';

	while (data[++i] != '\0')
	{
		if (data[i] != ch)
		{
			data[j++] = data[i];
		}
	}
	data[j] = '\0';
}

//获取硬件信息
int GetUserInfo(UserInfo& info)
{
	HRESULT hres;
	memset(&info, 0x00, sizeof(UserInfo));

	CoUninitialize();
	hres = CoInitializeEx(0, COINIT_MULTITHREADED);   //第二个参数设置当前线程的并发模式为多线程
	//hres =  CoInitializeEx(0,COINIT_APARTMENTTHREADED);  //并发模式为单线程（即只能在单线程函数中调用GetUserInfo()）
	if (FAILED(hres))
	{
		if (hres != S_FALSE && hres != RPC_E_CHANGED_MODE)
			return -1;
	}
	hres = CoInitializeSecurity(
		NULL,
		-1,
		NULL,
		NULL,
		RPC_C_AUTHN_LEVEL_DEFAULT,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		EOAC_NONE,
		NULL
	);
	if (FAILED(hres) && hres != RPC_E_TOO_LATE)
	{
		CoUninitialize();
		return -2;
	}
	IWbemLocator* pLoc = NULL;
	hres = CoCreateInstance(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hres))
	{
		CoUninitialize();
		return -3;
	}
	IWbemServices* pSvc = NULL;
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"),
		NULL,
		NULL,
		0,
		NULL,
		0,
		0,
		&pSvc
	);
	if (FAILED(hres))
	{
		pLoc->Release();
		CoUninitialize();
		return -4;
	}
	hres = CoSetProxyBlanket(
		pSvc,
		RPC_C_AUTHN_WINNT,
		RPC_C_AUTHZ_NONE,
		NULL,
		RPC_C_AUTHN_LEVEL_CALL,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		EOAC_NONE
	);
	if (FAILED(hres))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return -5;
	}

	//获取CPU序列号
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM win32_Processor"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	if (FAILED(hres))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return -6;
	}
	IWbemClassObject* pclsObj;
	ULONG uReturn = 0;
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)
		{
			break;
		}
		VARIANT vtProp;
		hr = pclsObj->Get(L"ProcessorId", 0, &vtProp, 0, 0);

		//如果不为默认字符串则放入
		if (strcmp(_com_util::ConvertBSTRToString(vtProp.bstrVal), "Default string"))
			wcstombs(info.CpuID, vtProp.bstrVal, 18);


		VariantClear(&vtProp);
		pclsObj->Release();
	}

	//获取主板型号
	pEnumerator->Release();
	pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_BaseBoard WHERE (Product IS NOT NULL)"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	if (FAILED(hres))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return -7;
	}
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)
		{
			break;
		}
		VARIANT vtProp;
		hr = pclsObj->Get(L"Product", 0, &vtProp, 0, 0);

		//如果不为默认字符串则放入
		if (strcmp(_com_util::ConvertBSTRToString(vtProp.bstrVal), "Default string"))
			wcstombs(info.BaseBoardMake, vtProp.bstrVal, 20);

		VariantClear(&vtProp);
		pclsObj->Release();
	}


	//获取电脑型号
	pEnumerator->Release();
	pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_computersystem"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	if (FAILED(hres))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return -7;
	}
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)
		{
			break;
		}
		VARIANT vtProp;
		hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);

		//如果不为默认字符串则放入
		if (strcmp(_com_util::ConvertBSTRToString(vtProp.bstrVal), "Default string"))
			wcstombs(info.ComputerMake, vtProp.bstrVal, 20);

		VariantClear(&vtProp);
		pclsObj->Release();
	}


	//获取主板ID
	pEnumerator->Release();
	pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_BaseBoard WHERE (SerialNumber IS NOT NULL)"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	if (FAILED(hres))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return -7;
	}
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)
		{
			break;
		}
		VARIANT vtProp;
		hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);

		//如果不为默认字符串则放入
		if (strcmp(_com_util::ConvertBSTRToString(vtProp.bstrVal), "Default string"))
			wcstombs(info.BaseBoardID, vtProp.bstrVal, 20);

		VariantClear(&vtProp);
		pclsObj->Release();
	}

	//获取系统所在硬盘的ID
	int diskIndex = 0;
	pEnumerator->Release();
	pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_DiskPartition WHERE Bootable = TRUE"),  //查找启动盘
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	if (FAILED(hres))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return -8;
	}
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)
		{
			break;
		}
		VARIANT vtProp;
		hr = pclsObj->Get(L"DiskIndex", 0, &vtProp, 0, 0);
		diskIndex = vtProp.intVal;
		VariantClear(&vtProp);
		pclsObj->Release();
	}

	////根据系统所在硬盘的ID查询序列号
	//char index[10];
	//string strQuery = "SELECT * FROM Win32_DiskDrive WHERE Index = ";
	//_itoa(diskIndex, index, 10);
	//string indexStr(index);
	//strQuery += indexStr;
	//pEnumerator->Release();
	//pEnumerator = NULL;
	//hres = pSvc->ExecQuery(
	//	bstr_t("WQL"),
	//	bstr_t(strQuery.c_str()),
	//	WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
	//	NULL,
	//	&pEnumerator);
	//if (FAILED(hres))
	//{
	//	pSvc->Release();
	//	pLoc->Release();
	//	CoUninitialize();
	//	return -8;
	//}
	//while (pEnumerator)
	//{
	//	HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
	//	if (0 == uReturn)
	//	{
	//		break;
	//	}
	//	VARIANT vtProp;
	//	hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);

	//	//如果不为默认字符串则放入
	//	if (strcmp(_com_util::ConvertBSTRToString(vtProp.bstrVal), "Default string"))
	//	{
	//		wcstombs(info.SystemDiskID, vtProp.bstrVal, 20);
	//		Trims(info.SystemDiskID);
	//	}

	//	VariantClear(&vtProp);
	//	pclsObj->Release();
	//}

	//获取BIOS序列号
	pEnumerator->Release();
	pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_BIOS"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	if (FAILED(hres))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return -9;
	}
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)
		{
			break;
		}
		VARIANT vtProp;
		hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);

		//如果不为默认字符串则放入
		if (strcmp(_com_util::ConvertBSTRToString(vtProp.bstrVal), "Default string"))
			wcstombs(info.BIOSID, vtProp.bstrVal, 20);

		VariantClear(&vtProp);
		pclsObj->Release();
	}

	//获取本地连接的MAC地址
	/*
	pEnumerator->Release();
	pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_NetworkAdapter WHERE (MACAddress IS NOT NULL) AND (NOT (PNPDeviceID LIKE 'ROOT%'))"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	if (FAILED(hres))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return -10;
	}
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)
		{
			break;
		}
		VARIANT vtProp;

		hr = pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
		string des = _com_util::ConvertBSTRToString(vtProp.bstrVal);
		if (strstr(des.c_str(), "Ethernet Connection") != NULL)
		{
			hr = pclsObj->Get(L"MacAddress", 0, &vtProp, 0, 0);
			wcstombs(info.MacAddress, vtProp.bstrVal, 20);
		}
		VariantClear(&vtProp);
		pclsObj->Release();
	}
	*/


	//清理
	pSvc->Release();
	pLoc->Release();
	pEnumerator->Release();
	CoUninitialize();

	return 0;
}

//获取机器码
bool GetComputerId(string& id, string& error)
{
	UserInfo info;
	int ret = GetUserInfo(info);

	if (ret != 0)
	{
		error = "获取机器码错误 " + to_string(ret);
		//cout << "错误信息: " << error << endl;

		return false;
	}

	time_t now_time = time(NULL);
	//获取本地时间  
	tm* t_tm = localtime(&now_time);

	//_mkdir((appFile + "log").c_str());

	////test
	//fstream file((appFile + "log/ComputerId.log").c_str(), ios::app);

	//if (file.good())
	//{
	//	file << "时间 " << asctime(t_tm) << endl;
	//	file << "bost： " << info.BIOSID << endl;
	//	file << "主板： " << info.BaseBoardID << endl;
	//	file << "cpu： " << info.CpuID << endl;
	//	//cout << "启动盘： " << info.SystemDiskID << endl;
	//	file << "主板型号： " << info.BaseBoardMake << endl;
	//	file << "电脑型号： " << info.ComputerMake << endl;
	//	file << endl << endl;

	//	file.close();
	//}

	string temp;
	temp = info.CpuID;
	//temp += info.SystemDiskID;
	temp += info.BaseBoardID;
	temp += info.BIOSID;
	temp += info.BaseBoardMake;
	temp += info.ComputerMake;


	id = MD5(temp).toString();

	return true;
}