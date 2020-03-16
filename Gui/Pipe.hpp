#pragma onceenum 

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <Windows.h>
#include <string>

#include <memory>

using namespace std;


//my using

enum PIPEMSGTYPE
{
	NONE,
	SQL,
	COMMAND
};






class PipeException :std::exception
{

public:
	PipeException(string inf) :inf(inf), exception(inf.c_str())
	{}

	string what()
	{
		return inf;
	}

private:
	string inf;
};


//定义管道通信类
class Pipe
{
#define DATA_MAX 4096

	enum PIPEUSERTYPE {
		NONE,
		USER_CLIENT, //客户端
		USER_SERVER, //服务端
	};


public:
	Pipe() :m_state(NONE), m_hWrite(NULL)
	{}

	void initServer(std::wstring File, std::wstring Command)
	{
		m_state = USER_SERVER;
		m_hWrite = NULL;

		SECURITY_ATTRIBUTES sa{ 0 };
		sa.nLength = sizeof(sa);
		sa.bInheritHandle = TRUE;


		HANDLE hRead;
		CreatePipe(&hRead, &m_hWrite, &sa, 0);

		STARTUPINFOW si{ 0 };
		si.cb = sizeof(si);
		si.hStdInput = hRead;
		si.dwFlags = STARTF_USESTDHANDLES;

		PROCESS_INFORMATION pi{ 0 };

		WCHAR szCommand[512]{ 0 };
		//GetModuleFileNameW(nullptr, szCommand, _countof(szCommand));
		wcscat(szCommand, File.c_str());
		wcscat(szCommand, Command.c_str());
		auto ret = CreateProcessW(NULL, szCommand, nullptr, nullptr, TRUE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi);


		if (!ret)
		{
			m_state = NONE;
			m_hWrite = NULL;

			throw PipeException("打开程序失败");
		}
	}

	void initClient()
	{
		m_state = USER_CLIENT;

	}

	bool WriteData(string buf)
	{
		if (m_state == USER_SERVER)
		{
			if (buf.length() >= DATA_MAX)
				throw PipeException("Pipe发送内容过多");

			DWORD nLen = 0;
			WriteFile(m_hWrite, buf.c_str(), buf.length(), &nLen, nullptr);
		}
		else
			return false;

		return true;
	}

	bool ReadData(string& buf)
	{
		if (m_state == USER_CLIENT)
		{
			DWORD nLEn = 0;
			CHAR szBuffer[DATA_MAX]{ 0 };

			OVERLAPPED ov;
			ov.Offset = 0;
			ov.OffsetHigh = 0;
			ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

 			ReadFile(GetStdHandle(STD_INPUT_HANDLE), szBuffer, sizeof(szBuffer), &nLEn, &ov);
			//ReadFileEx(GetStdHandle(STD_INPUT_HANDLE), szBuffer, sizeof(szBuffer), nullptr, nullptr);
			Sleep(100);

			buf = szBuffer;
		}
		else
			return false;


		return true;
	}


private:
	//	std::wstring m_pipe_name;
	HANDLE m_hWrite;
	PIPEUSERTYPE m_state; //状态设置
};