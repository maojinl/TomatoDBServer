
/************************************************************************
*  更新时间 2010.7.23
*  更新人:  DGH
*  文件名:	WGMail.h
*  功能:	world转发邮件给server。
*			执行脚本内容(执行完所有的脚本邮件)；
*			实现普通邮件(系统邮件)转发;
************************************************************************/

#include "stdafx.h"


#include "WGMail.h"
#include "Log.h"
#include "ServerManager.h"
#include "GamePlayer.h"
#include "PlayerPool.h"
#include "Scene.h"
#include "Obj_Human.h"
#include "WorkerManager.h"

#include "GWAskMail.h"

#define SCRIPT_MAIL 888889   //邮件脚本的LUA调用接口ID


UINT WGMailHandler::Execute( WGMail* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
