#include "stdafx.h"

#include "DBLinkObject.h"
#include "Log.h"

namespace tomatodb
{
	DBLinkObject::DBLinkObject(const Config& config, string tableName1, string tableName2):
		tableName(tableName1), linkedTableName(tableName2)
	{
		return;
	}

	DBLinkObject::~DBLinkObject()
	{
		return;
	}

	VOID DBLinkObject::CleanUp()
	{
		__ENTER_FUNCTION
		__LEAVE_FUNCTION
	}

	BOOL DBLinkObject::Init()
	{
		__ENTER_FUNCTION
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}
}
