#include "stdafx.h"


#include "IDTable.h"


IDTable::IDTable( )
{
	__ENTER_FUNCTION

		m_Count = 0 ;

	__LEAVE_FUNCTION
}

IDTable::~IDTable( )
{
	__ENTER_FUNCTION

		m_pTable.clear();
	m_Count = 0 ;

	__LEAVE_FUNCTION
}

VOID IDTable::InitTable( UINT MaxItem )
{
	__ENTER_FUNCTION

		m_Count = MaxItem ;

	__LEAVE_FUNCTION
}

BOOL IDTable::Add( UINT id, VOID* pPtr )
{
	__ENTER_FUNCTION

		UINT nSize = m_pTable.size();

	if (nSize>=m_Count)
	{
		return FALSE;
	}

	pair<map<IDMAP>::iterator, bool> Insert_Pair;

	Insert_Pair = m_pTable.insert(pair<IDMAP>(id,pPtr));

	if (Insert_Pair.second == true)
	{
		return TRUE ;
	}
	else
		return FALSE;

	__LEAVE_FUNCTION

		return FALSE ;
}

VOID* IDTable::Get( UINT id )
{
	__ENTER_FUNCTION

		map<IDMAP>::iterator  iter;

	iter = m_pTable.find(id);

	if(iter != m_pTable.end())
	{
		return iter->second;
	}
	else
		return NULL;

	__LEAVE_FUNCTION

		return NULL ;
}

VOID IDTable::Remove( UINT id )
{
	__ENTER_FUNCTION

	//	map<IDMAP>::iterator  iter;

	//iter = m_pTable.find(id);

	m_pTable.erase(id);

	__LEAVE_FUNCTION
}

VOID IDTable::CleanUp( )
{
	__ENTER_FUNCTION

		m_pTable.clear();

	__LEAVE_FUNCTION
}

