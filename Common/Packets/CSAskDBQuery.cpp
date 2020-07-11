#include "stdafx.h"

#include "CSAskDBQuery.h"

BOOL CSAskDBQuery::Read(SocketInputStream& iStream)
{
	__ENTER_FUNCTION
	iStream.Read((CHAR*)(m_QueryType), sizeof(DB_QUERY_TYPE));
	iStream.Read((CHAR*)(&m_DatabaseNameSize), sizeof(BYTE));
	iStream.Read((CHAR*)(m_DatabaseName), sizeof(CHAR) * m_DatabaseNameSize);
	m_DatabaseName[m_DatabaseNameSize] = 0;
	iStream.Read((CHAR*)(&m_KeySize), sizeof(BYTE));
	iStream.Read((CHAR*)(m_Key), sizeof(CHAR) * m_KeySize);
	m_Key[m_KeySize] = 0;
	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

BOOL CSAskDBQuery::Write(SocketOutputStream& oStream)const
{
	__ENTER_FUNCTION

		return TRUE;

	__LEAVE_FUNCTION

		return FALSE;
}

const DB_QUERY_TYPE CSAskDBQuery::GetQueryType() const
{
	return m_QueryType;
}
VOID CSAskDBQuery::SetQueryType(DB_QUERY_TYPE qType)
{
	m_QueryType = qType;
}

const CHAR* CSAskDBQuery::GetDatabaseName()	const
{
	return m_DatabaseName;
}

VOID CSAskDBQuery::SetDatabaseName(CHAR* pDBName)
{
	Assert(pDBName);
	memset(m_DatabaseName, 0, m_DatabaseNameSize);
	memcpy(m_DatabaseName, pDBName, m_DatabaseNameSize);
	m_DatabaseName[m_DatabaseNameSize] = 0;
}

const CHAR* CSAskDBQuery::GetDatabaseKey()	const
{
	return m_Key;
}
VOID CSAskDBQuery::SetDatabaseKey(CHAR* pKey)
{
	Assert(pKey);
	memset(m_Key, 0, m_KeySize);
	memcpy(m_Key, pKey, m_KeySize);
	m_Key[m_KeySize] = 0;
}

UINT CSAskDBQuery::Execute(Player* pPlayer)
{
	__ENTER_FUNCTION

		return CSAskDBQueryHandler::Execute(this, pPlayer);

	__LEAVE_FUNCTION

		return FALSE;
}
