//<pre name = "code" class = "cpp">// UseLibCurl.cpp : 定义控制台应用程序的入口点。  
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

	//开始下载
	bool start()
	{
		if (fp == NULL)
		{
			error = "文件打开失败";
			return false;
		}

		//初始化curl，这个是必须的  
		CURL* curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		//设置接收数据的回调  
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DownloadCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		//curl_easy_setopt(curl, CURLOPT_INFILESIZE, lFileSize);  
		//curl_easy_setopt(curl, CURLOPT_HEADER, 1);  
		//curl_easy_setopt(curl, CURLOPT_NOBODY, 1);  
		//curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);  
		// 设置重定向的最大次数  
		curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5);
		// 设置301、302跳转跟随location  
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
		//设置进度回调函数  
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);
		curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &Speed);
		//curl_easy_getinfo(curl,  CURLINFO_CONTENT_LENGTH_DOWNLOAD, &lFileSize);  
		//curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, g_hDlgWnd);  
		//开始执行请求  
		CURLcode retcCode = curl_easy_perform(curl);

		//清理curl，和前面的初始化匹配  
		curl_easy_cleanup(curl);

		//关闭文件
		fclose(fp);

		if (retcCode != CURLcode::CURLE_OK)
		{
			//查看是否有出错信息  
			error = curl_easy_strerror(retcCode);
			return false;

		}

		//删除原来的文件
		remove(path.c_str());

		//移动文件
		if (rename(temp_path.c_str(), path.c_str()) != 0)
		{
			return false;
		}

		return true;
	}

	bool open()
	{
		//界面打开方式
		int ret = WinExec(path.c_str(), SW_SHOWNORMAL);

		if (ret > 31)
		{
			return true;
		}
		else
		{
			error = "文件打开失败 错误码" + to_string(ret);
			return false;
		}
	}


	//获取错误消息
	string& get_error()
	{
		return error;
	}

private:

	static size_t DownloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, FILE* fp)
	{
		//把下载到的数据以追加的方式写入文件(一定要有a，否则前面写入的内容就会被覆盖了)  

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
		//通知进度条更新下载进度  

		*clientp = nPos;

		/*system("cls");
		printf("已经下载 %d %%\n", nPos);
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

	int& Speed;//进度
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
//		printf("下载成功");
//	}
//	else
//	{
//		printf("下载失败");
//	}
//
//	////移动文件
//	//if (rename("D://test.temp", "D://test.zip") != 0)
//	//{
//	//	printf("失败");
//	//}
//	//else
//	//{
//	//	printf("成功");
//	//}
//
//	return 0;
//}