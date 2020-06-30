#include "stdafx.h"

#include "GWSystemMsg.h"

UINT GWSystemMsgHandler::Execute(GWSystemMsg* pPacket, Player* pPlayer) {
  __ENTER_FUNCTION

  return PACKET_EXE_CONTINUE;

  __LEAVE_FUNCTION

  return PACKET_EXE_ERROR;
}

#include "GWAskMail.h"

UINT GWAskMailHandler::Execute(GWAskMail* pPacket, Player* pPlayer) {
  __ENTER_FUNCTION

  return PACKET_EXE_CONTINUE;

  __LEAVE_FUNCTION

  return PACKET_EXE_ERROR;
}

#include "GCEnterScene.h"

UINT GCEnterSceneHandler::Execute(GCEnterScene* pPacket, Player* pPlayer) {
  __ENTER_FUNCTION

  return PACKET_EXE_CONTINUE;

  __LEAVE_FUNCTION

  return PACKET_EXE_ERROR;
}