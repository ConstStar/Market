#include <CQEVE.h>
#include <CQAPI.h>
#include <CQAPI_EX.h>

#include "APPINFO.h"

#include <Windows.h>
#include <thread>
#include <string>

#include "Fun.hpp"
#include "FreeResFile.hpp"

using namespace std;
using namespace CQ;


//请加上static,表示这个logger只有本cpp有效


//应用已被启用
EVE_Enable(Enable)
try
{
	OpenWin::close();
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
		return 0;


	ph->detach();
	Conf::keyFun();
	Conf::initConf();

	logger.Info("应用被启用");
	return 0;
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
EVE_Disable(Disable)
try
{
	logger.Info("应用被停用");

	OpenWin::close();

	return 0;
}
catch (exception & e)
{
	logger.Info(string("“应用即将被停用” 出现崩溃已被阻止 原因:") + e.what());
}
catch (...)
{
	logger.Info("“应用即将被停用” 出现崩溃已被阻止 原因:未知");
}


EVE_Exit(Exit)
{
	logger.Info("酷Q关闭");
	OpenWin::close();

	return 0;
}



MUST_AppInfo_RETURN(CQAPPID)


//操作


//群成员添加
EVE_System_GroupMemberIncrease(intoGroup)
try
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");
	}

	SendEmail a(fromGroup, beingOperateQQ, "成员进群");
	a.send();

	return 0;
}
catch (exception & e)
{
	logger.Info(string("“群成员添加” 出现崩溃已被阻止 原因:") + e.what());
}
catch (...)
{
	logger.Info("“群成员添加” 出现崩溃已被阻止 原因:未知");
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
		SendEmail a(fromGroup, beingOperateQQ, "成员退群");
		a.send();
	}
	return 0;
}
catch (exception & e)
{
	logger.Info(string("“群成员退出” 出现崩溃已被阻止 原因:") + e.what());
}
catch (...)
{
	logger.Info("“群成员退出” 出现崩溃已被阻止 原因:未知");
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
}
catch (...)
{
	logger.Info("“好友添加” 出现崩溃已被阻止 原因:未知");
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
}
catch (...)
{
	logger.Info("“群添加” 出现崩溃已被阻止 原因:未知");
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
}
catch (...)
{
	logger.Info("“私聊消息” 出现崩溃已被阻止 原因:未知");
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

	KeyWordMsg a(fromGroup, fromQQ, msg);
	a.KeyWordFun();

	return 0;
}
catch (exception & e)
{
	logger.Info(string("“群消息” 出现崩溃已被阻止 原因:") + e.what());
}
catch (...)
{
	logger.Info("“群消息” 出现崩溃已被阻止 原因:未知");
}


//菜单
EVE_Menu(__menuSet)
try
{
	if (g_otherSet.appRun == false)
	{
		MessageBox(NULL, L"软件正在检测秘钥中，请稍等\n如果长时间提示未激活，请尝试手动重启酷Q", L"未激活", MB_OK);
		return 0;
	}

	if (OpenWin::openWin() == false)
	{
		MessageBox(NULL, L"界面打开失败,请查看日志中错误原因", L"失败", MB_OK);
	}

	return 0;
}
catch (exception & e)
{
	logger.Info(string("“菜单” 出现崩溃已被阻止 原因:") + e.what());
}
catch (...)
{
	logger.Info("“菜单” 出现崩溃已被阻止 原因:未知");
}