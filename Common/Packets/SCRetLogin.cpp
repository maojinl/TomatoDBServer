#include "stdafx.h"

#include "SCRetLogin.h"


BOOL SCRetLogin::Read( SocketInputStream& iStream )
{
	__ENTER_FUNCTION

	iStream.Read((CHAR*)(&Result), sizeof(LOGIN_RESULT));
	iStream.Read((CHAR*)(&m_CharName), sizeof(CHAR) * (MAX_CHARACTER_NAME + 1));
	iStream.Read((CHAR*)(&m_TitleName), sizeof(CHAR) * (MAX_CHARACTER_TITLE + 1));
	iStream.Read((CHAR*)(&m_iLevel), sizeof(UINT));

	return TRUE ;
	
	__LEAVE_FUNCTION

	return FALSE ;
}

BOOL SCRetLogin::Write( SocketOutputStream& oStream )const
{
	__ENTER_FUNCTION

	oStream.Write((CHAR*)(&Result), sizeof(LOGIN_RESULT));
	oStream.Write((CHAR*)(&m_CharName), sizeof(CHAR) * (MAX_CHARACTER_NAME + 1));
	oStream.Write((CHAR*)(&m_TitleName), sizeof(CHAR) * (MAX_CHARACTER_TITLE + 1));
	oStream.Write((CHAR*)(&m_iLevel), sizeof(UINT));
	
	return TRUE ;

	__LEAVE_FUNCTION

	return FALSE ;
}

UINT SCRetLogin::Execute( Player* pPlayer )
{
	__ENTER_FUNCTION

	return SCRetLoginHandler::Execute( this, pPlayer ) ;

	__LEAVE_FUNCTION

	return FALSE ;
}

LOGIN_RESULT SCRetLogin::GetResult() const
{
	return Result;
}

VOID SCRetLogin::SetResult(LOGIN_RESULT result)
{
	Result = result;
}
