
/************************************************************************
*  ����ʱ�� 2010.7.23
*  ������:  DGH
*  �ļ���:	WGMail.h
*  ����:	worldת���ʼ���server��
*			ִ�нű�����(ִ�������еĽű��ʼ�)��
*			ʵ����ͨ�ʼ�(ϵͳ�ʼ�)ת��;
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

#define SCRIPT_MAIL 888889   //�ʼ��ű���LUA���ýӿ�ID


UINT WGMailHandler::Execute( WGMail* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
