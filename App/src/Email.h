//#pragma once
////#include <WinSock2.h>  //����ƽ̨ Windows
////#pragma  comment(lib, "ws2_32.lib") /*����ws2_32.lib��̬���ӿ�*/ 
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
//// POP3���������˿ڣ�110�� Csmtp���������˿ڣ�25�� 
//using namespace std;
//class Csmtp
//{
//	bool is_html;//�Ƿ�Ϊhtml��ʽ
//
//	int port;
//	string domain;
//	string user;
//	string pass;
//	string name;//����������
//	string target;//����������
//	string title;  //�ʼ�����
//	string content;  //�ʼ�����
//
//	string error;
//
//	HOSTENT* pHostent;
//	SOCKET sockClient;  //�ͻ��˵��׽���
//	vector<string> filename;  //�洢������������
//
//public:
//
//	Csmtp(
//		int _port, //�˿�25
//		string _domain,     //����
//		string _user,       //�����ߵ�����
//		string _pass,       //����
//		string _name)        //����������)     
//		:port(_port), domain(_domain), user(_user), pass(_pass), is_html(false), name(_name) {};//���� 
//
//	bool CReateSocket();
//
//	//���ñ���
//	void setTitle(string tem) { title = tem; }
//
//	//������������
//	void setContent(string tem) { content = tem; }
//
//	//Ŀ������
//	void setTarget(string email) { target = email; }
//
//	//��ȡ������Ϣ
//	string getInf()
//	{
//		return error;
//	}
//
//	//�����Ƿ�Ϊhtml��ʽ
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