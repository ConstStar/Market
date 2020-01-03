#include <Windows.h>
#include <random>

class MySqlKey
{

public:

	//��Կ�Ա� ���µ�¼ʱ��   ����ֵ     0 ͨ��  1 ����  2����������  3��Կ������   -1��֤�쳣
	static int keyComp(string& key, string& ExceedDateTime, string& computerId)
	{

		try {
			typedef int(*Pwinfun)(const char* key, char* ExceedDateTime, const char* computerId, const char* num);
			HINSTANCE hDLL;

			Pwinfun PkeyComp = NULL;

			//�������dll
			hDLL = LoadLibrary(L"MySql.dll"); //���ض�̬���ӿ�MyDll.dll�ļ���

			if (hDLL == NULL) {
				MessageBoxA(NULL, "��Ҫdll��ȡʧ��", "����", NULL);
				//logger.Info("�����ʧ��");
				return false;
			}
			else
			{
				//ָ��dll�д򿪽��溯��
				PkeyComp = (Pwinfun)GetProcAddress(hDLL, "keyComp");

			}

			if (keyComp == NULL)
			{
				MessageBoxA(NULL, "��Ҫdll����ʧ��", "����", NULL);
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