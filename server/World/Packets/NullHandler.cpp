#include "stdafx.h"

#include "WGSystemMsg.h"

UINT WGSystemMsgHandler::Execute(WGSystemMsg* pPacket, Player* pPlayer) {
  __ENTER_FUNCTION

  return PACKET_EXE_CONTINUE;

  __LEAVE_FUNCTION

  return PACKET_EXE_ERROR;
}

#include "WGMail.h"

UINT WGMailHandler::Execute(WGMail* pPacket, Player* pPlayer) {
  __ENTER_FUNCTION

  return PACKET_EXE_CONTINUE;

  __LEAVE_FUNCTION

  return PACKET_EXE_ERROR;
}