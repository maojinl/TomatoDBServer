#include "stdafx.h"

#include "CSAskDBManipulateData.h"

BOOL CSAskDBManipulateData::Read( SocketInputStream& iStream )
{
__ENTER_FUNCTION
	iStream.Read((CHAR*)(m_OperationType), sizeof(DB_OPERATION_TYPE_NONE));
	iStream.Read((CHAR*)(m_DatabaseName), sizeof(CHAR) * (MAX_DATABASE_NAME + 1));
	iStream.Read((CHAR*)(m_Key), sizeof(CHAR) * (MAX_DATABASE_KEY + 1));
	iStream.Read((CHAR*)(m_Value), sizeof(CHAR) * (MAX_DATABASE_VALUE + 1));
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL CSAskDBManipulateData::Write( SocketOutputStream& oStream )const
{
__ENTER_FUNCTION

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

const CHAR* CSAskDBManipulateData::GetDatabaseName()	const
{
	return m_DatabaseName;
}
VOID CSAskDBManipulateData::SetDatabaseName(CHAR* pDBName)
{
	Assert(pDBName);
	strncpy(m_DatabaseName, pDBName, MAX_DATABASE_NAME);
	m_DatabaseName[MAX_DATABASE_NAME] = 0;
}

const CHAR* CSAskDBManipulateData::GetDatabaseKey()	const
{
	return m_Key;
}
VOID CSAskDBManipulateData::SetDatabaseKey(CHAR* pKey)
{
	Assert(pKey);
	strncpy(m_Key, pKey, MAX_DATABASE_KEY);
	m_Key[MAX_DATABASE_KEY] = 0;
}

const CHAR* CSAskDBManipulateData::GetDatabaseValue()	const
{
	return m_Value;
}
VOID CSAskDBManipulateData::SetDatabaseValue(CHAR* pValue)
{
	Assert(pValue);
	strncpy(m_Value, pValue, MAX_DATABASE_VALUE);
	m_Value[MAX_DATABASE_VALUE] = 0;
}

UINT CSAskDBManipulateData::Execute( Player* pPlayer )
{
__ENTER_FUNCTION

	return CSAskDBManipulateDataHandler::Execute( this, pPlayer ) ;

__LEAVE_FUNCTION

	return FALSE ;
}
