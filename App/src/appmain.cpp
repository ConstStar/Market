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
{
	appFile = CQ::getAppDirectory();

	logger.testLog("应用已被启用");


	if (FreeResFile::oneStart() == false)
		return 0;
	logger.testLog("End oneStart");


	thread* ph = new thread([]()
		{

			while (true)
			{
				Sleep(1000 * 60 * 60 * 24);
				Conf::keyFun();
			}

		}
	);
	ph->detach();
	Conf::keyFun();
	Conf::initConf();

	logger.testLog("End 应用被启用");
	logger.Info("应用被启用");
	return 0;
}

EVE_Disable(Disable)
{
	logger.Info("应用被停用");
	logger.testLog("应用被停用");
	return 0;
}

MUST_AppInfo_RETURN(CQAPPID)


//操作


//群成员添加
EVE_System_GroupMemberIncrease(intoGroup)
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");
	}

	logger.testLog("群成员添加");
	SendEmail a(fromGroup, beingOperateQQ, "成员进群");
	a.send();
	logger.testLog("End 群成员添加");

	return 0;
}


//群成员退出
EVE_System_GroupMemberDecrease(exitGroup)
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");

		return 0;
	}
	logger.testLog("群成员退出");

	if (g_otherSet.quitGroupSend)
	{
		SendEmail a(fromGroup, beingOperateQQ, "成员退群");
		a.send();
	}
	logger.testLog("End 群成员退出");
	return 0;
}


//好友添加
EVE_Request_AddFriend(addFriend)
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");
		return 0;
	}

	logger.testLog("好友添加");
	if (g_otherSet.addFriend)
	{
		CQ::setFriendAddRequest(responseFlag, 请求_通过, "");
	}

	logger.testLog("End 好友添加");
	return 0;
}


//群添加
EVE_Request_AddGroup(addGroup)
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");
		return 0;
	}

	logger.testLog("群添加");
	if (subType == 2)
	{
		if (g_otherSet.addGroupInto)
		{
			CQ::setGroupAddRequest(responseFlag, 请求_群邀请, 请求_通过, "");
		}

	}
	logger.testLog("End 群添加");
	return 0;
}


//私聊消息
EVE_PrivateMsg(privateMsg)
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");
		return 0;
	}

	return 0;
}


//群消息
EVE_GroupMsg(groupMsg)
{
	if (g_otherSet.appRun == false)
	{
		logger.Info("请先激活软件");
		return 0;
	}

	logger.testLog("群消息");
	KeyWordMsg a(fromGroup, fromQQ, msg);
	a.KeyWordFun();
	logger.testLog("End 群消息");
	return 0;
}


//菜单
EVE_Menu(__menuSet)
{
	if (g_otherSet.appRun == false)
	{
		MessageBox(NULL, L"请激活后使用，插件可能正在检测是否激活", L"未激活", MB_OK);
		return 0;
	}

	logger.testLog("菜单");
	if (OpenWin::openWin() == false)
	{
		MessageBox(NULL, L"界面打开失败,请查看日志中错误原因", L"失败", MB_OK);
	}

	logger.testLog("End 菜单");
	return 0;
}