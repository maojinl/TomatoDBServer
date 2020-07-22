#include "stdafx.h"

#include "CSAskDBDefinition.h"

BOOL CSAskDBDefinition::Read(SocketInputStream& iStream)
{
__ENTER_FUNCTION
	iStream.Read((CHAR*)(&m_OperationType), sizeof(DB_OPERATION_TYPE));
	iStream.Read((CHAR*)(&m_DatabaseNameSize), sizeof(BYTE));
	iStream.Read((CHAR*)(m_DatabaseName), sizeof(CHAR) * m_DatabaseNameSize);
	m_DatabaseName[m_DatabaseNameSize] = 0;
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL CSAskDBDefinition::Write( SocketOutputStream& oStream ) const
{
__ENTER_FUNCTION
	oStream.Write((CHAR*)(&m_OperationType), sizeof(DB_OPERATION_TYPE));
	oStream.Write((CHAR*)(&m_DatabaseNameSize), sizeof(BYTE));
	oStream.Write((CHAR*)(m_DatabaseName), sizeof(CHAR) * m_DatabaseNameSize);
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

const DB_OPERATION_TYPE CSAskDBDefinition::GetOperationType() const
{
	return m_OperationType;
}
VOID CSAskDBDefinition::SetOperationType(DB_OPERATION_TYPE opType)
{
	m_OperationType = opType;
}

const CHAR* CSAskDBDefinition::GetDatabaseName() const
{
	return m_DatabaseName;
}
VOID CSAskDBDefinition::SetDatabaseName(CHAR* pDBName)
{
	Assert(pDBName);
	memset(m_DatabaseName, 0, m_DatabaseNameSize); 
	memcpy(m_DatabaseName, pDBName, m_DatabaseNameSize);
	m_DatabaseName[m_DatabaseNameSize] = 0;
}

UINT CSAskDBDefinition::Execute(Player* pPlayer)
{
__ENTER_FUNCTION

	return CSAskDBDefinitionHandler::Execute(this, pPlayer);

__LEAVE_FUNCTION

	return FALSE ;
}
