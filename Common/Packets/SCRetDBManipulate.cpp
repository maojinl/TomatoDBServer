#include "stdafx.h"

#include "SCRetDBManipulate.h"

BOOL SCRetDBManipulate::Read(SocketInputStream& iStream)
{
	__ENTER_FUNCTION
	iStream.Read((CHAR*)(&Result), sizeof(ASKDBOPERATION_RESULT));
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

BOOL SCRetDBManipulate::Write(SocketOutputStream& oStream) const
{
	__ENTER_FUNCTION
	oStream.Write((CHAR*)(&Result), sizeof(ASKDBOPERATION_RESULT));
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

UINT SCRetDBManipulate::Execute(Player* pPlayer)
{
	__ENTER_FUNCTION

	return SCRetDBManipulateHandler::Execute(this, pPlayer);

	__LEAVE_FUNCTION

	return FALSE;
}

const DB_OPERATION_TYPE SCRetDBManipulate::GetOperationType() const
{
	return m_OperationType;
}
VOID SCRetDBManipulate::SetOperationType(DB_OPERATION_TYPE opType)
{
	m_OperationType = opType;
}

ASKDBOPERATION_RESULT SCRetDBManipulate::GetResult() const
{
	return Result;
}

VOID SCRetDBManipulate::SetResult(ASKDBOPERATION_RESULT result)
{
	Result = result;
}
