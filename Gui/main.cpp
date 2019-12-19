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


string appFile="D:\\�û��ĵ�\\����\\��������\\��Q\\data\\app\\cn.xiaoxiaoge.Market\\";
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

//��ȡ�ļ�ȫ������
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

		//��ȡ�����ڴ�
		//wstring strMapName(L"MarketWin");                // �ڴ�ӳ���������
		LPVOID pBuffer;                                    // �����ڴ�ָ��

		// ������ͼ��һ���������ڴ�ӳ���ļ�����  
		HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName.c_str());
		if (NULL == hMap)
		{
			throw exception("�����ͨ�ڴ��ȡʧ��");
		}
		else
		{
			//�򿪳ɹ���ӳ������һ����ͼ���õ�ָ�����ڴ��ָ�룬��ʾ�����������
			pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			temp_buf = (const char*)pBuffer;
		}
		::UnmapViewOfFile(pBuffer);
#endif
		string temp_buf = readFileAll("win.tmp");

		remove("./win.tmp");

		boost::property_tree::wptree temp_json;

		//����json�ַ���
		wstringstream temp_ss(OperateStr::string2wstring(temp_buf));
		boost::property_tree::read_json(temp_ss, temp_json);

		//��ȡ�ļ�·��
		wstring wAppFile = temp_json.get<wstring>(L"AppFile");
		appFile = OperateStr::wstring2string(wAppFile);

		//��ȡ������
		wstring wComputerId = temp_json.get<wstring>(L"ComputerId", L"");
		local_computer = OperateStr::wstring2string(wComputerId);

		//��ȡkey
		wstring wKey = temp_json.get<wstring>(L"Key", L"");
		key = OperateStr::wstring2string(wKey);

		//��ȡ����ʱ��
		wstring wExceedDateTime = temp_json.get<wstring>(L"ExceedDateTime", L"");
		exceedDateTime = OperateStr::wstring2string(wExceedDateTime);

		//��ȡ�汾��
		wstring wVersion = temp_json.get<wstring>(L"Version", L"");
		version = OperateStr::wstring2string(wVersion);


		//��ȡȺ�б�
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

		//����Ƿ�Ϊ��
		if (appFile.empty())
		{
			throw exception("����·��Ϊ��");
		}

	}
	catch (exception & e)
	{
		MessageBoxA(NULL, e.what(), "������ ��ͨ����", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("��ͨ����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return false;
	}
	catch (...)
	{
		MessageBoxA(NULL, "��ȡ�����쳣", "������ ��ͨ����", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("��ͨ����"), QString::fromLocal8Bit("��ȡ�����쳣"), QMessageBox::Ok);
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

		//��ȡ�����ڴ�
		wstring strMapName(L"MarketKey");                // �ڴ�ӳ���������
		LPVOID pBuffer;                                    // �����ڴ�ָ��

		// ������ͼ��һ���������ڴ�ӳ���ļ�����  
		HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName.c_str());
		if (NULL == hMap)
		{
			throw exception("�����ͨ�ڴ��ȡʧ��");
		}
		else
		{
			//�򿪳ɹ���ӳ������һ����ͼ���õ�ָ�����ڴ��ָ�룬��ʾ�����������
			pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			temp_buf = (const char*)pBuffer;
		}
		::UnmapViewOfFile(pBuffer);
#endif

		string temp_buf = readFileAll("win.tmp");
		remove("./win.tmp");

		boost::property_tree::wptree temp_json;

		//����json�ַ���
		wstringstream temp_ss(OperateStr::string2wstring(temp_buf));
		boost::property_tree::read_json(temp_ss, temp_json);

		//��ȡ�ļ�·��
		wstring wAppFile = temp_json.get<wstring>(L"AppFile", L"");
		appFile = OperateStr::wstring2string(wAppFile);

		//��ȡ������
		wstring wComputerId = temp_json.get<wstring>(L"ComputerId", L"");
		local_computer = OperateStr::wstring2string(wComputerId);

		//��ȡkey
		wstring wKey = temp_json.get<wstring>(L"Key", L"");
		key = OperateStr::wstring2string(wKey);


		//����Ƿ�Ϊ��
		if (appFile.empty())
		{
			throw exception("����·��Ϊ��");
		}

		//����Ƿ�Ϊ��
		if (wComputerId.empty())
		{
			throw exception("����·��Ϊ��");
		}
	}
	catch (exception & e)
	{
		MessageBoxA(NULL, e.what(), "��Կ ��ͨ����", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("��ͨ����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return false;
	}
	catch (...)
	{
		MessageBoxA(NULL, "��ȡ�����쳣", "��Կ ��ͨ����", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("��ͨ����"), QString::fromLocal8Bit("��ȡ�����쳣"), QMessageBox::Ok);
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

		//��ȡ�����ڴ�
		//wstring strMapName(L"MarketWin");                // �ڴ�ӳ���������
		LPVOID pBuffer;                                    // �����ڴ�ָ��

		// ������ͼ��һ���������ڴ�ӳ���ļ�����  
		HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName.c_str());
		if (NULL == hMap)
		{
			throw exception("�����ͨ�ڴ��ȡʧ��");
		}
		else
		{
			//�򿪳ɹ���ӳ������һ����ͼ���õ�ָ�����ڴ��ָ�룬��ʾ�����������
			pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			temp_buf = (const char*)pBuffer;
		}
		::UnmapViewOfFile(pBuffer);

#endif

		string temp_buf = readFileAll("win.tmp");
		remove("./win.tmp");


		boost::property_tree::wptree temp_json;

		//����json�ַ���
		wstringstream temp_ss(OperateStr::string2wstring(temp_buf));
		boost::property_tree::read_json(temp_ss, temp_json);

		//��ȡ�ļ�·��
		wstring wAppFile = temp_json.get<wstring>(L"AppFile");
		appFile = OperateStr::wstring2string(wAppFile);

		//��ȡ�汾��
		wstring wVersion = temp_json.get<wstring>(L"Version", L"");
		version = OperateStr::wstring2string(wVersion);

		//����Ƿ�Ϊ��
		if (appFile.empty())
		{
			throw exception("����·��Ϊ��");
		}

	}
	catch (exception & e)
	{
		MessageBoxA(NULL, e.what(), "������ ��ͨ����", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("��ͨ����"), QString::fromLocal8Bit(e.what()), QMessageBox::Ok);
		//MessageBoxA(NULL, e.what(), "����", MB_OK);
		return false;
	}
	catch (...)
	{
		MessageBoxA(NULL, "��ȡ�����쳣", "������ ��ͨ����", MB_OK);
		//QMessageBox::warning(NULL, QString::fromLocal8Bit("��ͨ����"), QString::fromLocal8Bit("��ȡ�����쳣"), QMessageBox::Ok);
		return false;
	}

	return true;
}