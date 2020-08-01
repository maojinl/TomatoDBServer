#include "stdafx.h"


#include "Packet.h"

Packet::Packet( )
{
__ENTER_FUNCTION_FOXNET

	SetPacketRetFlag(PRF_SUCCESS);
	m_Status = 0;
	m_ProcessTime = 0 ;

__LEAVE_FUNCTION_FOXNET
}

Packet::~Packet( )
{
__ENTER_FUNCTION_FOXNET



__LEAVE_FUNCTION_FOXNET
}


UINT Packet::ExecutePacket(Player* pPlayer)
{
	
	g_pLog->FastSaveLog(LOG_FILE_1, "Executing packet %d in thread %d",
		this->GetPacketID(), MyGetCurrentThreadID());
	return Execute(pPlayer);
}

