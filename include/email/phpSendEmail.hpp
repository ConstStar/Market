#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <chrono>

using namespace std;


class phpSendEmail
{

public:
	phpSendEmail(
		string& phpPath,
		string& phpFile,
		string& sendFile,
		string& verifyFile,
		string verifyPutEmail,
		string verifyPasswd,
		string smtp,
		bool isSSL,
		string port,
		string putEmail,
		string passwd,
		bool isHTML,
		string getEmail,
		string putName,
		string title,
		string word
	)
		:m_phpFile(phpFile)
		, m_sendFile(sendFile)
		, m_verifyFile(verifyFile)
		, m_phpPath(phpPath)
		, m_verifyPutEmail(verifyPutEmail)
		, m_verifyPasswd(verifyPasswd)
		, m_smtp(smtp)
		, m_isSSL(isSSL)
		, m_port(port)
		, m_putEmail(putEmail)
		, m_passwd(passwd)
		, m_isHTML(isHTML)
		, m_getEmail(getEmail)
		, m_putName(putName)
		, m_title(title)
		, m_word(word)

	{}

	phpSendEmail(
		string& phpPath,
		string& phpFile,
		string& sendFile,
		string smtp,
		bool isSSL,
		string port,
		string putEmail,
		string passwd
	)
		:m_phpFile(phpFile)
		, m_sendFile(sendFile)
		, m_phpPath(phpPath)
		, m_smtp(smtp)
		, m_isSSL(isSSL)
		, m_port(port)
		, m_putEmail(putEmail)
		, m_passwd(passwd)
	{}

	phpSendEmail(
		string& phpPath,
		string& phpFile,
		string& sendFile,
		string smtp,
		bool isSSL,
		string port,
		string putEmail,
		string passwd,
		string getEmail,
		string name,
		string title,
		string word
	)
		:m_phpFile(phpFile)
		, m_sendFile(sendFile)
		, m_phpPath(phpPath)
		, m_smtp(smtp)
		, m_isSSL(isSSL)
		, m_port(port)
		, m_putEmail(putEmail)
		, m_passwd(passwd)
		,m_getEmail(getEmail)
		,m_putName(name)
		,m_title(title)
		,m_word(word)
	{}


	phpSendEmail(
		string& phpPath,
		string& phpFile,
		string& verifyFile,
		string& verifyPutEmail,
		string& verifyPasswd,
		string getEmail
	)
		: m_verifyFile(verifyFile)
		, m_phpFile(phpFile)
		, m_phpPath(phpPath)
		, m_verifyPutEmail(verifyPutEmail)
		, m_verifyPasswd(verifyPasswd)
		, m_getEmail(getEmail)
	{}

	//发送

	bool send()
	{
		//char tempFile[1024];
		long long temp_time = std::chrono::system_clock::now().time_since_epoch().count();

		//sprintf(tempFile, "%x", temp_time);
		//_ultoa(temp_time, tempFile, 36);
		string tempPathFile(m_phpPath + "\\Send_" + to_string(temp_time) + ".php");
		//log(tempPathFile);

		string phpStr = readFileAll(m_sendFile.c_str());

		replace_str(phpStr, "{smtp}", m_smtp.c_str());
		if (m_isSSL)
			replace_str(phpStr, "{isSSL}", "ssl");
		else
			replace_str(phpStr, "{isSSL}", "");

		replace_str(phpStr, "{port}", m_port.c_str());
		replace_str(phpStr, "{putEmail}", m_putEmail.c_str());
		replace_str(phpStr, "{passwd}", m_passwd.c_str());
		if (m_isHTML)
			replace_str(phpStr, "{isHTML}", "true");
		else
			replace_str(phpStr, "{isHTML}", "false");

		replace_str(phpStr, "{getEmail}", m_getEmail.c_str());
		replace_str(phpStr, "{putName}", G2U(m_putName.c_str()));
		replace_str(phpStr, "{title}", G2U(m_title.c_str()));
		replace_str(phpStr, "{word}", G2U(m_word.c_str()));

		string stmp_file(tempPathFile);
		fstream temp_file(tempPathFile, ios::out);
		if (temp_file.good())
			temp_file << phpStr;
		else
			cout << "写入失败" << endl;
		temp_file.close();


		string cmdStr(m_phpFile);
		cmdStr += " ";
		cmdStr += tempPathFile;


		retInf = U2G(ExeCmd(cmdStr).c_str());

		//remove(tempPathFile.c_str());

		if (retInf == "[Success]")
			return true;
		else
			return false;
	}

	bool verify()
	{
		//char tempFile[1024];
		long long temp_time = std::chrono::system_clock::now().time_since_epoch().count();;
		//_ltoa(temp_time, tempFile, 36);
		string tempPathFile(m_phpPath + "\\Verify_" + to_string(temp_time) + ".php");
		//log(tempPathFile);

		string phpStr = readFileAll(m_verifyFile.c_str());

		replace_all_distinct(phpStr, "{putEmail}", m_verifyPutEmail.c_str());
		replace_str(phpStr, "{passwd}", m_verifyPasswd.c_str());
		replace_str(phpStr, "{getEmail}", m_getEmail.c_str());

		string stmp_file(tempPathFile);
		fstream temp_file(stmp_file, ios::out);
		if (temp_file.good())
			temp_file << phpStr;
		else
			cout << "写入失败" << endl;
		temp_file.close();


		string cmdStr(m_phpFile);
		cmdStr += " ";
		cmdStr += tempPathFile;


		retInf = U2G(ExeCmd(cmdStr).c_str());

		remove(tempPathFile.c_str());

		if (retInf == "[Success]")
			return true;
		else
			return false;
	}

	//获取错误信息
	const string& getInf()
	{
		return retInf;
	}

	//设置

	void setGetEmail(string& tmp)
	{
		m_getEmail = tmp;
	}

	void setPutName(string& tmp)
	{
		m_putName = tmp;
	}

	void setTitle(string& tmp)
	{
		m_title = tmp;
	}

	void setWord(string& tmp)
	{
		m_word = tmp;
	}

	void setIsHtml(bool t)
	{
		m_isHTML = t;
	}


private:

	//	//执行cmd命令 并获取返回内容
	//	string getCmdResult(const string& strCmd)
	//	{
	//		/*for (int i = 0; i < 200; i++)
	//		{
	//			WinExec("cmd /c dir c:\\*.* >d:\\cfiles.txt", SW_HIDE);
	//		}*/
	//		string strResult;
	//		long long temp_time = std::chrono::system_clock::now().time_since_epoch().count();
	//		string tempPathFile(m_phpPath + "\\cmd_" + to_string(temp_time) + ".log");
	//
	//		string cmdStr(strCmd + " > " + tempPathFile);
	//
	//		system(("cmd /c " + cmdStr).c_str());
	//
	//		strResult = readFileAll(tempPathFile.c_str());
	//#if 0
	//		char buf[10240] = { 0 };
	//		FILE* pf = NULL;
	//
	//		if ((pf = _popen(strCmd.c_str(), "r")) == NULL)
	//		{
	//			return "";
	//		}
	//
	//		string strResult;
	//		while (fgets(buf, sizeof buf, pf))
	//		{
	//			strResult += buf;
	//		}
	//
	//		_pclose(pf);
	//
	//		unsigned int iSize = strResult.size();
	//		if (iSize > 0 && strResult[iSize - 1] == '\n')  // linux
	//		{
	//			strResult = strResult.substr(0, iSize - 1);
	//		}
	//
	//#endif
	//
	//		return strResult;
	//	}

	void log(string buf)
	{
		fstream file("test.log", ios::app);
		file << buf << endl;
		file.close();
	}

	static wstring string2wstring(string str)
	{
		wstring result;
		//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
		TCHAR* buffer = new TCHAR[len + 1];
		//多字节编码转换成宽字节编码  
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
		buffer[len] = '\0';             //添加字符串结尾  
		//删除缓冲区并返回值  
		result.append(buffer);
		delete[] buffer;
		return result;
	}

	string ExeCmd(string pszCmd)
	{
		wstring pszCmd_w = string2wstring(pszCmd);
		//wcout << "pszCmd_w is " << pszCmd_w << endl;
		// 创建匿名管道,write->read;
		SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
		HANDLE hRead, hWrite;
		if (!CreatePipe(&hRead, &hWrite, &sa, 0))
		{
			//cout << "@ CreatePipe failed!" << endl;
			return (" ");
		}
		//cout << "@0" << endl;
		// 设置命令行进程启动信息(以隐藏方式启动命令并定位其输出到hWrite
		STARTUPINFO si = { sizeof(STARTUPINFO) }; // Pointer to STARTUPINFO structure;
		GetStartupInfo(&si);
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
		//si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE; //隐藏窗口；
		si.hStdError = hWrite;
		si.hStdError = hWrite;
		si.hStdOutput = hWrite; //管道的输入端口连接命令行的输出；
		// 启动命令行
		PROCESS_INFORMATION pi;// Pointer to PROCESS_INFORMATION structure;
		if (!CreateProcess(NULL,
			(LPWSTR)pszCmd_w.c_str(),
			NULL,
			NULL,
			TRUE,
			//FALSE,          // Set handle inheritance to FALSE
			NULL,
			//0,              // No creation flags
			NULL,
			NULL,
			&si,
			&pi))
		{
			//cout << "@ CreateProcess failed!" << endl;
			return ("Cannot create process");
		}
		CloseHandle(hWrite);//关闭管道的输入端口；
		// 读取命令行返回值
		string strRetTmp;
		char buff[1024] = { 0 };
		DWORD dwRead = 0;
		strRetTmp = buff;
		while (ReadFile(hRead, buff, 1024, &dwRead, NULL))//从管道的输出端获取命令行写入的数据；
		{
			//cout << "buff = " << buff << endl;
			strRetTmp += buff;
		}
		CloseHandle(hRead);//关闭管道的输出端口；
		//cout << "strRetTmp:" << strRetTmp << endl;
		return strRetTmp;
	}


	//字符串替换
	void replace_all_distinct(string& str, string old_value, const char* new_value)
	{
		for (string::size_type pos(0); pos != string::npos; pos += strlen(new_value))
		{
			if ((pos = str.find(old_value, pos)) != string::npos)
			{
				str.replace(pos, old_value.length(), new_value);
			}
			else { break; }
		}
		//return str;
	}

	void replace_str(string& str, string old_value, const char* new_value)
	{
		str.replace(str.find(old_value), old_value.length(), new_value);
	}

	//读取文件全部内容
	string readFileAll(const char* file)
	{
		std::ifstream in(file);
		std::ostringstream tmp;
		tmp << in.rdbuf();
		return tmp.str();
	}


	char* G2U(const char* gb2312)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
		len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		char* str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
		if (wstr) delete[] wstr;
		return str;
	}

	char* U2G(const char* utf8)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
		len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
		char* str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
		if (wstr) delete[] wstr;
		return str;
	}

private:
	string m_phpPath;
	string m_phpFile;
	string m_sendFile;
	string m_verifyFile;


	string m_smtp;
	bool m_isSSL;
	string m_port;
	string m_putEmail;
	string m_passwd;
	bool m_isHTML;
	string m_getEmail;
	string m_putName;
	string m_title;
	string m_word;

	string m_verifyPutEmail;
	string m_verifyPasswd;

	string retInf;
};