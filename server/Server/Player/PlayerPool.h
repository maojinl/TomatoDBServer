

#ifndef __PLAYERPOOL_H__
#define __PLAYERPOOL_H__

#include "Type.h"
#include "GamePlayer.h"
#include <map>
#include <iostream>
#include <string>

using  namespace std;

//����������ݵ����ݳ�
//

class PlayerPool
{


public :
	PlayerPool( ) ;
	~PlayerPool( ) ;

	//��ʼ�����ݳ�
	BOOL				Init( UINT PlayerPoolMaxCount = MAX_POOL_SIZE) ;

	//ȡ��ShareMem�ĳ�ʼ��
	//BOOL				PostInit();


	//������ҵ�PlayerIDȡ������ָ��
	GamePlayer*			GetPlayer( PlayerID_t PlayerID )
	{
		if( PlayerID==INVALID_ID || PlayerID>=(PlayerID_t)m_PlayerPoolMaxCount || PlayerID<0 )
			return nullptr ;
		return &(m_pPlayer[PlayerID]) ;
	};

	//������ҵ�Nameȡ������ָ��
	//TODO:��Ҫ�Ľ�
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

	//������ҵ�Nameȡ������ָ��
	//TODO:��Ҫ�Ľ�
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

	//�ӿ������ݳ������һ���������
	GamePlayer*			NewPlayer( ) ;
	GamePlayer*			NewPlayer(PlayerID_t PlayerID);
	//��һ�����������ջ���
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
