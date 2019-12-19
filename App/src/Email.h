//#pragma once
////#include <WinSock2.h>  //适用平台 Windows
////#pragma  comment(lib, "ws2_32.lib") /*链接ws2_32.lib动态链接库*/ 
//
//
//#include <winsock.h>
//#pragma comment (lib ,"wsock32.lib")
//
//#include <fstream>  
//#include <iostream>  
//#include <string>  
//#include <vector>
//
//
//// POP3服务器（端口：110） Csmtp服务器（端口：25） 
//using namespace std;
//class Csmtp
//{
//	bool is_html;//是否为html格式
//
//	int port;
//	string domain;
//	string user;
//	string pass;
//	string name;//发送者名称
//	string target;//接受者邮箱
//	string title;  //邮件标题
//	string content;  //邮件内容
//
//	string error;
//
//	HOSTENT* pHostent;
//	SOCKET sockClient;  //客户端的套接字
//	vector<string> filename;  //存储附件名的向量
//
//public:
//
//	Csmtp(
//		int _port, //端口25
//		string _domain,     //域名
//		string _user,       //发送者的邮箱
//		string _pass,       //密码
//		string _name)        //发送者名称)     
//		:port(_port), domain(_domain), user(_user), pass(_pass), is_html(false), name(_name) {};//内容 
//
//	bool CReateSocket();
//
//	//设置标题
//	void setTitle(string tem) { title = tem; }
//
//	//设置邮箱内容
//	void setContent(string tem) { content = tem; }
//
//	//目标邮箱
//	void setTarget(string email) { target = email; }
//
//	//获取处理信息
//	string getInf()
//	{
//		return error;
//	}
//
//	//设置是否为html格式
//	void setHtml(bool t) { is_html = t; }
//
//	int verify();
//
//	int SendAttachment(SOCKET& sockClient);
//	bool SendMail();
//	void addfile(string str) { filename.push_back(str); }
//
//	bool errorCode(string buf);
//	int MyRecv(SOCKET& s, string& buff);
//};