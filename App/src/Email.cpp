//#include "Email.h"
////#include <afx.h>//�쳣��
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
//int Csmtp::SendAttachment(SOCKET& sockClient) /*���͸���*/
//{
//	for (std::vector<string>::iterator iter = filename.begin(); iter != filename.end(); iter++)
//	{
//		cout << "Attachment is sending������ " << endl;
//
//		string path = *iter;
//		ifstream ifs(path, ios::in | ios::binary); //'������2�����ԣ������롢�����ƴ�'
//		if (false == ifs.is_open())
//		{
//			cout << "�޷����ļ���" << endl;
//			return 1;
//		}
//
//		string sendstring;
//		sendstring = "--@boundary@\r\nContent-Type: application/octet-stream; name=\"1.jpg\"\r\n";
//		sendstring += "Content-Disposition: attachment; filename=\"1.jpg\"\r\n";
//		sendstring += "Content-Transfer-Encoding: base64\r\n\r\n";
//		send(sockClient, sendstring.c_str(), sendstring.length(), 0);
//
//		//infile.read((char*)buffer,sizeof(��������));
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
//			cout << "�������ͳ���!" << endl;
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
//	//WSAStarup����WSA(Windows SocKNDs Asynchronous��Windows�׽����첽)����������
//	int err = WSAStartup(wVersionRequested, &wsaData);
//	//cout << "WSAStartup(0:successful):" << err << endl;
//
//	//char namebuf[128];    //��ñ��ؼ������
//	//string ip_list;
//	//if (0 == gethostname(namebuf, 128))
//	//{
//	//	struct hostent* pHost;  //��ñ���IP��ַ
//	//	pHost = gethostbyname(namebuf);  //pHost���ص���ָ���������б�
//	//	for (int i = 0; pHost != NULL && pHost->h_addr_list[i] != NULL; i++)
//	//	{
//	//		string tem = inet_ntoa(*(struct in_addr*)pHost->h_addr_list[i]);
//	//		ip_list += tem;
//	//		ip_list += "\n";
//	//	}
//	//}
//	//else
//	//{
//	//	cout << "��ȡ������Ϣʧ��..." << endl;
//	//}
//	////////////////////////////////////////////////////////////////////////////
//	//title = namebuf;// �ʼ�����
//	//content = ip_list; //����ip
//
//
//	if (title.empty())
//	{
//		cout << "���ⲻ��Ϊ��" << endl;
//		error = "���ⲻ��Ϊ��";
//		return false;
//	}
//
//	if (content.empty())
//	{
//		cout << "���ݲ���Ϊ��" << endl;
//		error = "���ݲ���Ϊ��";
//		return false;
//	}
//
//
//	if (target.empty())
//	{
//		cout << "�ռ��˲���Ϊ��" << endl;
//		error = "�ռ��˲���Ϊ��";
//		return false;
//	}
//
//
//	sockClient = socket(AF_INET, SOCK_STREAM, 0); //����socket����  
//
//	int recvTimeout = 200;  //0.2s
//	setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, (char*)&recvTimeout, sizeof(int));
//
//	pHostent = gethostbyname(domain.c_str()); //�õ��й�����������Ϣ
//
//	if (pHostent == NULL)
//	{
//		cout << "��������ʧ�ܣ�Ҳ��û������" << endl;
//		error = "�����쳣������������������";
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
//	//��ȷ�ķ�����
//	if (code == 250 || code == 251 || code == 221)
//	{
//		error = buf;
//		return true;
//	}
//
//	//����ķ�����
//	if (code == 501 || code == 551 || code == 550)
//	{
//		error = "����������ܲ����� ������Ϣ:" + buf;
//	}
//
//	this->error = buf;
//	return false;
//}
//
////��֤���������		���� 0��������ȷ  1����δע��  -1�����쳣
//int Csmtp::verify()
//{
//	WSADATA wsaData;
//	WORD wVersionRequested = MAKEWORD(2, 1);
//	//WSAStarup����WSA(Windows SocKNDs Asynchronous��Windows�׽����첽)����������
//	int err = WSAStartup(wVersionRequested, &wsaData);
//
//	sockClient = socket(AF_INET, SOCK_STREAM, 0); //����socket����  
//
//	int recvTimeout = 200;  //0.2s
//	setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, (char*)&recvTimeout, sizeof(int));
//
//	pHostent = gethostbyname(domain.c_str()); //�õ��й�����������Ϣ
//
//	if (pHostent == NULL)
//	{
//		cout << "��������ʧ�ܣ�Ҳ��û������" << endl;
//		error = "�����쳣������������������";
//		return -1;
//	}
//
//	char* ecode;
//
//	string buff;
//	err = 0;
//	string message; //
//
//	SOCKADDR_IN addrServer;  //����˵�ַ
//	addrServer.sin_addr.S_un.S_addr = *((DWORD*)pHostent->h_addr_list[0]); //�õ�smtp�������������ֽ����ip��ַ     
//
//
//	addrServer.sin_family = AF_INET;
//	addrServer.sin_port = htons(port); //���Ӷ˿�25 
//	//int connect (SOCKET s , const struct sockaddr FAR *name , int namelen );
//	err = connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));   //���������������  
//
//
//	if (err)
//	{
//		error = "������������������";
//		return -1;
//	}
//
//
//	//cout << "connect:" << err << endl;
//	//telnet smtp.126.com 25 ���ӷ���������
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//220 smtp.qq.com Esmtp QQ Mail Server
//	//����sock
//	int ret = MyRecv(sockClient, buff);
//
//	//cout << "connect:" << buff << endl;
//	if (atoi(buff.c_str()) != 220)
//	{
//		error = "�������Ӵ��� ";
//		error += buff;
//		return -1;
//	}
//
//	message = "ehlo 126.com\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//250
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "helo:" << buff << endl;
//	if (atoi(buff.c_str()) != 250)
//	{
//		error = "����ehlo���� ";
//		error += buff;
//		return -1;
//	}
//
//	message = "auth login \r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 VXNlcm5hbWU6
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "auth login:" << buff << endl;
//	//�ϴ�������
//	message = user;
//	ecode = base64Encode(message.c_str(), strlen(message.c_str()));
//	message = ecode;
//	message += "\r\n";
//	delete[]ecode;
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 UGFzc3dvcmQ6
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "usrname:" << buff << endl;
//	if (atoi(buff.c_str()) != 334)
//	{
//		error = "���������˺Ŵ��� ";
//		error += buff;
//		return -1;
//	}
//
//
//	//�ϴ���������
//	message = pass;
//	ecode = base64Encode(message.c_str(), strlen(message.c_str()));
//	message = ecode;
//	delete[]ecode;
//	message += "\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 UGFzc3dvcmQ6//235 OK Authenticated
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "password:" << buff << endl;
//	if (atoi(buff.c_str()) != 334 && atoi(buff.c_str()) != 235)
//	{
//		error = "��������������� ";
//		error += buff;
//		return -1;
//	}
//
//	message = "mail from:<" + user + ">\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//235 Authentication successful //250 ok\r\n
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "mail from: " << buff << endl;
//	if (atoi(buff.c_str()) != 235 && atoi(buff.c_str()) != 250)
//	{
//		error = "���ͷ������������ ";
//		error += buff;
//		return -1;
//	}
//
//
//	message = "rcpt to:<" + target + ">\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//250
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "rcpt to: " << buff << endl;
//
//	//�ر�����
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
//	//��ȡ���һ����Ϣ
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
//	//��֤����ֵ�Ƿ���ȷ
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
//			//������������
//			temp[ret] = '\0';
//			buff += temp;
//		}
//		else
//		{
//			if ((ret < 0) && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
//			{
//				continue;//������������
//			}
//			if (t)
//				break;//��������ѭ��
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
//	//SOCKADDR_IN addrServer;  //����˵�ַ
//	addrServer.sin_addr.S_un.S_addr = *((DWORD*)pHostent->h_addr_list[0]); //�õ�smtp�������������ֽ����ip��ַ     
//
//
//	addrServer.sin_family = AF_INET;
//	addrServer.sin_port = htons(port); //���Ӷ˿�25 
//	//int connect (SOCKET s , const struct sockaddr FAR *name , int namelen );
//	err = connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));   //���������������  
//
//
//	if (err)
//	{
//		error = "������������������";
//		return false;
//	}
//
//
//	//cout << "connect:" << err << endl;
//	//telnet smtp.126.com 25 ���ӷ���������
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//220 smtp.qq.com Esmtp QQ Mail Server
//	//����sock
//	int ret = MyRecv(sockClient, buff);
//
//	//cout << "connect:" << buff << endl;
//	if (atoi(buff.c_str()) != 220)
//	{
//		error = "�������Ӵ��� ";
//		error += buff;
//		return false;
//	}
//
//	message = "ehlo 126.com\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//250
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "helo:" << buff << endl;
//	if (atoi(buff.c_str()) != 250)
//	{
//		error = "����ehlo���� ";
//		error += buff;
//		return false;
//	}
//
//	message = "auth login \r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 VXNlcm5hbWU6
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "auth login:" << buff << endl;
//	//�ϴ�������
//	message = user;
//	ecode = base64Encode(message.c_str(), strlen(message.c_str()));
//	message = ecode;
//	message += "\r\n";
//	delete[]ecode;
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 UGFzc3dvcmQ6
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "usrname:" << buff << endl;
//	if (atoi(buff.c_str()) != 334)
//	{
//		error = "���������˺Ŵ��� ";
//		error += buff;
//		return false;
//	}
//
//
//	//�ϴ���������
//	message = pass;
//	ecode = base64Encode(message.c_str(), strlen(message.c_str()));
//	message = ecode;
//	delete[]ecode;
//	message += "\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//334 UGFzc3dvcmQ6//235 OK Authenticated
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "password:" << buff << endl;
//	if (atoi(buff.c_str()) != 334 && atoi(buff.c_str()) != 235)
//	{
//		error = "��������������� ";
//		error += buff;
//		return false;
//	}
//
//	message = "mail from:<" + user + ">\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//235 Authentication successful //250 ok\r\n
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "mail from: " << buff << endl;
//	if (atoi(buff.c_str()) != 235 && atoi(buff.c_str()) != 250)
//	{
//		error = "���ͷ������������ ";
//		error += buff;
//		return false;
//	}
//
//
//	message = "rcpt to:<" + target + ">\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//	//buff[recv(sockClient, buff, 500, 0)] = '\0';//250
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	//cout << "rcpt to: " << buff << endl;
//	if (atoi(buff.c_str()) != 235 && atoi(buff.c_str()) != 250)
//	{
//		error = "���ͽ������������ ";
//		error += buff;
//		return false;
//	}
//
//
//	message = "data\r\n";//dataҪ��������һ��
//	send(sockClient, message.c_str(), message.length(), 0);
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	if (atoi(buff.c_str()) != 354)
//	{
//		error = "����data���� ";
//		error += buff;
//		return false;
//	}
//
//
//	//cout << "data: " << buff << endl;
//	///-----------------------------------------DATA-------------------------------------
//	//Ҫʹ��Csmtp ���͸���, ��Ҫ��Csmtp ͷ��Ϣ����˵��, �ı�Content-type ��Ϊÿһ���������BOUNDARY ��,
//	//cout << "-------------------DATA------------------------" << endl;
//	//  ͷ
//
//	message = "from:" + name + " <" + user + ">\r\nto:<" + target + ">\r\nsubject:" + title + "\r\n";
//	message += "MIME-Version: 1.0\r\n";
//	message += "Content-Type: multipart/mixed;boundary=@boundary@\r\n\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//
//	/*"Content-type: text/html; charset=iso-8859-1\r\n"
//		"Content-Transfer-Encoding: base64\r\n\r\n";*/
//
//		//  ����
//	std::string type = is_html ? "html" : "plain";//�ж�Ϊhtml���ͻ��Ǵ��ı�����
//
//	message = "--@boundary@\r\nContent-Type: text/" + type;
//	message += ";charset=\"gb2312\"\r\n\r\n" + content + "\r\n\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//
//	//------------------------------------------------------------------------------------------------
//	//  ���͸���
//
//	SendAttachment(sockClient);
//
//	/*���ͽ�β��Ϣ*/
//	message = "--@boundary@--\r\n.\r\n";
//	send(sockClient, message.c_str(), message.length(), 0);
//
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	if (atoi(buff.c_str()) != 250)
//	{
//		error = "���ͽ�β��Ϣ���� ";
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
//	//����sock
//	ret = MyRecv(sockClient, buff);
//
//	int index = 0;
//	//��ȡ���һ����Ϣ
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
//		error = "����QUIT���� ";
//		error += buff;
//		return false;
//	}
//
//	buff = buff.c_str() + index;
//
//	//�ر�����
//	closesocket(sockClient);
//
//	//
//	title.clear();
//	content.clear();
//	target.clear();
//
//	return errorCode(buff);
//}