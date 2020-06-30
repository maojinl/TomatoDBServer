#include "stdafx.h"

#include "Player.h"
#include "Socket.h"
#include "PacketFactoryManager.h"
#include "TimeManager.h"
#include "Log.h"

using namespace Packets ;

Player::Player( )
{
__ENTER_FUNCTION

	m_PID = INVALID_ID ;
	m_UID = INVALID_ID ;
	m_PlayerManagerID = INVALID_ID ;


	m_pSocket = new Socket ;
	Assert( m_pSocket ) ;

	m_pSocketInputStream = new SocketInputStream( m_pSocket,DEFAULTSOCKETINPUTBUFFERSIZE,64*1024*1024 ) ;
	Assert( m_pSocketInputStream ) ;

	m_pSocketOutputStream = new SocketOutputStream( m_pSocket,DEFAULTSOCKETOUTPUTBUFFERSIZE,64*1024*1024 ) ;
	Assert( m_pSocketOutputStream ) ;

	m_IsEmpty		= TRUE ;
	m_IsDisconnect	= FALSE ;

	m_PacketIndex	 = 0 ;

__LEAVE_FUNCTION
}

Player::~Player( )
{
__ENTER_FUNCTION

	SAFE_DELETE( m_pSocketInputStream ) ;
	SAFE_DELETE( m_pSocketOutputStream ) ;

	SAFE_DELETE( m_pSocket ) ;

__LEAVE_FUNCTION
}

void Player::CleanUp( )
{
__ENTER_FUNCTION

	m_pSocket->close() ;
	m_pSocketInputStream->CleanUp() ;
	m_pSocketOutputStream->CleanUp() ;
	SetPlayerManagerID( INVALID_ID ) ;
	SetUserID( INVALID_ID ) ;
	m_PacketIndex = 0 ;
	SetDisconnect(FALSE) ;


__LEAVE_FUNCTION
}

void Player::Disconnect( )
{
__ENTER_FUNCTION

	_MY_TRY
	{
		m_pSocket->close() ;
	}
	_MY_CATCH
	{
	}

__LEAVE_FUNCTION
}

BOOL Player::IsValid( )
{
__ENTER_FUNCTION

	if( m_pSocket==NULL ) return FALSE ;

	if( !m_pSocket->isValid() ) return FALSE ;


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Player::ProcessInput( )
{
__ENTER_FUNCTION

	if( IsDisconnect() )
		return TRUE ;

	_MY_TRY 
	{
		UINT ret = m_pSocketInputStream->Fill( ) ;
		if( (int)ret <= SOCKET_ERROR )
		{
			Log::SaveLog( SERVER_ERRORFILE, "[%d] m_pSocketInputStream->Fill ret:%d %s", 
				g_pTimeManager->Time2DWORD(), (int)ret, MySocketError() ) ;
			return FALSE ;
		}
	} 
	_MY_CATCH
	{
		return FALSE ;
	}


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Player::ProcessCommand( bool Option )
{
__ENTER_FUNCTION

	BOOL ret ;

	Header header;
	PacketID_t packetID;
	UINT packetFlag = 0, packetSize = 0, packetIndex = 0, packetTick = 0;
	Packet* pPacket = NULL ;

	if( IsDisconnect( ) )
		return TRUE ;

	_MY_TRY
	{
		if( Option ) 
		{//执行部分选项操作
		}

//每帧可以执行的消息数量上限
#define EXE_COUNT_PER_TICK 120
		for( INT i=0;i<EXE_COUNT_PER_TICK; i++ )
		{
			if( !m_pSocketInputStream->Peek((CHAR *)&header, PACKET_HEADER_SIZE) )
			{//数据不能填充消息头
				break ;
			}

			packetID	= header.getPackageId();	//2
			packetTick	= header.getTimestamp();	//4
			packetIndex	= header.index;				//1
			packetSize	= header.getLength();		// 2
			packetFlag	= header.flag;				//1

			//packetSize = GET_PACKET_LEN(packetuint) ;
			//packetIndex = GET_PACKET_INDEX(packetuint) ;

			if( packetID >= (PacketID_t)PACKET_MAX )
			{//无效的消息类型
				Assert( FALSE ) ;
				return FALSE ;
			}

			//消息解密处理--Begin
			//{
			//	UINT t_uSize = packetSize+PACKET_HEADER_SIZE;
			//	UINT t_uHead = m_pSocketInputStream->GetHead();
			//	UINT t_uTail = m_pSocketInputStream->GetTail();
			//	UINT t_uBufferLen = m_pSocketInputStream->GetBuffLen();
			//	CHAR* t_szBuffer = m_pSocketInputStream->GetBuff();
			//	if ( t_uHead < t_uTail ) 
			//	{
			//		this->Decrypt_CS(&t_szBuffer[t_uHead], t_uSize, 0);
			//	} 
			//	else 
			//	{
			//		UINT rightLen = t_uBufferLen - t_uHead ;
			//		if( t_uSize <= rightLen ) 
			//		{
			//			this->Decrypt_CS(&t_szBuffer[t_uHead], t_uSize, 0);
			//		} 
			//		else 
			//		{
			//			this->Decrypt_CS(&t_szBuffer[t_uHead], rightLen, 0);
			//			this->Decrypt_CS(t_szBuffer, t_uSize-rightLen, rightLen);
			//		}
			//	}
			//}
			//消息解密处理--End

			_MY_TRY
			{

				if( m_pSocketInputStream->Length()<PACKET_HEADER_SIZE+packetSize )
				{//消息没有接收全
					break;
				}

				if( packetSize>g_pPacketFactoryManager->GetPacketMaxSize(packetID) )
				{//消息的大小出现异常，收到的消息比预定义消息的最大值还要大
					Assert( FALSE ) ;
					return FALSE ;
				}

				Packet* pPacket = g_pPacketFactoryManager->CreatePacket( packetID ) ;
				if( pPacket==NULL )
				{//不能分配到足够的内存
					Assert( FALSE ) ;
					return FALSE ;
				}

				//设置消息序列号
				pPacket->SetPacketIndex( packetIndex ) ;


				m_pSocketInputStream->Skip(PACKET_HEADER_SIZE);
				ret = m_pSocketInputStream->ReadPacket( pPacket ) ;
				if( ret==FALSE )
				{//读取消息内容错误
					Assert( FALSE ) ;
					g_pPacketFactoryManager->RemovePacket( pPacket ) ;
					return FALSE ;
				}

				BOOL bNeedRemove = TRUE ;

				_MY_TRY
				{
					//修正m_KickTime信息，m_KickTime信息中的值为判断是否需要踢掉
					//客户端的依据
					ResetKick( ) ;

					UINT uret ;
					_MY_TRY
					{
						uret = pPacket->Execute( this ) ;
					}
					_MY_CATCH
					{
						uret=PACKET_EXE_ERROR ;
					}
					if( uret==PACKET_EXE_ERROR )
					{//出现异常错误，断开此玩家连接
						if( pPacket ) 
							g_pPacketFactoryManager->RemovePacket( pPacket ) ;
						return FALSE ;
					}
					else if( uret==PACKET_EXE_BREAK )
					{//当前消息的解析执行将停止
					 //直到下个循环时才继续对缓存中的数据进行消息格式
					 //化和执行。
					 //当需要将客户端的执行从一个场景转移到另外一个场景时：
					 //需要在发送转移消息后将执行在本线程中停止。
						if( pPacket ) 
							g_pPacketFactoryManager->RemovePacket( pPacket ) ;
						break ;
					}
					else if( uret==PACKET_EXE_CONTINUE )
					{//继续解析剩下的消息
					}
					else if( uret==PACKET_EXE_NOTREMOVE )
					{//继续解析剩下的消息，并且不回收当前消息
						bNeedRemove = FALSE ;
					}
					else if( uret==PACKET_EXE_NOTREMOVE_ERROR )
					{
						return FALSE ;
					}
					else
					{//未知的返回值
						Assert(FALSE) ;
					}
				}
				_MY_CATCH
				{
				}

				if( pPacket && bNeedRemove ) 
					g_pPacketFactoryManager->RemovePacket( pPacket ) ;
			}
			_MY_CATCH
			{
			}
		}
	}
	_MY_CATCH
	{
	}



	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Player::ProcessOutput( )
{
__ENTER_FUNCTION

	if( IsDisconnect( ) )
		return TRUE ;

	_MY_TRY
	{
		UINT size = m_pSocketOutputStream->Length() ;
		if( size==0 )
		{
			return TRUE ;
		}
//		else if( size < MAX_SEND_SIZE )
//		{//缓存中的数据小于一定长度时，不是每次都发送数据
//			if( m_CurrentTime < m_LastSendTime+MAX_SEND_TIME )
//			{//判断上一次发送数据离现在时间是否超过一定时间，如果不超过则不发送数据
//				return TRUE ;
//			}
//		}
//		m_LastSendTime = m_CurrentTime ;

		UINT ret = m_pSocketOutputStream->Flush( ) ;
		if( (int)ret <= SOCKET_ERROR )
		{
			Log::SaveLog( SERVER_ERRORFILE, "[%d] m_pSocketOutputStream->Flush ret:%d %s", 
				g_pTimeManager->Time2DWORD(), (int)ret, MySocketError() ) ;
			return FALSE ;
		}
	} 
	_MY_CATCH
	{
		return FALSE ;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}


BOOL Player::SendPacket( Packet* pPacket )
{
__ENTER_FUNCTION

	if( IsDisconnect( ) )
		return TRUE ;

	if( m_pSocketOutputStream!=NULL )
	{
		Header header;

		pPacket->SetPacketIndex( m_PacketIndex++ ) ;

		header.setPackageId(pPacket->GetPacketID());
		header.setTimestamp(g_pTimeManager->RunTick());
		header.index = pPacket->GetPacketIndex() ;
		header.setLength(pPacket->GetPacketSize());
		header.flag = pPacket->GetPacketRetFlag();

		UINT w;
		//if ( packetID < PACKET_MAX)//PACKET_LC_MAXCOUNT)
		//{
		//	w = m_pSocketOutputStream->Write_ex( PACK_COMPART , PACK_COMPART_SIZE ) ;
		//}

		UINT t_uTail_Begin = m_pSocketOutputStream->GetTail();//查询当前包尾位置。记录写包前位置

		w = m_pSocketOutputStream->Write( (CHAR*)&header , sizeof(Header) ) ;

		//UINT packetUINT ;
		//UINT packetSize = pPacket->GetPacketSize( ) ;
		//UINT packetIndex = pPacket->GetPacketIndex() ;

		//SET_PACKET_INDEX(packetUINT, packetIndex) ;
		//SET_PACKET_LEN(packetUINT, packetSize) ;

		//w = m_pSocketOutputStream->Write( (CHAR*)&packetUINT, sizeof(UINT) ) ;

		BOOL ret = pPacket->Write( *m_pSocketOutputStream ) ;

		UINT t_uTail_End = m_pSocketOutputStream->GetTail();//查询当前包尾位置。记录写包后位置

		////消息加密处理--Begin
		//{
		//	UINT t_uSize = t_uTail_End - t_uTail_Begin;
		//	UINT t_uHead = m_pSocketOutputStream->GetHead();
		//	UINT t_uTail = m_pSocketOutputStream->GetTail();
		//	UINT t_uBufferLen = m_pSocketOutputStream->GetBuffLen();
		//	CHAR* t_szBuffer = m_pSocketOutputStream->GetBuff();
		//	if ( t_uHead < t_uTail ) 
		//	{
		//		this->Encrypt_SC(&(t_szBuffer[t_uTail_Begin]), t_uSize, 0);
		//	} 
		//	else
		//	{
		//		UINT rightLen = t_uBufferLen - t_uHead ;
		//		if( t_uSize <= rightLen ) 
		//		{
		//			this->Encrypt_SC(&(t_szBuffer[t_uTail_Begin]), t_uSize, 0);
		//		} 
		//		else 
		//		{
		//			this->Encrypt_SC(&(t_szBuffer[t_uTail_Begin]), rightLen, 0);
		//			this->Encrypt_SC(t_szBuffer, t_uSize-rightLen, rightLen);
		//		}
		//	}
		//}
		////消息加密处理--End

		//BOOL ret = m_pSocketOutputStream->WritePacket( pPacket ) ;
		Assert( ret ) ;
		//Log::SaveLog( "./Log/LoginDebug.log", "SendPacket! SOCKET=%d, ID=%d", 
		//	m_pSocket->getSOCKET(), pPacket->GetPacketID() ) ;
		
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Player::HeartBeat( DWORD dwTime )
{
__ENTER_FUNCTION



	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

void Player::ResetKick( )
{
__ENTER_FUNCTION
__LEAVE_FUNCTION
}


