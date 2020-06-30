

#ifndef __PLAYERPOOL_H__
#define __PLAYERPOOL_H__

#include "Type.h"
#include "ServerPlayer.h"

//����������ݵ����ݳ�
//
class PlayerPool
{
public :
	PlayerPool( ) ;
	~PlayerPool( ) ;

	//��ʼ�����ݳ�
	BOOL				Init( UINT PlayerPoolMaxCount = MAX_POOL_SIZE ) ;

	//������ҵ�PlayerIDȡ������ָ��
	ServerPlayer*		GetPlayer( PlayerID_t PlayerID )
	{
		if( PlayerID==INVALID_ID || PlayerID>=(PlayerID_t)m_PlayerPoolMaxCount || PlayerID<0 )
			return NULL ;
		return &(m_pPlayer[PlayerID]) ;
	};

	////������ҵ�Nameȡ������ָ��
	////TODO:��Ҫ�Ľ�
	//GamePlayer*			GetPlayerByName( const CHAR* PlayerName )
	//{
	//	for( UINT i=0; i < m_PlayerPoolMaxCount; i++ )
	//	{
	//		if( !m_pPlayer[i].IsEmpty() )
	//		{
	//			Obj_Human* pHuman = m_pPlayer[i].GetHuman();
	//			if (strcmp(pHuman->GetName(), PlayerName) == 0)
	//			{
	//				return &(m_pPlayer[i]) ;
	//			}
	//		}
	//	}
	//	return NULL;
	//};

	//�ӿ������ݳ������һ���������
	ServerPlayer*		NewPlayer( ) ;
	//��һ�����������ջ���
	void				DelPlayer( PlayerID_t PlayerID ) ;

	void				Lock( ){ m_Lock.Lock() ; } ;
	void				Unlock( ){ m_Lock.Unlock() ; } ;

private :
	ServerPlayer*		m_pPlayer ;
	UINT				m_Position ;

	MyLock				m_Lock ;
	UINT				m_PlayerCount ;

	UINT				m_PlayerPoolMaxCount;

};


extern PlayerPool* g_pPlayerPool ;


#endif
