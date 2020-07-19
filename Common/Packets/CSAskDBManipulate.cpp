#include "stdafx.h"

#include "CSAskDBManipulate.h"

BOOL CSAskDBManipulate::Read( SocketInputStream& iStream )
{
__ENTER_FUNCTION
	iStream.Read((CHAR*)(&m_ManipulateType), sizeof(DB_MANIPULATE_TYPE));
	iStream.Read((CHAR*)(&m_DatabaseNameSize), sizeof(BYTE));
	iStream.Read((CHAR*)(m_DatabaseName), sizeof(CHAR) * m_DatabaseNameSize);
	m_DatabaseName[m_DatabaseNameSize] = 0;
	iStream.Read((CHAR*)(&m_KeySize), sizeof(BYTE));
	iStream.Read((CHAR*)(m_Key), sizeof(CHAR) * m_KeySize);
	m_Key[m_KeySize] = 0;
	iStream.Read((CHAR*)(&m_ValueSize), sizeof(UINT));
	iStream.Read((CHAR*)(m_Value), sizeof(CHAR) * m_ValueSize);
	m_Value[m_ValueSize] = 0;
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL CSAskDBManipulate::Write( SocketOutputStream& oStream )const
{
__ENTER_FUNCTION

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

const CHAR* CSAskDBManipulate::GetDatabaseName()	const
{
	return m_DatabaseName;
}

VOID CSAskDBManipulate::SetDatabaseName(CHAR* pDBName)
{
	Assert(pDBName);
	memset(m_DatabaseName, 0, m_DatabaseNameSize);
	memcpy(m_DatabaseName, pDBName, m_DatabaseNameSize);
	m_DatabaseName[m_DatabaseNameSize] = 0;
}

const CHAR* CSAskDBManipulate::GetDatabaseKey()	const
{
	return m_Key;
}
VOID CSAskDBManipulate::SetDatabaseKey(CHAR* pKey)
{
	Assert(pKey);
	memset(m_Key, 0, m_KeySize);
	memcpy(m_Key, pKey, m_KeySize);
	m_Key[m_KeySize] = 0;
}

const DB_MANIPULATE_TYPE CSAskDBManipulate::GetManipulateType() const
{
	return m_ManipulateType;
}
VOID CSAskDBManipulate::SetManipulateType(DB_MANIPULATE_TYPE manType)
{
	m_ManipulateType = manType;
}

const CHAR* CSAskDBManipulate::GetDatabaseValue()	const
{
	return m_Value;
}
VOID CSAskDBManipulate::SetDatabaseValue(CHAR* pValue)
{
	Assert(pValue);
	memset(m_Value, 0, m_ValueSize);
	memcpy(m_Value, pValue, m_ValueSize);
	m_Value[m_ValueSize] = 0;
}

UINT CSAskDBManipulate::Execute( Player* pPlayer )
{
__ENTER_FUNCTION

	return CSAskDBManipulateHandler::Execute( this, pPlayer ) ;

__LEAVE_FUNCTION

	return FALSE ;
}
