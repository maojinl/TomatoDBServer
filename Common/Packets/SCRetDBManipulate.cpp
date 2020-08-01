#include "stdafx.h"

#include "SCRetDBManipulate.h"

BOOL SCRetDBManipulate::Read(SocketInputStream& iStream)
{
	__ENTER_FUNCTION
	iStream.Read((CHAR*)(&m_ManipulateType), sizeof(DB_MANIPULATE_TYPE));
	iStream.Read((CHAR*)(&Result), sizeof(ASKDBOPERATION_RESULT));
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

BOOL SCRetDBManipulate::Write(SocketOutputStream& oStream) const
{
	__ENTER_FUNCTION
	oStream.Write((CHAR*)(&m_ManipulateType), sizeof(DB_MANIPULATE_TYPE));
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

const DB_MANIPULATE_TYPE SCRetDBManipulate::GetManipulateType() const
{
	return m_ManipulateType;
}
VOID SCRetDBManipulate::SetManipulateType(DB_MANIPULATE_TYPE manType)
{
	m_ManipulateType = manType;
}

ASKDBOPERATION_RESULT SCRetDBManipulate::GetResult() const
{
	return Result;
}

VOID SCRetDBManipulate::SetResult(ASKDBOPERATION_RESULT result)
{
	Result = result;
}
