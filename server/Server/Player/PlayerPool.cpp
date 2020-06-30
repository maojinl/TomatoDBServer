#include "stdafx.h"

#include "PlayerPool.h"
#include "GUIDManager.h"

PlayerPool* g_pPlayerPool=NULL ;

PlayerPool::PlayerPool( )
{
	__ENTER_FUNCTION

		m_pPlayer = NULL ;
	m_Position = 0 ;
	m_PlayerCount = 0 ;
	m_PlayerPoolMaxCount = 0;

	__LEAVE_FUNCTION
}

PlayerPool::~PlayerPool( ) 
{
	__ENTER_FUNCTION

	SAFE_DELETE_ARRAY( m_pPlayer ) ;

	__LEAVE_FUNCTION
}

BOOL PlayerPool::Init( UINT PlayerPoolMaxCount )
{
	__ENTER_FUNCTION

		m_PlayerPoolMaxCount = PlayerPoolMaxCount;

	m_pPlayer = new GamePlayer[m_PlayerPoolMaxCount] ;
	Assert( m_pPlayer ) ;

	for( UINT i=0; i<m_PlayerPoolMaxCount; i++ )
	{
		m_pPlayer[i].SetPlayerID( (PlayerID_t)i ) ;
		m_pPlayer[i].SetEmpty(TRUE) ;
		//printf("m_pPlayer[i] = %d\n",m_pPlayer[i].PlayerID());
	}
	m_Position = 0 ;
	m_PlayerCount = m_PlayerPoolMaxCount ;

	return TRUE ;

	__LEAVE_FUNCTION

		return FALSE ;
}

GamePlayer* PlayerPool::NewPlayer( )
{
	__ENTER_FUNCTION

		Lock() ;

		INT iRet = 0 ;
		for( UINT i=0; i<m_PlayerPoolMaxCount; i++ )
		{
			if( m_pPlayer[m_Position].IsEmpty() )
			{
				iRet = m_Position ;
				m_pPlayer[m_Position].SetEmpty( FALSE ) ;

				m_Position ++ ;
				if( m_Position >= m_PlayerPoolMaxCount ) 
					m_Position = 0 ;

				m_PlayerCount -- ;

				Unlock() ;

				return &(m_pPlayer[iRet]) ;
			}

			m_Position ++ ;
			if( m_Position >= m_PlayerPoolMaxCount ) 
				m_Position = 0 ;
		}

		Unlock() ;

		return NULL ;

	__LEAVE_FUNCTION

		Unlock() ;

	return NULL ;
}

GamePlayer* PlayerPool::NewPlayer( PlayerID_t PlayerID)
{
	__ENTER_FUNCTION

		Lock() ;

		if(PlayerID>=(PlayerID_t)m_PlayerPoolMaxCount)
		{
			Unlock();
			return NULL;
		}


		if(m_pPlayer[PlayerID].IsEmpty())
		{
			GamePlayer* pPlayer = &(m_pPlayer[PlayerID]);
			pPlayer->SetEmpty(FALSE);

			m_PlayerCount--;
			m_Position = PlayerID;
			m_Position ++ ;
			if( m_Position >= m_PlayerPoolMaxCount ) 
				m_Position = 0 ;

			Unlock();
			return pPlayer;

		}

		Unlock() ;
		return NULL ;
	__LEAVE_FUNCTION
		Unlock() ;
	return NULL ;
}

VOID PlayerPool::DelPlayer( PlayerID_t PlayerID )
{
	__ENTER_FUNCTION

	Lock() ;

	if( (UINT)PlayerID >= m_PlayerPoolMaxCount )
	{
		Assert( FALSE ) ;
		Unlock() ;
		return ;
	}

	if( m_pPlayer[PlayerID].IsEmpty() )
	{
		Unlock() ;
		return ;
	}

	string strPlayerName(m_pPlayer[m_Position].GetName());
	DelPlayerIndex4Name(strPlayerName);

	m_pPlayer[PlayerID].SetEmpty( TRUE ) ;

	m_PlayerCount ++ ;

	Unlock() ;

	return ;

	__LEAVE_FUNCTION

	Unlock() ;

	return ;
}

BOOL PlayerPool::AddPlayerIndex4GUID(GUID_t id, PlayerID_t PlayerID)
{
	__ENTER_FUNCTION

	DelPlayerIndex4GUID(id);

	mapPlayerGUID.insert(map<GUID_t, PlayerID_t>::value_type(id, PlayerID));

	return TRUE;
	__LEAVE_FUNCTION

	return FALSE;

}
BOOL PlayerPool::DelPlayerIndex4GUID(GUID_t id)
{
	__ENTER_FUNCTION

	map<GUID_t, PlayerID_t>::iterator Iter;

	Iter = mapPlayerGUID.find(id);
	if (Iter != mapPlayerGUID.end())
	{
		mapPlayerGUID.erase(Iter);
	}

		return TRUE;
	__LEAVE_FUNCTION

		return FALSE;
}

BOOL PlayerPool::AddPlayerIndex4Name(string szName,PlayerID_t PlayerID)
{
	__ENTER_FUNCTION

		DelPlayerIndex4Name(szName);

		mapPlayerName.insert(map<string, PlayerID_t>::value_type(szName, PlayerID));		

		return TRUE;
	__LEAVE_FUNCTION

		return FALSE;
}

BOOL PlayerPool::DelPlayerIndex4Name(string szName)
{
	__ENTER_FUNCTION
	map<string, PlayerID_t>::iterator Iter;

	Iter = mapPlayerName.find(szName);
	if (Iter != mapPlayerName.end())
	{
		mapPlayerName.erase(Iter);
	}

	return TRUE;
	__LEAVE_FUNCTION

	return FALSE;
}