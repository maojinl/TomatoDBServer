#include "stdafx.h"

#include "SCRetDBManipulateData.h"


BOOL SCRetDBManipulateData::Read(SocketInputStream& iStream)
{
	__ENTER_FUNCTION
	iStream.Read((CHAR*)(&Result), sizeof(ASKDBOPERATION_RESULT));
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

BOOL SCRetDBManipulateData::Write(SocketOutputStream& oStream) const
{
	__ENTER_FUNCTION
	oStream.Write((CHAR*)(&Result), sizeof(ASKDBOPERATION_RESULT));
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

UINT SCRetDBManipulateData::Execute(Player* pPlayer)
{
	__ENTER_FUNCTION

	return SCRetDBManipulateDataHandler::Execute(this, pPlayer);

	__LEAVE_FUNCTION

	return FALSE;
}

const DB_OPERATION_TYPE SCRetDBManipulateData::GetOperationType() const
{
	return m_OperationType;
}
VOID SCRetDBManipulateData::SetOperationType(DB_OPERATION_TYPE opType)
{
	m_OperationType = opType;
}

ASKDBOPERATION_RESULT SCRetDBManipulateData::GetResult() const
{
	return Result;
}

VOID SCRetDBManipulateData::SetResult(ASKDBOPERATION_RESULT result)
{
	Result = result;
}
