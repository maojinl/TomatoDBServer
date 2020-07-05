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

	oStream.Write((CHAR*)(szAccount), sizeof(CHAR) * (MAX_ACCOUNT + 1));
	oStream.Write((CHAR*)(szPassKey), sizeof(CHAR) * (MAX_ACCOUNT + 1));

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

UINT CSAskLogin::Execute( Player* pPlayer )
{
__ENTER_FUNCTION

	return CSAskLoginHandler::Execute( this, pPlayer ) ;

__LEAVE_FUNCTION

	return FALSE ;
}
