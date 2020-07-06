#include "stdafx.h"

#include "CSAskLogin.h"

BOOL CSAskLogin::Read( SocketInputStream& iStream )
{
__ENTER_FUNCTION
	iStream.Read((CHAR*)(szAccount), sizeof(CHAR) * (MAX_ACCOUNT + 1));
	iStream.Read((CHAR*)(szPassKey), sizeof(CHAR) * (MAX_ACCOUNT + 1));
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL CSAskLogin::Write( SocketOutputStream& oStream )const
{
__ENTER_FUNCTION

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

const	CHAR* CSAskLogin::GetAccount()	const
{
	return szAccount;
}
VOID			CSAskLogin::SetAccount(CHAR* pAccount)
{
	Assert(pAccount);
	strncpy(szAccount, pAccount, MAX_ACCOUNT);
	szAccount[MAX_ACCOUNT] = 0;
}

UINT			CSAskLogin::GetVersion() const
{
	return	uVersion;
}

VOID			CSAskLogin::SetVersion(UINT version)
{
	uVersion = version;
}

WorkerID_t			CSAskLogin::GetWorkerID() const
{
	return	m_nWorkerID;
}

VOID			CSAskLogin::SetWorkerID(WorkerID_t workerID)
{
	m_nWorkerID = workerID;
}

UINT CSAskLogin::Execute( Player* pPlayer )
{
__ENTER_FUNCTION

	return CSAskLoginHandler::Execute( this, pPlayer ) ;

__LEAVE_FUNCTION

	return FALSE ;
}
