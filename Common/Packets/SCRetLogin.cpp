#include "stdafx.h"

#include "SCRetLogin.h"


BOOL SCRetLogin::Read( SocketInputStream& iStream )
{
	__ENTER_FUNCTION

	//iStream.Read( (CHAR*)(&szAccount), sizeof(CHAR)*MAX_ACCOUNT);
	iStream.Read((CHAR*)(&m_CharName), sizeof(CHAR) * MAX_CHARACTER_NAME);
	iStream.Read((CHAR*)(&m_TitleName), sizeof(CHAR) * MAX_CHARACTER_TITLE);
	iStream.Read((CHAR*)(&m_iLevel), sizeof(UINT));
	iStream.Read((CHAR*)(&Result),sizeof(LOGIN_RESULT));
	
	return TRUE ;
	
	__LEAVE_FUNCTION

	return FALSE ;
}

BOOL SCRetLogin::Write( SocketOutputStream& oStream )const
{
	__ENTER_FUNCTION

	//oStream.Write( (CHAR*)(&szAccount), sizeof(CHAR)*MAX_ACCOUNT);
	oStream.Write((CHAR*)(&m_CharName), sizeof(CHAR) * MAX_CHARACTER_NAME);
	oStream.Write((CHAR*)(&m_TitleName), sizeof(CHAR) * MAX_CHARACTER_TITLE);
	oStream.Write((CHAR*)(&m_iLevel), sizeof(UINT));
	oStream.Write((CHAR*)(&Result),sizeof(LOGIN_RESULT));
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

//const CHAR* SCRetLogin::GetAccount()	const
//{
//	return szAccount;
//}
//VOID SCRetLogin::SetAccount(const CHAR*	pAccount)
//{
//	Assert(pAccount);
//	strncpy(szAccount,pAccount,MAX_ACCOUNT*sizeof(CHAR));
//	szAccount[MAX_ACCOUNT] = '\0' ;
//}

LOGIN_RESULT SCRetLogin::GetResult() const
{
	return Result;
}

VOID SCRetLogin::SetResult(LOGIN_RESULT result)
{
	Result = result;
}
