//#include "Email.h"
////#include <afx.h>//异常类
//
//static const char base64Char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//char* base64Encode(char const* origSigned, unsigned origLength)
//{
//	unsigned char const* orig = (unsigned char const*)origSigned; // in case any input bytes have the MSB set  
//	if (orig == NULL) return NULL;
//
//	unsigned const numOrig24BitValues = origLength / 3;
//	bool havePadding = origLength > numOrig24BitValues * 3;
//	bool havePadding2 = origLength == numOrig24BitValues * 3 + 2;
//	unsigned const numResultBytes = 4 * (numOrig24BitValues + havePadding);
//	char* result = new char[numResultBytes + 3]; // allow for trailing '/0'  
//
//	// Map each full group of 3 input bytes into 4 output base-64 characters:  
//	unsigned i;
//	for (i = 0; i < numOrig24BitValues; ++i)
//	{
//		result[4 * i + 0] = base64Char[(orig[3 * i] >> 2) & 0x3F];
//		result[4 * i + 1] = base64Char[(((orig[3 * i] & 0x3) << 4) | (orig[3 * i + 1] >> 4)) & 0x3F];
//		result[4 * i + 2] = base64Char[((orig[3 * i + 1] << 2) | (orig[3 * i + 2] >> 6)) & 0x3F];
//		result[4 * i + 3] = base64Char[orig[3 * i + 2] & 0x3F];
//	}
//
//	// Now, take padding into account.  (Note: i == numOrig24BitValues)  
//	if (havePadding)
//	{
//		result[4 * i + 0] = base64Char[(orig[3 * i] >> 2) & 0x3F];
//		if (havePadding2)
//		{
//			result[4 * i + 1] = base64Char[(((orig[3 * i] & 0x3) << 4) | (orig[3 * i + 1] >> 4)) & 0x3F];
//			result[4 * i + 2] = base64Char[(orig[3 * i + 1] << 2) & 0x3F];
//		}
//		else
//		{
//			result[4 * i + 1] = base64Char[((orig[3 * i] & 0x3) << 4) & 0x3F];
//			result[4 * i + 2] = '=';
//		}
//		result[4 * i + 3] = '=';
//	}
//
//	result[numResultBytes] = '\0';
//	return result;
//}
//
//
//int Csmtp::SendAttachment(SOCKET& sockClient) /*发送附件*/
//{
//	for (std::vector<string>::iterator iter = filename.begin(); iter != filename.end(); iter++)
//	{
//		cout << "Attachment is sending··· " << endl;
//
//		string path = *iter;
//		ifstream ifs(path, ios::in | ios::binary); //'或链接2个属性，以输入、二进制打开'
//		if (false == ifs.is_open())
//		{
//			cout << "无法打开文件！" << endl;
//			return 1;
//		}
//
//		string sendstring;
//		sendstring = "--@boundary@\r\nContent-Type: application/octet-stream; name=\"1.jpg\"\r\n";
//		sendstring += "Content-Disposition: attachment; filename=\"1.jpg\"\r\n";
//		sendstring += "Content-Transfer-Encoding: base64\r\n\r\n";
//		send(sockClient, sendstring.c_str(), sendstring.length(), 0);
//
//		//infile.read((char*)buffer,sizeof(数据类型));
//
//		// get length of file:
//		ifs.seekg(0, ifs.end);
//		int length = ifs.tellg();
//		ifs.seekg(0, ifs.beg);
//		cout << "length:" << length << endl;
//		// allocate memory:
//		char* buffer = new char[length];
//		// read data as a block:
//		ifs.read(buffer, length);
//		ifs.close();
//		char* pbase;
//		pbase = base64Encode(buffer, length);
//		delete[]buffer;
//		string str(pbase);
//		delete[]pbase;
//		str += "\r\n";
//		int err = send(sockClient, str.c_str(), strlen(str.c_str()), 0);
//
//		if (err != strlen(str.c_str()))
//		{
//			cout << "附件发送出错!" << endl;
//			return 1;
//		}
//	}
//	return 0;
//}
//
//
//bool Csmtp::CReateSocket()
//{
//	WSADATA wsaData;
//	WORD wVersionRequested = MAKEWORD(2, 1);
//	//WSAStarup，即WSA(Windows SocKNDs Asynchronous，Windows套接字异步)的启动命令
//	int err = WSAStartup(wVersionRequested, &wsaData);
//	//cout << "WSAStartup(0:successful):" << err << endl;
//
//	//char namebuf[128];    //获得本地计算机名
//	//string ip_list;
//	//if (0 == gethostname(namebuf, 128))
//	//{
//	//	struct hostent* pHost;  //获得本地IP地址
//	//	pHost = gethostbyname(namebuf);  //pHost返回的是指向主机的列表
//	//	for (int i = 0; pHost != NULL && pHost->h_addr_list[i] != NULL; i++)
//	//	{
//	//		string tem = inet_ntoa(*(struct in_addr*)pHost->h_addr_list[i]);
//	//		ip_list += tem;
//	//		ip_list += "\n";
//	//	}
//	//}
//	//else
//	//{
//	//	cout << "获取主机信息失败..." << endl;
//	//}
//	////////////////////////////////////////////////////////////////////////////
//	//title = namebuf;// 邮件标题
//	//content = ip_list; //主机ip
//
//
//	if (title.empty())
//	{
//		cout << "标题不能为空" << endl;
//		error = "标题不能为空";
//		return false;
//	}
//
//	if (content.empty())
//	{
//		cout << "内容不能为空" << endl;
//		error = "内容不能为空";
//		return false;
//	}
//
//
//	if (target.empty())
//	{
//		cout << "收件人不能为空" << endl;
//		error = "收件人不能为空";
//		return false;
//	}
//
//
//	sockClient = socket(AF_INET, SOCK_STREAM, 0); //建立socket对象  
//
//	int recvTimeout = 200;  //0.2s
//	setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, (char*)&recvTimeout, sizeof(int));
//
//	pHostent = gethostbyname(domain.c_str()); //得到有关于域名的信息
//
//	if (pHostent == NULL)
//	{
//		cout << "创建连接失败，也许没联网！" << endl;
//		error = "网络异常或您的邮箱设置有误";
//		return false;
//	}
//
//	return true;
//}
//
//bool Csmtp::errorCode(string buf)
//{
//	int code = atoi(buf.c_str());
//
//	//正确的返回码
//	if (code == 250 || code == 251 || code == 221)
//	{
//		error = buf;
//		return true;
//	}
//
//	//错误的返回码
//	if (code == 501 || code == 551 || code == 550)
//	{
//		error = "接收邮箱可能不存在 返回消息:" + buf;
//	}
//
//	this->error = buf;
//	return false;
//}
//
////验证邮箱可用性		返回 0则邮箱正确  1邮箱未注册  -1发送异常
//int Csmtp::verify()
//{
//	WSADATA wsaData;
//	WORD wVersionRequested = MAKEWORD(2, 1);
//	//WSAStarup，即WSA(Windows SocKNDs Asynchronous，Windows套接字异步)的启动命令
//	int err = WSAStartup(wVersionRequested, &wsaData);
//
//	sockClient = socket(AF_INET, SOCK_STREAM, 0); //建立socket对象  
//
//	int recvTimeout = 200;  //0.2s
//	setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, (char*)&recvTimeout, sizeof(int));
//
//	pHostent = gethostbyname(domain.c_str()); //得到有关于域名的信息
//
//	if (pHostent == NULL)
//	{
//		cout << "创建连接失败，也许没联网！" << endl;
//		error = "网络异常或您的邮箱设置有误";
//		return -1;
//	}
//
//	char* ecode;
//
//	string buff;
//	err = 0;
//	string message; //
//
//	SOCKADDR_IN addrServer;  //服务端地址
//	addrServer.sin_addr.S_un.S_addr = *((DWORD*)pHostent->h_addr_list[0]); //得到smtp服务器的网络字节序的ip地址     
//
//
//	addrServer.sin_family = AF_INET;
//	addrServer.sin_port = htons(port); //连接端口25 
//	//int connect (SOCKET s , const struct sockaddr FAR *name , int namelen );
//	err = connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));   //向服务器发送请求  
//
//
//	if (err)
//	{
//		error = "向服务器发送请求错误";
//		return -1;
//	}
//
//
//	//cout << "connect:" << err << endl;
//	//telnet smtp.126.com 25 连接服务器结束
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//220 smtp.qq.com Esmtp QQ Mail Server
//	//堵塞sock
//	int ret = MyRecv(sockClient, buff);
//
//	//cout << "connect:" << buff << endl;
//	if (atoi(buff.c_str()) != 220)
//	{
//		error = "发送连接错误 ";
//		error += buff;
//		return -1;
//	}
//
//	message = "ehlo 126.com\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//250
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "helo:" << buff << endl;
//	if (atoi(buff.c_str()) != 250)
//	{
//		error = "发送ehlo错误 ";
//		error += buff;
//		return -1;
//	}
//
//	message = "auth login \r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 VXNlcm5hbWU6
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "auth login:" << buff << endl;
//	//上传邮箱名
//	message = user;
//	ecode = base64Encode(message.c_str(), strlen(message.c_str()));
//	message = ecode;
//	message += "\r\n";
//	delete[]ecode;
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 UGFzc3dvcmQ6
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "usrname:" << buff << endl;
//	if (atoi(buff.c_str()) != 334)
//	{
//		error = "发送邮箱账号错误 ";
//		error += buff;
//		return -1;
//	}
//
//
//	//上传邮箱密码
//	message = pass;
//	ecode = base64Encode(message.c_str(), strlen(message.c_str()));
//	message = ecode;
//	delete[]ecode;
//	message += "\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 UGFzc3dvcmQ6//235 OK Authenticated
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "password:" << buff << endl;
//	if (atoi(buff.c_str()) != 334 && atoi(buff.c_str()) != 235)
//	{
//		error = "发送邮箱密码错误 ";
//		error += buff;
//		return -1;
//	}
//
//	message = "mail from:<" + user + ">\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//235 Authentication successful //250 ok\r\n
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "mail from: " << buff << endl;
//	if (atoi(buff.c_str()) != 235 && atoi(buff.c_str()) != 250)
//	{
//		error = "发送发送者邮箱错误 ";
//		error += buff;
//		return -1;
//	}
//
//
//	message = "rcpt to:<" + target + ">\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//250
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "rcpt to: " << buff << endl;
//
//	//关闭链接
//	closesocket(sockClient);
//
//
//	//
//	title.clear();
//	content.clear();
//	target.clear();
//
//
//
//	int index = 0;
//	//获取最后一行信息
//	for (int i = 0, j = 0; buff[i] != 0; i++)
//	{
//		if (buff[i] == '\n')
//		{
//			index = j;
//			j = i + 1;
//		}
//	}
//
//	buff = buff.c_str() + index;
//
//
//	if (atoi(buff.c_str()) == 550)
//	{
//		error = buff;
//
//		return 1;
//	}
//
//
//	//验证返回值是否正确
//	if (errorCode(buff))
//		return 0;
//	else
//		return -1;
//}
//
//int Csmtp::MyRecv(SOCKET& s, string& buff)
//{
//	char temp[500];
//	buff = "";
//
//	bool t = false;
//	/*for (int i = 0; i < 10; i++)
//	{
//		int ret = recv(sockClient, temp, 500, 0);
//
//		temp[ret] = '\0';
//		buff += temp;
//
//		if (ret == EINTR)
//		{
//
//		}
//
//		Sleep(200);
//	}*/
//
//	while (1)
//	{
//		int ret = recv(sockClient, temp, 500, 0);
//		if (ret > 0)
//		{
//			t = true;
//			//正常处理数据
//			temp[ret] = '\0';
//			buff += temp;
//		}
//		else
//		{
//			if ((ret < 0) && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
//			{
//				continue;//继续接收数据
//			}
//			if (t)
//				break;//跳出接收循环
//		}
//	}
//
//	return 0;
//}
//
//
//bool Csmtp::SendMail()
//{
//	char* ecode;
//
//	string buff;
//	int err = 0;
//	string message; //
//
//	SOCKADDR_IN addrServer;
//	//SOCKADDR_IN addrServer;  //服务端地址
//	addrServer.sin_addr.S_un.S_addr = *((DWORD*)pHostent->h_addr_list[0]); //得到smtp服务器的网络字节序的ip地址     
//
//
//	addrServer.sin_family = AF_INET;
//	addrServer.sin_port = htons(port); //连接端口25 
//	//int connect (SOCKET s , const struct sockaddr FAR *name , int namelen );
//	err = connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));   //向服务器发送请求  
//
//
//	if (err)
//	{
//		error = "向服务器发送请求错误";
//		return false;
//	}
//
//
//	//cout << "connect:" << err << endl;
//	//telnet smtp.126.com 25 连接服务器结束
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//220 smtp.qq.com Esmtp QQ Mail Server
//	//堵塞sock
//	int ret = MyRecv(sockClient, buff);
//
//	//cout << "connect:" << buff << endl;
//	if (atoi(buff.c_str()) != 220)
//	{
//		error = "发送连接错误 ";
//		error += buff;
//		return false;
//	}
//
//	message = "ehlo 126.com\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//250
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "helo:" << buff << endl;
//	if (atoi(buff.c_str()) != 250)
//	{
//		error = "发送ehlo错误 ";
//		error += buff;
//		return false;
//	}
//
//	message = "auth login \r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 VXNlcm5hbWU6
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "auth login:" << buff << endl;
//	//上传邮箱名
//	message = user;
//	ecode = base64Encode(message.c_str(), strlen(message.c_str()));
//	message = ecode;
//	message += "\r\n";
//	delete[]ecode;
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 UGFzc3dvcmQ6
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "usrname:" << buff << endl;
//	if (atoi(buff.c_str()) != 334)
//	{
//		error = "发送邮箱账号错误 ";
//		error += buff;
//		return false;
//	}
//
//
//	//上传邮箱密码
//	message = pass;
//	ecode = base64Encode(message.c_str(), strlen(message.c_str()));
//	message = ecode;
//	delete[]ecode;
//	message += "\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 UGFzc3dvcmQ6//235 OK Authenticated
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "password:" << buff << endl;
//	if (atoi(buff.c_str()) != 334 && atoi(buff.c_str()) != 235)
//	{
//		error = "发送邮箱密码错误 ";
//		error += buff;
//		return false;
//	}
//
//	message = "mail from:<" + user + ">\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//235 Authentication successful //250 ok\r\n
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "mail from: " << buff << endl;
//	if (atoi(buff.c_str()) != 235 && atoi(buff.c_str()) != 250)
//	{
//		error = "发送发送者邮箱错误 ";
//		error += buff;
//		return false;
//	}
//
//
//	message = "rcpt to:<" + target + ">\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//250
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "rcpt to: " << buff << endl;
//	if (atoi(buff.c_str()) != 235 && atoi(buff.c_str()) != 250)
//	{
//		error = "发送接受者邮箱错误 ";
//		error += buff;
//		return false;
//	}
//
//
//	message = "data\r\n";//data要单独发送一次
//	send(sockClient, message.c_str(), message.length(), 0);
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	if (atoi(buff.c_str()) != 354)
//	{
//		error = "发送data错误 ";
//		error += buff;
//		return false;
//	}
//
//
//	//cout << "data: " << buff << endl;
//	///-----------------------------------------DATA-------------------------------------
//	//要使用Csmtp 发送附件, 需要对Csmtp 头信息进行说明, 改变Content-type 及为每一段正文添加BOUNDARY 名,
//	//cout << "-------------------DATA------------------------" << endl;
//	//  头
//
//	message = "from:" + name + " <" + user + ">\r\nto:<" + target + ">\r\nsubject:" + title + "\r\n";
//	message += "MIME-Version: 1.0\r\n";
//	message += "Content-Type: multipart/mixed;boundary=@boundary@\r\n\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//
//	/*"Content-type: text/html; charset=iso-8859-1\r\n"
//		"Content-Transfer-Encoding: base64\r\n\r\n";*/
//
//		//  正文
//	std::string type = is_html ? "html" : "plain";//判断为html类型还是纯文本类型
//
//	message = "--@boundary@\r\nContent-Type: text/" + type;
//	message += ";charset=\"gb2312\"\r\n\r\n" + content + "\r\n\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//
//	//------------------------------------------------------------------------------------------------
//	//  发送附件
//
//	SendAttachment(sockClient);
//
//	/*发送结尾信息*/
//	message = "--@boundary@--\r\n.\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	if (atoi(buff.c_str()) != 250)
//	{
//		error = "发送结尾信息错误 ";
//		error += buff;
//		return false;
//	}
//
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';
//	//cout << "end_qwertyuiop:" << buff << endl;
//
//	message = "QUIT\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';
//	//cout << "Send mail is finish:" << buff << endl;
//
//	//堵塞sock
//	ret = MyRecv(sockClient, buff);
//
//	int index = 0;
//	//获取最后一行信息
//	for (int i = 0, j = 0; buff[i] != 0; i++)
//	{
//		if (buff[i] == '\n')
//		{
//			index = j;
//			j = i + 1;
//		}
//	}
//	if (atoi(buff.c_str()) != 221)
//	{
//		error = "发送QUIT错误 ";
//		error += buff;
//		return false;
//	}
//
//	buff = buff.c_str() + index;
//
//	//关闭链接
//	closesocket(sockClient);
//
//	//
//	title.clear();
//	content.clear();
//	target.clear();
//
//	return errorCode(buff);
//}