//<pre name = "code" class = "cpp">// UseLibCurl.cpp : �������̨Ӧ�ó������ڵ㡣  
//  
#include <Windows.h>  
#include <CommCtrl.h>  
#include <curl/curl.h>

#include <string>
#include <fstream>

#include <cstdio>

using namespace std;


class Download
{
public:
	Download(string url, string path, string temp_path, int& Speed) :url(url), path(path), fp(NULL), Speed(Speed), temp_path(temp_path)
	{
		fp = fopen(temp_path.c_str(), "wb+");
	}

	~Download()
	{
		remove(temp_path.c_str());
	}

	//��ʼ����
	bool start()
	{
		if (fp == NULL)
		{
			error = "�ļ���ʧ��";
			return false;
		}

		//��ʼ��curl������Ǳ����  
		CURL* curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		//���ý������ݵĻص�  
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DownloadCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		//curl_easy_setopt(curl, CURLOPT_INFILESIZE, lFileSize);  
		//curl_easy_setopt(curl, CURLOPT_HEADER, 1);  
		//curl_easy_setopt(curl, CURLOPT_NOBODY, 1);  
		//curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);  
		// �����ض����������  
		curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5);
		// ����301��302��ת����location  
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
		//���ý��Ȼص�����  
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);
		curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &Speed);
		//curl_easy_getinfo(curl,  CURLINFO_CONTENT_LENGTH_DOWNLOAD, &lFileSize);  
		//curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, g_hDlgWnd);  
		//��ʼִ������  
		CURLcode retcCode = curl_easy_perform(curl);

		//����curl����ǰ��ĳ�ʼ��ƥ��  
		curl_easy_cleanup(curl);

		//�ر��ļ�
		fclose(fp);

		if (retcCode != CURLcode::CURLE_OK)
		{
			//�鿴�Ƿ��г�����Ϣ  
			error = curl_easy_strerror(retcCode);
			return false;

		}

		//ɾ��ԭ�����ļ�
		remove(path.c_str());

		//�ƶ��ļ�
		if (rename(temp_path.c_str(), path.c_str()) != 0)
		{
			return false;
		}

		return true;
	}

	bool open()
	{
		//����򿪷�ʽ
		int ret = WinExec(path.c_str(), SW_SHOWNORMAL);

		if (ret > 31)
		{
			return true;
		}
		else
		{
			error = "�ļ���ʧ�� ������" + to_string(ret);
			return false;
		}
	}


	//��ȡ������Ϣ
	string& get_error()
	{
		return error;
	}

private:

	static size_t DownloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, FILE* fp)
	{
		//�����ص���������׷�ӵķ�ʽд���ļ�(һ��Ҫ��a������ǰ��д������ݾͻᱻ������)  

		//size_t nWrite = file.write((char*)pBuffer, nSize*nMemByte);
		//printf("%d\n", fp);

		size_t nWrite = fwrite(pBuffer, nSize, nMemByte, fp);

		return nWrite;
	}

	static int ProgressCallback(int* clientp, double dltotal, double dlnow, double ultotal, double ulnow)
	{
		if (dltotal > -0.1 && dltotal < 0.1)
			return 0;
		int nPos = (int)((dlnow / dltotal) * 100);
		//֪ͨ�������������ؽ���  

		*clientp = nPos;

		/*system("cls");
		printf("�Ѿ����� %d %%\n", nPos);
*/
//::Sleep(10);  
		return 0;
	}

private:
	string url;
	string path;
	string temp_path;

	string error;

	FILE* fp;

	int& Speed;//����
};

//int main()
//{
//	int s;
//	Download a("http://101.132.160.17/app/%5B%E5%B0%8F%E5%B0%8F%E5%93%A5%5D%E7%BE%A4%E5%85%B3%E9%94%AE%E8%AF%8D%E7%9B%91%E6%8E%A72.0.0.zip",
//		"D://test.zip", "D://test.temp", s);
//	bool ret=a.start();
//
//	if (ret)
//	{
//		printf("���سɹ�");
//	}
//	else
//	{
//		printf("����ʧ��");
//	}
//
//	////�ƶ��ļ�
//	//if (rename("D://test.temp", "D://test.zip") != 0)
//	//{
//	//	printf("ʧ��");
//	//}
//	//else
//	//{
//	//	printf("�ɹ�");
//	//}
//
//	return 0;
//}