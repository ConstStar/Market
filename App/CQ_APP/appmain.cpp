






//您应当先看appinfo.h





//现在，您已经可以尝试开始编译你的第一个插件,虽然它只包含一些测试项目和示例
//编译完成后，你将得到DLL以及JSON文件
//请遵循官方文档启用插件
//https://docs.cqp.im/dev/v9/getting-started/



#include "Fun.hpp"

#include <CQSDK.h>
#include "appinfo.h"

//--------应用正式开始--------
//本cpp讲述如何在插件启动和停止时执行必要的初始化和收尾工作



MUST_AppInfo_RETURN(APP_ID)



//请加上static,表示这个logger只有本cpp有效
//static Logger logger("");





//使用EVE_开头的宏指令
//可以快速生成一条符合要求的事件函数
//使您无需关心这个函数需要怎样的格式
//即可快速开始使用
EVE_Startup_EX(Startup)
//name:酷Q启动
//priority:30000
/*
以上2行为注释,用于json自动生成
name为事件名称,一般标识用途,不需要表明事件类型
priority为事件优先级(参见 cq.im/deveventpriority)
开头必须为<//name:>或<//priority:>,不得有空格等
如果没有name,默认为事件名
如果没有priority,默认为30000
不要包含{字符,否则视为结束
*/

{
	//logger.Info("Startup");
	//本函数在执行周期最多只会执行一次
	//可以在这里加载全局资源
}



//接下来请转向 Msg.cpp 以继续



//应用已被启用
EVE_Enable_EX(Enable)
try
{
	appFile = CQ::getAppDirectory();

	//检查秘钥
	thread* ph = new thread([]()
		{

			while (true)
			{
				Sleep(1000 * 60 * 60 * 24);
				Conf::keyFun();
			}

		}
	);

	//检查是否为第一次启动
	if (FreeResFile::oneStart() == false)
		return;


	ph->detach();
	Conf::keyFun();
	Conf::initConf();

	logger.Info("应用被启用");


	//OpenWin::openWin();
	return;
}
catch (exception & e)
{
	logger.Info(string("“应用已被启用” 出现崩溃已被阻止 原因:") + e.what());	
}
catch (...)
{
	logger.Info("“应用已被启用” 出现崩溃已被阻止 原因:未知");
}


//应用被停用
EVE_Disable_EX(Disable)
try
{
	//关闭界面
	string closeWin = to_string(PIPEMSGTYPE::COMMAND) + "close";
	WinPipe.WriteData(closeWin);


	//logger.Info("应用被停用");
}
catch (exception & e)
{
	logger.Info(string("“应用即将被停用” 出现崩溃已被阻止 原因:") + e.what());
}
catch (...)
{
	logger.Info("“应用即将被停用” 出现崩溃已被阻止 原因:未知");
}


EVE_Exit_EX(Exit)
{
	//关闭界面
	string closeWin = to_string(PIPEMSGTYPE::COMMAND) + "close";
	WinPipe.WriteData(closeWin);


	//logger.Info("酷Q关闭");
}

//操作


//群成员添加
EVE_System_GroupMemberIncrease(intoGroup)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");
	}

	SendEmail a(fromGroup, beingOperateAccount, "成员进群");
	a.send();

	return 0;
}
catch (exception & e)
{
	logger.Info(string("“群成员添加” 出现崩溃已被阻止 原因:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("“群成员添加” 出现崩溃已被阻止 原因:未知");
	return 0;
}



//群成员退出
EVE_System_GroupMemberDecrease(exitGroup)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");

		return 0;
	}

	if (g_otherSet.quitGroupSend)
	{
		SendEmail a(fromGroup, beingOperateAccount, "成员退群");
		a.send();
	}
	return 0;
}
catch (exception & e)
{
	logger.Info(string("“群成员退出” 出现崩溃已被阻止 原因:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("“群成员退出” 出现崩溃已被阻止 原因:未知");
	return 0;
}


//好友添加
EVE_Request_AddFriend(addFriend)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");
		return 0;
	}

	if (g_otherSet.addFriend)
	{
		CQ::setFriendAddRequest(responseFlag, 请求_通过, "");
	}

	return 0;
}
catch (exception & e)
{
	logger.Info(string("“好友添加” 出现崩溃已被阻止 原因:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("“好友添加” 出现崩溃已被阻止 原因:未知");
	return 0;
}


//群添加
EVE_Request_AddGroup(addGroup)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");
		return 0;
	}
	if (subType == 2)
	{
		if (g_otherSet.addGroupInto)
		{
			CQ::setGroupAddRequest(responseFlag, 请求_群邀请, 请求_通过, "");
		}

	}
	return 0;
}
catch (exception & e)
{
	logger.Info(string("“群添加” 出现崩溃已被阻止 原因:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("“群添加” 出现崩溃已被阻止 原因:未知");
	return 0;
}


//私聊消息
EVE_PrivateMsg(privateMsg)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");
		return 0;
	}

	return 0;
}
catch (exception & e)
{
	logger.Info(string("“私聊消息” 出现崩溃已被阻止 原因:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("“私聊消息” 出现崩溃已被阻止 原因:未知");
	return 0;
}


//群消息
EVE_GroupMsg(groupMsg)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");
		return 0;
	}

	//忽略匿名消息
	if (fromAccount == 80000000)
		return 0;


	KeyWordMsg a(fromGroup, fromAccount, msg);
	a.KeyWordFun();

	return 0;
}
catch (exception & e)
{
	logger.Info(string("“群消息” 出现崩溃已被阻止 原因:") + e.what());
	return 0;
}
catch (...)
{
	logger.Info("“群消息” 出现崩溃已被阻止 原因:未知");
	return 0;
}


//菜单
EVE_Menu_EX(menu)
//name:设置
try
{
	if (g_otherSet.appRun == false)
	{
		MessageBox(NULL, L"软件正在检测秘钥中，请稍等\n如果长时间提示未激活，请尝试手动重启酷Q", L"未激活", MB_OK);
		return;
	}

	if (OpenWin::openWin() == false)
	{
		MessageBox(NULL, L"界面打开失败,请查看日志中错误原因", L"失败", MB_OK);
	}

	return ;
}
catch (exception & e)
{
	logger.Info(string("“菜单” 出现崩溃已被阻止 原因:") + e.what());
}
catch (...)
{
	logger.Info("“菜单” 出现崩溃已被阻止 原因:未知");
}