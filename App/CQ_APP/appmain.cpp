






//��Ӧ���ȿ�appinfo.h





//���ڣ����Ѿ����Գ��Կ�ʼ������ĵ�һ�����,��Ȼ��ֻ����һЩ������Ŀ��ʾ��
//������ɺ��㽫�õ�DLL�Լ�JSON�ļ�
//����ѭ�ٷ��ĵ����ò��
//https://docs.cqp.im/dev/v9/getting-started/



#include "Fun.hpp"

#include <CQSDK.h>
#include "appinfo.h"

//--------Ӧ����ʽ��ʼ--------
//��cpp��������ڲ��������ֹͣʱִ�б�Ҫ�ĳ�ʼ������β����



MUST_AppInfo_RETURN(APP_ID)



//�����static,��ʾ���loggerֻ�б�cpp��Ч
//static Logger logger("");





//ʹ��EVE_��ͷ�ĺ�ָ��
//���Կ�������һ������Ҫ����¼�����
//ʹ������������������Ҫ�����ĸ�ʽ
//���ɿ��ٿ�ʼʹ��
EVE_Startup_EX(Startup)
//name:��Q����
//priority:30000
/*
����2��Ϊע��,����json�Զ�����
nameΪ�¼�����,һ���ʶ��;,����Ҫ�����¼�����
priorityΪ�¼����ȼ�(�μ� cq.im/deveventpriority)
��ͷ����Ϊ<//name:>��<//priority:>,�����пո��
���û��name,Ĭ��Ϊ�¼���
���û��priority,Ĭ��Ϊ30000
��Ҫ����{�ַ�,������Ϊ����
*/

{
	//logger.Info("Startup");
	//��������ִ���������ֻ��ִ��һ��
	//�������������ȫ����Դ
}



//��������ת�� Msg.cpp �Լ���



//Ӧ���ѱ�����
EVE_Enable_EX(Enable)
try
{
	appFile = CQ::getAppDirectory();

	//�����Կ
	thread* ph = new thread([]()
		{

			while (true)
			{
				Sleep(1000 * 60 * 60 * 24);
				Conf::keyFun();
			}

		}
	);

	//����Ƿ�Ϊ��һ������
	if (FreeResFile::oneStart() == false)
		return;


	ph->detach();
	Conf::keyFun();
	Conf::initConf();

	logger.Info("Ӧ�ñ�����");


	//OpenWin::openWin();
	return;
}
catch (exception & e)
{
	logger.Info(string("��Ӧ���ѱ����á� ���ֱ����ѱ���ֹ ԭ��:") + e.what());	
}
catch (...)
{
	logger.Info("��Ӧ���ѱ����á� ���ֱ����ѱ���ֹ ԭ��:δ֪");
}


//Ӧ�ñ�ͣ��
EVE_Disable_EX(Disable)
try
{
	//�رս���
	string closeWin = to_string(PIPEMSGTYPE::COMMAND) + "close";
	WinPipe.WriteData(closeWin);


	//logger.Info("Ӧ�ñ�ͣ��");
}
catch (exception & e)
{
	logger.Info(string("��Ӧ�ü�����ͣ�á� ���ֱ����ѱ���ֹ ԭ��:") + e.what());
}
catch (...)
{
	logger.Info("��Ӧ�ü�����ͣ�á� ���ֱ����ѱ���ֹ ԭ��:δ֪");
}


EVE_Exit_EX(Exit)
{
	//�رս���
	string closeWin = to_string(PIPEMSGTYPE::COMMAND) + "close";
	WinPipe.WriteData(closeWin);


	//logger.Info("��Q�ر�");
}

//����


//Ⱥ��Ա���
EVE_System_GroupMemberIncrease(intoGroup)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("���ȼ������");
	}

	SendEmail a(fromGroup, beingOperateAccount, "��Ա��Ⱥ");
	a.send();

	return 0;
}
catch (exception & e)
{
	logger.Info(string("��Ⱥ��Ա��ӡ� ���ֱ����ѱ���ֹ ԭ��:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("��Ⱥ��Ա��ӡ� ���ֱ����ѱ���ֹ ԭ��:δ֪");
	return 0;
}



//Ⱥ��Ա�˳�
EVE_System_GroupMemberDecrease(exitGroup)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("���ȼ������");

		return 0;
	}

	if (g_otherSet.quitGroupSend)
	{
		SendEmail a(fromGroup, beingOperateAccount, "��Ա��Ⱥ");
		a.send();
	}
	return 0;
}
catch (exception & e)
{
	logger.Info(string("��Ⱥ��Ա�˳��� ���ֱ����ѱ���ֹ ԭ��:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("��Ⱥ��Ա�˳��� ���ֱ����ѱ���ֹ ԭ��:δ֪");
	return 0;
}


//�������
EVE_Request_AddFriend(addFriend)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("���ȼ������");
		return 0;
	}

	if (g_otherSet.addFriend)
	{
		CQ::setFriendAddRequest(responseFlag, ����_ͨ��, "");
	}

	return 0;
}
catch (exception & e)
{
	logger.Info(string("��������ӡ� ���ֱ����ѱ���ֹ ԭ��:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("��������ӡ� ���ֱ����ѱ���ֹ ԭ��:δ֪");
	return 0;
}


//Ⱥ���
EVE_Request_AddGroup(addGroup)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("���ȼ������");
		return 0;
	}
	if (subType == 2)
	{
		if (g_otherSet.addGroupInto)
		{
			CQ::setGroupAddRequest(responseFlag, ����_Ⱥ����, ����_ͨ��, "");
		}

	}
	return 0;
}
catch (exception & e)
{
	logger.Info(string("��Ⱥ��ӡ� ���ֱ����ѱ���ֹ ԭ��:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("��Ⱥ��ӡ� ���ֱ����ѱ���ֹ ԭ��:δ֪");
	return 0;
}


//˽����Ϣ
EVE_PrivateMsg(privateMsg)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("���ȼ������");
		return 0;
	}

	return 0;
}
catch (exception & e)
{
	logger.Info(string("��˽����Ϣ�� ���ֱ����ѱ���ֹ ԭ��:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("��˽����Ϣ�� ���ֱ����ѱ���ֹ ԭ��:δ֪");
	return 0;
}


//Ⱥ��Ϣ
EVE_GroupMsg(groupMsg)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("���ȼ������");
		return 0;
	}

	//����������Ϣ
	if (fromAccount == 80000000)
		return 0;


	KeyWordMsg a(fromGroup, fromAccount, msg);
	a.KeyWordFun();

	return 0;
}
catch (exception & e)
{
	logger.Info(string("��Ⱥ��Ϣ�� ���ֱ����ѱ���ֹ ԭ��:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("��Ⱥ��Ϣ�� ���ֱ����ѱ���ֹ ԭ��:δ֪");
	return 0;
}


//�˵�
EVE_Menu_EX(menu)
//name:����
try
{
	if (g_otherSet.appRun == false)
	{
		MessageBox(NULL, L"������ڼ����Կ�У����Ե�\n�����ʱ����ʾδ����볢���ֶ�������Q", L"δ����", MB_OK);
		return;
	}

	if (OpenWin::openWin() == false)
	{
		MessageBox(NULL, L"�����ʧ��,��鿴��־�д���ԭ��", L"ʧ��", MB_OK);
	}

	return ;
}
catch (exception & e)
{
	logger.Info(string("���˵��� ���ֱ����ѱ���ֹ ԭ��:") + e.what());
}
catch (...)
{
	logger.Info("���˵��� ���ֱ����ѱ���ֹ ԭ��:δ֪");
}