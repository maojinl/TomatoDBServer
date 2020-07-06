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

#include "SCRetLogin.h"

UINT SCRetLoginHandler::Execute(SCRetLogin* pPacket, Player* pPlayer) {
  __ENTER_FUNCTION

  return PACKET_EXE_CONTINUE;

  __LEAVE_FUNCTION

  return PACKET_EXE_ERROR;
}

#include "SCRetCreateDB.h"

UINT SCRetCreateDBHandler::Execute(SCRetCreateDB* pPacket, Player* pPlayer) {
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}