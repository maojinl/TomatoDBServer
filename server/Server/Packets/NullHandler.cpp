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

#include "SCRetDBDefinition.h"

UINT SCRetDBDefinitionHandler::Execute(SCRetDBDefinition* pPacket, Player* pPlayer) {
	__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "SCRetDBManipulate.h"

UINT SCRetDBManipulateHandler::Execute(SCRetDBManipulate* pPacket, Player* pPlayer) {
	__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "SCRetDBQuery.h"

UINT SCRetDBQueryHandler::Execute(SCRetDBQuery* pPacket, Player* pPlayer) {
	__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}