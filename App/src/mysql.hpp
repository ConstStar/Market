#include <Windows.h>
#include <random>

class MySqlKey
{

public:

	//秘钥对比 更新登录时间   返回值     0 通过  1 过期  2机器码有误  3秘钥不存在   -1验证异常
	static int keyComp(string& key, string& ExceedDateTime, string& computerId)
	{

		try {
			typedef int(*Pwinfun)(const char* key, char* ExceedDateTime, const char* computerId, const char* num);
			HINSTANCE hDLL;

			Pwinfun PkeyComp = NULL;

			//导入界面dll
			hDLL = LoadLibrary(L"MySql.dll"); //加载动态链接库MyDll.dll文件；

			if (hDLL == NULL) {
				MessageBoxA(NULL, "重要dll获取失败", "错误", NULL);
				//logger.Info("界面打开失败");
				return false;
			}
			else
			{
				//指向dll中打开界面函数
				PkeyComp = (Pwinfun)GetProcAddress(hDLL, "keyComp");

			}

			if (keyComp == NULL)
			{
				MessageBoxA(NULL, "重要dll加载失败", "错误", NULL);
				return false;
			}

			char temp_ExceedDateTime[30];

			srand(time(NULL));

			int num1 = rand() % 769;
			int num2 = rand() % 13498;

			char num_str[512];
			_itoa(num2, num_str, 36);
			string temp_str = to_string(num1) + num_str;

			strcpy(num_str, temp_str.c_str());

			int ret = PkeyComp(key.c_str(), temp_ExceedDateTime, computerId.c_str(), num_str);
			ExceedDateTime = temp_ExceedDateTime;

			FreeLibrary(hDLL);


			int temp_num = atoi(num_str) + 7;
			temp_num *= 3 * temp_num;

			ret -= temp_num;

			return ret;

		}
		catch (...) {

			return -1;
		}

		return -1;
	}

};