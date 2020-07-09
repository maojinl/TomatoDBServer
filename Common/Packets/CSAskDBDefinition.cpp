#include "stdafx.h"

#include "CSAskDBDefinition.h"

BOOL CSAskDBDefinition::Read(SocketInputStream& iStream)
{
__ENTER_FUNCTION
	iStream.Read((CHAR*)(m_OperationType), sizeof(DB_OPERATION_TYPE_NONE));
	iStream.Read((CHAR*)(m_DatabaseName), sizeof(CHAR) * (MAX_DATABASE_NAME + 1));
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL CSAskDBDefinition::Write( SocketOutputStream& oStream ) const
{
__ENTER_FUNCTION

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
	strncpy(m_DatabaseName, pDBName, MAX_DATABASE_NAME);
	m_DatabaseName[MAX_DATABASE_NAME] = 0;
}

UINT CSAskDBDefinition::Execute(Player* pPlayer)
{
__ENTER_FUNCTION

	return CSAskDBDefinitionHandler::Execute(this, pPlayer);

__LEAVE_FUNCTION

	return FALSE ;
}
