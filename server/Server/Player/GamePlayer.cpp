#include "stdafx.h"


#include "GamePlayer.h"
#include "PacketFactoryManager.h"
#include "PlayerPool.h"
#include "WorkerManager.h"
#include "GUIDManager.h"
#include "TimeManager.h"
#include "Log.h"
#include "ServerManager.h"
#include "RecyclePlayerManager.h"
#include "Obj_Human.h"

GamePlayer::GamePlayer( )
{
__ENTER_FUNCTION

	m_Status = PS_SERVER_EMPTY ;
//	m_GamePlayerSceneID = INVALID_ID ;
	m_KickTime = 0 ;

	m_LastSendTime	 = 0 ;
	m_KickTime		 = 0 ;
	m_CurrentTime	 = 0 ;
	m_LeftTimeToQuit = 0 ;

	m_SaveTime = 0 ;

	m_pHuman = new Obj_Human();
	m_pHuman->SetPlayer(this);

__LEAVE_FUNCTION
}

GamePlayer::~GamePlayer( )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

VOID GamePlayer::CleanUp( )
{
__ENTER_FUNCTION

	m_Status = PS_SERVER_EMPTY ;
	m_KickTime = 0 ;

	m_LastSendTime = 0 ;
	m_CurrentTime = 0 ;
	m_LeftTimeToQuit = 0 ;
	ResetKick( ) ;

	return Player::CleanUp( ) ;

__LEAVE_FUNCTION
}

BOOL GamePlayer::ProcessCommand( BOOL Option )
{
__ENTER_FUNCTION

	BOOL ret = Player::ProcessCommand( Option ) ;
	return ret;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL GamePlayer::ProcessInput( )
{
__ENTER_FUNCTION

	BOOL ret = Player::ProcessInput( ) ;
	return ret;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL GamePlayer::ProcessOutput( )
{
__ENTER_FUNCTION

	BOOL ret = Player::ProcessOutput( ) ;
	return ret;

__LEAVE_FUNCTION
	return FALSE;
}

BOOL GamePlayer::SendPacket( Packet* pPacket )
{
__ENTER_FUNCTION

	return Player::SendPacket( pPacket ) ;

__LEAVE_FUNCTION

	return FALSE ;
}


BOOL GamePlayer::HeartBeat( UINT uTime, INT nFlag )
{
__ENTER_FUNCTION

	if( IsDisconnect())
	{
		return FALSE ;
	}

	m_LastSendTime -= (uTime-m_CurrentTime) ;

	m_CurrentTime =uTime ;

#ifndef _DEBUG
	if( nFlag )
	{
		if(uTime>m_KickTime+MAX_INCOM_KICK_TIME )
		{
			g_pLog->FastSaveLog( LOG_FILE_1, "ERROR: Incoming Player::HeartBeat Didn't recv message for too long time. Kicked!" ) ;
			return FALSE ;
		}
	}
	else
	{
		//如果Player在一定时间内没有收到任何消息，则断开客户端连接
		//在Player处理消息前会执行ResetKick函数修正m_KickTime信息
		if(uTime>m_KickTime+MAX_KICK_TIME )
		{
			g_pLog->FastSaveLog( LOG_FILE_1, "ERROR: Player::HeartBeat Didn't recv message for too long time. Kicked!" ) ;
			return FALSE ;
		}
	}
#endif
	return Player::HeartBeat(uTime) ;

__LEAVE_FUNCTION

	return FALSE ;
}


BOOL GamePlayer::FreeOwn( )
{
__ENTER_FUNCTION
	SetPlayerStatus( PS_SERVER_LEAVE_RECYCLE ) ;

	CleanUp( ) ;

	g_pPlayerPool->DelPlayer( PlayerID() ) ;

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

VOID GamePlayer::Init( )
{
__ENTER_FUNCTION

	SetDisconnect( FALSE ) ;
	ResetKick() ;
	SetDirty( TRUE ) ;

__LEAVE_FUNCTION
}

BOOL GamePlayer::CheckKey( UINT key )
{
__ENTER_FUNCTION
	
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

VOID GamePlayer::Disconnect( )
{
__ENTER_FUNCTION

	_MY_TRY
	{
		m_LeftTimeToQuit = 0 ;
		SetDisconnect( TRUE ) ;
	}
	_MY_CATCH
	{
		SaveCodeLog( ) ;
	}

	Player::Disconnect( ) ;

__LEAVE_FUNCTION
}

VOID GamePlayer::ResetKick( )
{
__ENTER_FUNCTION

	m_KickTime = g_pTimeManager->CurrentSavedTime() ;

	Player::ResetKick( ) ;

__LEAVE_FUNCTION
}
