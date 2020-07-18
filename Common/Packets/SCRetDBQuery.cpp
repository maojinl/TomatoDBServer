#include "stdafx.h"

#include "SCRetDBQuery.h"


BOOL SCRetDBQuery::Read(SocketInputStream& iStream)
{
	__ENTER_FUNCTION
	iStream.Read((CHAR*)(&Result), sizeof(ASKDBOPERATION_RESULT));
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

BOOL SCRetDBQuery::Write(SocketOutputStream& oStream) const
{
	__ENTER_FUNCTION
	oStream.Write((CHAR*)(&m_QueryType), sizeof(DB_QUERY_TYPE));
	oStream.Write((CHAR*)(&Result), sizeof(ASKDBOPERATION_RESULT));
	UINT sz = m_Values.size();
	oStream.Write((CHAR*)(&sz), sizeof(UINT));
	for (int i = 0; i < sz; i++)
	{
		UINT sz1 = m_Values[i].size();
		oStream.Write((CHAR*)(&sz1), sizeof(UINT));
		oStream.Write((CHAR*)(m_Values[i].c_str()), sizeof(CHAR) * sz1);
	}
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

const DB_QUERY_TYPE SCRetDBQuery::GetQueryType() const
{
	return m_QueryType;
}
VOID SCRetDBQuery::SetQueryType(DB_QUERY_TYPE qType)
{
	m_QueryType = qType;
}

ASKDBOPERATION_RESULT SCRetDBQuery::GetResult() const
{
	return Result;
}

VOID SCRetDBQuery::SetResult(ASKDBOPERATION_RESULT result)
{
	Result = result;
}

vector<string>& SCRetDBQuery::GetValues()
{
	return m_Values;
}

VOID SCRetDBQuery::SetValues(const vector<string>& values)
{
	m_Values = values;
}

UINT SCRetDBQuery::Execute(Player* pPlayer)
{
	__ENTER_FUNCTION

	return SCRetDBQueryHandler::Execute(this, pPlayer);

	__LEAVE_FUNCTION

	return FALSE;
}