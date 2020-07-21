

#ifndef __PLAYERPOOL_H__
#define __PLAYERPOOL_H__

#include "Type.h"
#include "GamePlayer.h"
#include <map>
#include <iostream>
#include <string>

using  namespace std;

//分配玩家数据的数据池
//

class PlayerPool
{


public :
	PlayerPool( ) ;
	~PlayerPool( ) ;

	//初始化数据池
	BOOL				Init( UINT PlayerPoolMaxCount = MAX_POOL_SIZE) ;

	//取得ShareMem的初始化
	//BOOL				PostInit();


	//根据玩家的PlayerID取得数据指针
	GamePlayer*			GetPlayer( PlayerID_t PlayerID )
	{
		if( PlayerID==INVALID_ID || PlayerID>=(PlayerID_t)m_PlayerPoolMaxCount || PlayerID<0 )
			return nullptr ;
		return &(m_pPlayer[PlayerID]) ;
	};

	//根据玩家的Name取得数据指针
	//TODO:需要改进
	GamePlayer*			GetPlayerByName( const CHAR* PlayerName )
	{
		string sName(PlayerName);
		map<string, PlayerID_t>::iterator iter;

		iter = mapPlayerName.find(sName);

		if(iter != mapPlayerName.end())
		{
			return &(m_pPlayer[iter->second]) ; 
		}

		return nullptr;
	};

	//根据玩家的Name取得数据指针
	//TODO:需要改进
	GamePlayer*			GetPlayerByGUID( const GUID_t guid )
	{

		map<GUID_t, PlayerID_t>::iterator iter;

		iter = mapPlayerGUID.find(guid);

		if(iter != mapPlayerGUID.end())
		{
			return &(m_pPlayer[iter->second]) ; 
		}

		return nullptr;
	};

	UINT				GetPlayerPoolMaxCount()
	{
		return m_PlayerPoolMaxCount;
	};

	//从空闲数据池里分配一个玩家数据
	GamePlayer*			NewPlayer( ) ;
	GamePlayer*			NewPlayer(PlayerID_t PlayerID);
	//将一个玩家数据清空回收
	VOID				DelPlayer( PlayerID_t PlayerID ) ;

	VOID				Lock( ){ m_Lock.Lock() ; } ;
	VOID				Unlock( ){ m_Lock.Unlock() ; } ;

	BOOL				AddPlayerIndex4GUID(GUID_t id, PlayerID_t PlayerID);
	BOOL				DelPlayerIndex4GUID(GUID_t id);

	BOOL				AddPlayerIndex4Name(string szName,PlayerID_t PlayerID);
	BOOL				DelPlayerIndex4Name(string szName);

private :
	GamePlayer*			m_pPlayer ;
	UINT				m_Position ;

	MyLock				m_Lock ;
	UINT				m_PlayerCount ;

	UINT				m_PlayerPoolMaxCount;


	VOID				SetPosition(UINT pos);

	map<GUID_t, PlayerID_t>  mapPlayerGUID;
	map<string, PlayerID_t>   mapPlayerName;
};


extern PlayerPool* g_pPlayerPool ;


#endif
