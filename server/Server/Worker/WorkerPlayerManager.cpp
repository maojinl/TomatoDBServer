#include "stdafx.h"

#include "WorkerPlayerManager.h"
#include "Log.h"
#include "GamePlayer.h"
#include "PlayerPool.h"
#include "WorkerManager.h"
#include "ServerManager.h"
#include "PacketFactoryManager.h"

WorkerPlayerManager::WorkerPlayerManager( )
{
__ENTER_FUNCTION

	FD_ZERO( &m_ReadFDs[SELECT_BAK] ) ;
	FD_ZERO( &m_WriteFDs[SELECT_BAK] ) ;
	FD_ZERO( &m_ExceptFDs[SELECT_BAK] ) ;
	FD_ZERO( &m_ReadFDs[SELECT_USE] ) ;
	FD_ZERO( &m_WriteFDs[SELECT_USE] ) ;
	FD_ZERO( &m_ExceptFDs[SELECT_USE] ) ;

	m_Timeout[SELECT_BAK].tv_sec = 0;
	m_Timeout[SELECT_BAK].tv_usec = 0;

	m_MinFD = m_MaxFD = INVALID_SOCKET ;

	m_nFDSize = 0 ;

	m_WorkerID = INVALID_ID ;

__LEAVE_FUNCTION
}

WorkerPlayerManager::~WorkerPlayerManager( )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

BOOL WorkerPlayerManager::Select( )
{
__ENTER_FUNCTION

//	if( m_nPlayers == 0 )
	{
		MySleep( 50 ) ;
	}

	if( m_MaxFD==INVALID_SOCKET && m_MinFD==INVALID_SOCKET )
		return TRUE ;

	m_Timeout[SELECT_USE].tv_sec  = m_Timeout[SELECT_BAK].tv_sec;
	m_Timeout[SELECT_USE].tv_usec = m_Timeout[SELECT_BAK].tv_usec;

	m_ReadFDs[SELECT_USE]   = m_ReadFDs[SELECT_BAK];
	m_WriteFDs[SELECT_USE]  = m_WriteFDs[SELECT_BAK];
	m_ExceptFDs[SELECT_USE] = m_ExceptFDs[SELECT_BAK];

	_MY_TRY 
	{
		INT ret = SocketAPI::select_ex(	(INT)m_MaxFD+1 , 
										&m_ReadFDs[SELECT_USE] , 
										&m_WriteFDs[SELECT_USE] , 
										&m_ExceptFDs[SELECT_USE] , 
										&m_Timeout[SELECT_USE] ) ;
		if( ret == SOCKET_ERROR )
		{
			Assert(FALSE) ;
		}
	} 
	_MY_CATCH
	{
		SaveCodeLog( ) ;
	}


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerPlayerManager::ProcessInputs( )
{
__ENTER_FUNCTION

	BOOL ret = FALSE ;

	if (m_MinFD == INVALID_SOCKET && m_MaxFD == INVALID_SOCKET) // no player exist
	{ 
		return TRUE ;
	}

	//���ݶ�ȡ
	UINT nPlayerCount = GetPlayerNumber() ;
	for( UINT i=0; i<nPlayerCount; i++ )
	{
		if( m_pPlayers[i]==INVALID_ID )
			continue ;

		GamePlayer* pPlayer = g_pPlayerPool->GetPlayer(m_pPlayers[i]) ;
		Assert( pPlayer ) ;

		if (pPlayer->IsDirty())
		{
			continue ;
		}

		//�����ѶϿ�
		if( pPlayer->IsDisconnect() )
			continue;

		SOCKET s = pPlayer->GetSocket()->getSOCKET() ;
		Assert( s!=INVALID_SOCKET ) ;

		if( FD_ISSET( s, &m_ReadFDs[SELECT_USE] ) )
		{
			if( pPlayer->GetSocket()->isSockError() )
			{//���ӳ��ִ���
				g_pLog->FastSaveLog( LOG_FILE_1, "ERROR CI0 GUID=%X NeedRemove", 
					pPlayer->m_HumanGUID ) ;
					
				RemovePlayer( pPlayer, "������ӳ��ִ���" ) ;
			}
			else
			{//��������
				_MY_TRY
				{
					ret = pPlayer->ProcessInput( ) ;
					if( !ret )
					{
						g_pLog->FastSaveLog( LOG_FILE_1, "ERROR CI1 GUID=%X NeedRemove",
							pPlayer->m_HumanGUID ) ;

						RemovePlayer( pPlayer, "ProcessInputִ�з��ؽ������" ) ;
					}
				}
				_MY_CATCH
				{
					SaveCodeLog( ) ;

					g_pLog->FastSaveLog( LOG_FILE_1, "ERROR CI2 GUID=%X NeedRemove",
						pPlayer->m_HumanGUID ) ;

					RemovePlayer( pPlayer, "ProcessInputִ�з����쳣" ) ;
				}
			}
		}
	}


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerPlayerManager::ProcessOutputs( )
{
__ENTER_FUNCTION

	BOOL ret = FALSE ;

	if (m_MinFD == INVALID_SOCKET && m_MaxFD == INVALID_SOCKET) // no player exist
	{ 
		return TRUE ;
	}

	//���ݷ���
	UINT nPlayerCount = GetPlayerNumber() ;
	for( UINT i=0; i<nPlayerCount; i++ )
	{
		if( m_pPlayers[i]==INVALID_ID )
			continue ;

		GamePlayer* pPlayer = g_pPlayerPool->GetPlayer(m_pPlayers[i]) ;
		Assert( pPlayer ) ;

		if( pPlayer->IsDisconnect( ) )
			continue ;

		SOCKET s = pPlayer->GetSocket()->getSOCKET() ;
		Assert( s!=INVALID_SOCKET ) ;

		if( FD_ISSET( s, &m_WriteFDs[SELECT_USE] ) )
		{
			if( pPlayer->GetSocket()->isSockError() )
			{//���ӳ��ִ���
				g_pLog->FastSaveLog( LOG_FILE_1, "ERROR CO0 GUID=%X NeedRemove",
					pPlayer->m_HumanGUID ) ;

				RemovePlayer( pPlayer, "ProcessOutputsʱ������ӳ���" ) ;
			}
			else
			{//��������
				_MY_TRY
				{
					ret = pPlayer->ProcessOutput( ) ;
					if( !ret )
					{
						g_pLog->FastSaveLog( LOG_FILE_1, "ERROR CO1 GUID=%X NeedRemove",
							pPlayer->m_HumanGUID ) ;

						RemovePlayer( pPlayer, "ProcessOutputִ�г���" ) ;
					}
				}
				_MY_CATCH
				{
					SaveCodeLog( ) ;

					g_pLog->FastSaveLog( LOG_FILE_1, "ERROR CO2 GUID=%X NeedRemove",
						pPlayer->m_HumanGUID ) ;

					RemovePlayer( pPlayer, "ProcessOutputִ�г����쳣" ) ;
				}
			}
		}
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerPlayerManager::ProcessExceptions( )
{
__ENTER_FUNCTION

	if (m_MinFD == INVALID_SOCKET && m_MaxFD == INVALID_SOCKET) // no player exist
	{ 
		return TRUE ;
	}

	UINT nPlayerCount = GetPlayerNumber() ;
	for( UINT i=0; i<nPlayerCount; i++ )
	{
		if( m_pPlayers[i]==INVALID_ID )
			continue ;

		//ĳ����ҶϿ���������

		GamePlayer* pPlayer = g_pPlayerPool->GetPlayer(m_pPlayers[i]) ;
		Assert( pPlayer ) ;

		if( pPlayer->IsDisconnect() )
			continue ;

		SOCKET s = pPlayer->GetSocket()->getSOCKET() ;
		Assert( s!=INVALID_SOCKET ) ;

		if( FD_ISSET( s, &m_ExceptFDs[SELECT_USE] ) )
		{
			RemovePlayer( pPlayer, "ĳ����ҶϿ���������" ) ;
		}
	}




	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerPlayerManager::ProcessCommands( )
{
__ENTER_FUNCTION

	BOOL ret ;

	if (m_MinFD == INVALID_SOCKET && m_MaxFD == INVALID_SOCKET) // no player exist
	{ 
		return TRUE ;
	}

	UINT nPlayerCount = GetPlayerNumber() ;
	for( UINT i=0; i<nPlayerCount; i++ )
	{
		if( m_pPlayers[i]==INVALID_ID )
			continue ;

		GamePlayer* pPlayer = g_pPlayerPool->GetPlayer(m_pPlayers[i]) ;
		Assert( pPlayer ) ;

		if( pPlayer->IsDisconnect() )
			continue ;

		SOCKET s = pPlayer->GetSocket()->getSOCKET() ;
		Assert( s!=INVALID_SOCKET ) ;

		if( pPlayer->GetSocket()->isSockError() )
		{//���ӳ��ִ���
			g_pLog->FastSaveLog( LOG_FILE_1, "ERROR CC1 GUID=%X NeedRemove",
				pPlayer->m_HumanGUID ) ;

			RemovePlayer( pPlayer, "ProcessCommandsʱ���ӳ���" ) ;
		}
		else
		{//��������
			_MY_TRY
			{
				ret = pPlayer->ProcessCommand( FALSE ) ;
				if( !ret )
				{
					
					g_pLog->FastSaveLog( LOG_FILE_1, "ERROR CC2 GUID=%X NeedRemove",
						pPlayer->m_HumanGUID ) ;
     
					RemovePlayer( pPlayer, "ProcessCommandִ�н������", TRUE ) ;
					return TRUE;
				}
			}
			_MY_CATCH
			{
				SaveCodeLog( ) ;

				g_pLog->FastSaveLog( LOG_FILE_1, "ERROR CC3 GUID=%X NeedRemove",
					pPlayer->m_HumanGUID ) ;

				RemovePlayer( pPlayer,  "ProcessCommandִ�з����쳣", TRUE ) ;
			}
		}
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerPlayerManager::RemovePlayer( Player* pPlayer, char* szReason, BOOL bReal )
{
__ENTER_FUNCTION

	Assert( pPlayer ) ;

	BOOL ret = FALSE ;

	//��һ�������Socket��Ϣ
	SOCKET fd = pPlayer->GetSocket()->getSOCKET() ;
	if( fd != INVALID_SOCKET )
	{
		DelPlayerSocket( fd ) ;
		pPlayer->Disconnect( ) ;

		g_pLog->FastSaveLog( LOG_FILE_1, "WorkerPlayerManager::RemovePlayer Disconnect(SOCKET=%d)...OK", 
			fd ) ;
	}

	//�ڶ�������������е��������
	Worker* pWorker;
	_MY_TRY
	{
		pWorker = g_pWorkerManager->GetWorker( GetWorkerID() ) ;
		if( pWorker )
		{
			GamePlayer* pGamePlayer = (GamePlayer*)pPlayer ;
			Obj_Human *pHuman = pGamePlayer->GetHuman() ;
			
		}
	}
	_MY_CATCH
	{
		SaveCodeLog( ) ;
	}

	//�����������PlayerManager�е���Ϣ
	if( pPlayer->PlayerManagerID()!=INVALID_ID )
	{
		ret = DelPlayer( pPlayer->PlayerID() ) ;
		if( !ret )
		{
			SaveCodeLog( ) ;
		}
	}

	//���Ĳ������PlayerPool�е���Ϣ��ע��˲������������
	//�����ô˲����󣬵�ǰPlayer���п��ܻᱻ���Ϸ�����½������
	GUID_t guid = ((GamePlayer*)pPlayer)->GetHuman()->GetGUID() ;
	if( guid!=INVALID_ID )
	{
		((GamePlayer*)pPlayer)->FreeOwn() ;
	}

	g_pLog->FastSaveLog( LOG_FILE_1, "WorkerPlayerManager::Real RemovePlayer(GUID=%X)...OK", 
		guid ) ;

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerPlayerManager::AddPlayer( Player* pPlayer )
{
__ENTER_FUNCTION

	if( m_nFDSize>=FD_SETSIZE )
	{//�Ѿ������ܹ������������������
		return FALSE ;
	}

	BOOL ret = PlayerManager::AddPlayer( pPlayer ) ;
	if( !ret )
	{
		Assert( FALSE ) ;
		return FALSE ;
	}


	SOCKET fd = pPlayer->GetSocket()->getSOCKET() ;
	AddPlayerSocket( fd ) ;

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerPlayerManager::AddPlayerSocket( SOCKET fd )
{
__ENTER_FUNCTION

	Assert(fd!=INVALID_SOCKET) ;
	if( FD_ISSET(fd,&m_ReadFDs[SELECT_BAK]) )
	{
		return FALSE ;
	}

	m_MinFD = ((m_MinFD==INVALID_SOCKET)?fd:min(fd , m_MinFD));
	m_MaxFD = ((m_MaxFD==INVALID_SOCKET)?fd:max(fd,m_MaxFD));

	FD_SET(fd , &m_ReadFDs[SELECT_BAK]);
	FD_SET(fd , &m_WriteFDs[SELECT_BAK]);
	FD_SET(fd , &m_ExceptFDs[SELECT_BAK]);

	m_nFDSize++ ;


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerPlayerManager::DelPlayer( PlayerID_t pid )
{
__ENTER_FUNCTION

	Assert( pid!=INVALID_ID) ;

//���PlayerManager�е���Ϣ
	PlayerManager::RemovePlayer( pid ) ;




	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerPlayerManager::DelPlayerSocket( SOCKET fd )
{
__ENTER_FUNCTION

	if( m_MinFD==INVALID_SOCKET )
	{
		g_pLog->FastSaveLog( LOG_FILE_1, "ERROR WorkerPlayerManager::DelPlayerSocket m_MinFD (SOCKET=%d)", 
			fd ) ;
		return FALSE ;
	}
	if( m_MaxFD==INVALID_SOCKET )
	{
		g_pLog->FastSaveLog( LOG_FILE_1, "ERROR WorkerPlayerManager::DelPlayerSocket m_MaxFD (SOCKET=%d)", 
			fd ) ;
		return FALSE ;
	}
	if( fd == INVALID_SOCKET )
	{
		g_pLog->FastSaveLog( LOG_FILE_1, "ERROR WorkerPlayerManager::DelPlayerSocket fd (SOCKET=%d)", 
			fd ) ;
		return FALSE ;
	}
	if( !FD_ISSET(fd,&m_ReadFDs[SELECT_BAK]) )
	{
		g_pLog->FastSaveLog( LOG_FILE_1, "ERROR WorkerPlayerManager::DelPlayerSocket(SOCKET=%d)", 
			fd ) ;
		return FALSE ;
	}


	if( fd==m_MinFD ) 
	{
		SOCKET s = m_MaxFD ;
		UINT nPlayerCount = GetPlayerNumber() ;
		for( UINT i=0; i<nPlayerCount; i++ )
		{
			if( m_pPlayers[i]==INVALID_ID )
				continue ;

			GamePlayer* pPlayer = g_pPlayerPool->GetPlayer(m_pPlayers[i]) ;
			Assert( pPlayer ) ;
			if( pPlayer==NULL )
				continue ;


			SOCKET temp = pPlayer->GetSocket()->getSOCKET() ;
			if( temp == fd )
				continue ;
			if( temp==INVALID_SOCKET )
				continue ;

			if( temp < s )
			{
				s = temp ;
			}
		}

		if( m_MinFD == m_MaxFD )
		{
			m_MinFD = m_MaxFD = INVALID_SOCKET ;
		}
		else
		{
			m_MinFD = s ;
		}
	} 
	else if( fd==m_MaxFD ) 
	{
		SOCKET s = m_MinFD ;
		UINT nPlayerCount = GetPlayerNumber() ;
		for( UINT i=0; i<nPlayerCount; i++ )
		{
			if( m_pPlayers[i]==INVALID_ID )
				continue ;

			GamePlayer* pPlayer = g_pPlayerPool->GetPlayer(m_pPlayers[i]) ;
			Assert( pPlayer ) ;
			if( pPlayer==NULL )
				continue ;


			SOCKET temp = pPlayer->GetSocket()->getSOCKET() ;
			if( temp == fd )
				continue ;
			if( temp==INVALID_SOCKET )
				continue ;

			if( temp > s )
			{
				s = temp ;
			}
		}

		if( m_MaxFD == m_MinFD )
		{
			m_MinFD = m_MaxFD = INVALID_SOCKET ;
		}
		else
		{
			m_MaxFD = s ;
		}
	}

	FD_CLR(fd , &m_ReadFDs[SELECT_BAK]);
	FD_CLR(fd , &m_ReadFDs[SELECT_USE]);
	FD_CLR(fd , &m_WriteFDs[SELECT_BAK]);
	FD_CLR(fd , &m_WriteFDs[SELECT_USE]);
	FD_CLR(fd , &m_ExceptFDs[SELECT_BAK]);
	FD_CLR(fd , &m_ExceptFDs[SELECT_USE]);

	m_nFDSize-- ;
	Assert( m_nFDSize>=0 ) ;



	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerPlayerManager::HeartBeat( UINT uTime )
{
__ENTER_FUNCTION

	BOOL ret ;

	UINT nPlayerCount = GetPlayerNumber() ;
	for( UINT i=0; i<nPlayerCount; i++ )
	{
		if( m_pPlayers[i] == INVALID_ID )
			continue ;

		GamePlayer* pPlayer = g_pPlayerPool->GetPlayer(m_pPlayers[i]) ;
		if( pPlayer==NULL )
		{
			Assert(FALSE) ;
			return FALSE ;
		}

		_MY_TRY
		{
			ret = pPlayer->HeartBeat(uTime ) ;
		}
		_MY_CATCH
		{
			SaveCodeLog( ) ;
			ret = FALSE ;
		}
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

VOID WorkerPlayerManager::RemoveAllPlayer( )
{
__ENTER_FUNCTION

	UINT nPlayerCount = GetPlayerNumber() ;
	for( UINT i=0; i<nPlayerCount; i++ )
	{
		if( m_pPlayers[0] == INVALID_ID )
			break ;

		Player* pPlayer = g_pPlayerPool->GetPlayer(m_pPlayers[0]) ;
		if( pPlayer==NULL )
		{
			Assert(FALSE) ;
			break ;
		}

		RemovePlayer( pPlayer, "������Ҷ��Ͽ�", TRUE ) ;
	}

__LEAVE_FUNCTION
}
