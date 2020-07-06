#include "stdafx.h"

#include "SCRetCreateDB.h"


BOOL SCRetCreateDB::Read(SocketInputStream& iStream)
{
	__ENTER_FUNCTION
	iStream.Read((CHAR*)(&Result), sizeof(LOGIN_RESULT));
	iStream.Read((CHAR*)(&m_DatabaseName), sizeof(CHAR) * MAX_DATABASE_NAME);
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

BOOL SCRetCreateDB::Write(SocketOutputStream& oStream) const
{
	__ENTER_FUNCTION
	oStream.Write((CHAR*)(&Result), sizeof(ASKCREATEDB_RESULT));
	oStream.Write((CHAR*)(&m_DatabaseName), sizeof(CHAR) * MAX_DATABASE_NAME);
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

UINT SCRetCreateDB::Execute(Player* pPlayer)
{
	__ENTER_FUNCTION

	return SCRetCreateDBHandler::Execute(this, pPlayer);

	__LEAVE_FUNCTION

	return FALSE;
}

ASKCREATEDB_RESULT SCRetCreateDB::GetResult() const
{
	return Result;
}

VOID SCRetCreateDB::SetResult(ASKCREATEDB_RESULT result)
{
	Result = result;
}
