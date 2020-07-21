#include "stdafx.h"

#include "SCRetDBDefinition.h"


BOOL SCRetDBDefinition::Read(SocketInputStream& iStream)
{
	__ENTER_FUNCTION
	iStream.Read((CHAR*)(&m_OperationType), sizeof(DB_OPERATION_TYPE));
	iStream.Read((CHAR*)(&Result), sizeof(ASKDBOPERATION_RESULT));
	iStream.Read((CHAR*)(&m_DatabaseNameSize), sizeof(BYTE));
	iStream.Read((CHAR*)(m_DatabaseName), sizeof(CHAR) * m_DatabaseNameSize);
	m_DatabaseName[m_DatabaseNameSize] = 0;
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

BOOL SCRetDBDefinition::Write(SocketOutputStream& oStream) const
{
	__ENTER_FUNCTION
	oStream.Write((CHAR*)(&m_OperationType), sizeof(DB_OPERATION_TYPE));
	oStream.Write((CHAR*)(&Result), sizeof(ASKDBOPERATION_RESULT));
	oStream.Write((CHAR*)(&m_DatabaseNameSize), sizeof(BYTE));
	oStream.Write((CHAR*)(m_DatabaseName), sizeof(CHAR) * m_DatabaseNameSize);
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

UINT SCRetDBDefinition::Execute(Player* pPlayer)
{
	__ENTER_FUNCTION

	return SCRetDBDefinitionHandler::Execute(this, pPlayer);

	__LEAVE_FUNCTION

	return FALSE;
}

const DB_OPERATION_TYPE SCRetDBDefinition::GetOperationType() const
{
	return m_OperationType;
}
VOID SCRetDBDefinition::SetOperationType(DB_OPERATION_TYPE opType)
{
	m_OperationType = opType;
}


ASKDBOPERATION_RESULT SCRetDBDefinition::GetResult() const
{
	return Result;
}

VOID SCRetDBDefinition::SetResult(ASKDBOPERATION_RESULT result)
{
	Result = result;
}
