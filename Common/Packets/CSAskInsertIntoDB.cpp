#include "stdafx.h"

#include "CSAskCreateDB.h"

BOOL CSAskCreateDB::Read( SocketInputStream& iStream )
{
__ENTER_FUNCTION
	iStream.Read((CHAR*)(m_DatabaseName), sizeof(CHAR) * (MAX_DATABASE_NAME));
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL CSAskCreateDB::Write( SocketOutputStream& oStream )const
{
__ENTER_FUNCTION

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

const CHAR* CSAskCreateDB::GetDatabaseName()	const
{
	return m_DatabaseName;
}
VOID CSAskCreateDB::SetDatabaseName(CHAR* pDBName)
{
	Assert(pDBName);
	strncpy(m_DatabaseName, pDBName, MAX_DATABASE_NAME);
	m_DatabaseName[MAX_DATABASE_NAME] = 0;
}

UINT CSAskCreateDB::Execute( Player* pPlayer )
{
__ENTER_FUNCTION

	return CSAskCreateDBHandler::Execute( this, pPlayer ) ;

__LEAVE_FUNCTION

	return FALSE ;
}
