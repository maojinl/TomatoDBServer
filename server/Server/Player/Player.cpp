#include "stdafx.h"

#include "Player.h"
#include "Socket.h"
#include "PacketFactoryManager.h"
#include "TimeManager.h"
#include "Log.h"

using namespace Packets ;

Player::Player( BOOL bIsServer )
{
__ENTER_FUNCTION

	m_PID = INVALID_ID ;
	m_UID = INVALID_ID ;
	m_PlayerManagerID = INVALID_ID ;

	m_pSocket = new Socket ;
	Assert( m_pSocket ) ;
	
	if( bIsServer )
	{
		m_pSocketInputStream = new SocketInputStream( m_pSocket,DEFAULTSOCKETINPUTBUFFERSIZE,64*1024*1024 ) ;
		Assert( m_pSocketInputStream ) ;

		m_pSocketOutputStream = new SocketOutputStream( m_pSocket,DEFAULTSOCKETOUTPUTBUFFERSIZE,64*1024*1024 ) ;
		Assert( m_pSocketOutputStream ) ;
	}
	else
	{
		m_pSocketInputStream = new SocketInputStream( m_pSocket ) ;
		Assert( m_pSocketInputStream ) ;

		m_pSocketOutputStream = new SocketOutputStream( m_pSocket ) ;
		Assert( m_pSocketOutputStream ) ;
	}

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

VOID Player::CleanUp( )
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

VOID Player::Disconnect( )
{
__ENTER_FUNCTION

	_MY_TRY
	{
		m_pSocket->close() ;
	}
	_MY_CATCH
	{
		SaveCodeLog( ) ;
	}

__LEAVE_FUNCTION
}

BOOL Player::IsValid( )
{
__ENTER_FUNCTION

	if( m_pSocket==nullptr ) return FALSE ;

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
		if( (INT)ret <= SOCKET_ERROR )
		{
			g_pLog->FastSaveLog( LOG_FILE_2, "[%d] m_pSocketInputStream->Fill ret:%d %s", 
				g_pTimeManager->Time2DWORD(), (INT)ret, MySocketError() ) ;
			return FALSE ;
		}
	} 
	_MY_CATCH
	{
		SaveCodeLog( ) ;
		return FALSE ;
	}


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Player::ProcessCommand( BOOL Option )
{
__ENTER_FUNCTION

	BOOL ret ;

	Header header;
	PacketID_t packetID = 0;
	UINT packetFlag = 0, packetSize = 0, packetIndex = 0, packetTick = 0;
	Packet* pPacket = nullptr ;

	if( IsDisconnect( ) )
		return TRUE ;

	_MY_TRY
	{
		if( Option ) 
		{//ִ�в���ѡ�����
		}

//ÿ֡����ִ�е���Ϣ��������
#define EXE_COUNT_PER_TICK 12
		for( INT i=0;i<EXE_COUNT_PER_TICK; i++ )
		{
			if( !m_pSocketInputStream->Peek((CHAR *)&header, PACKET_HEADER_SIZE) )
			{//���ݲ��������Ϣͷ
				break ;
			}

			packetID	= header.getPackageId();	//2
			packetTick	= header.getTimestamp();	//4
			packetIndex	= header.index;				//1
			packetSize	= header.getLength();		//4
			packetFlag	= header.flag;				//1

			if(packetID == 532)
			{
				packetID = 532;
			}

			//packetSize = GET_PACKET_LEN(packetuint) ;
			//packetIndex = GET_PACKET_INDEX(packetuint) ;

			if( packetID >= (PacketID_t)PACKET_MAX )
			{//��Ч����Ϣ����
				g_pPacketFactoryManager->RemovePacket( pPacket ) ;
			    g_pLog->FastSaveLog( LOG_FILE_1, "ERROR(>PACKET_MAX) Packid is %d%!! " ,packetID) ;
				return FALSE ;
			}			

			_MY_TRY
			{

				if( m_pSocketInputStream->Length()<packetSize +PACKET_HEADER_SIZE)
				{//��Ϣû�н���ȫ
                    g_pLog->FastSaveLog( LOG_FILE_1, "ERROR (Size) Packid is %d%!! " ,packetID) ;
					break;
				}

				if( packetSize > g_pPacketFactoryManager->GetPacketMaxSize(packetID) )
				{//��Ϣ�Ĵ�С�����쳣���յ�����Ϣ��Ԥ������Ϣ�����ֵ��Ҫ��
//					m_pSocketInputStream->Skip( PACKET_HEADER_SIZE+packetSize ) ;
					g_pLog->FastSaveLog( LOG_FILE_1, "PacketMaxSize!!! packetid is [%d], [%d] > [%d] ", packetID, packetSize, g_pPacketFactoryManager->GetPacketMaxSize(packetID)) ;
					return FALSE ;
				}

				Packet* pPacket = g_pPacketFactoryManager->CreatePacket( packetID ) ;
				if( pPacket==nullptr )
				{//���ܷ��䵽�㹻���ڴ�
//					m_pSocketInputStream->Skip( PACKET_HEADER_SIZE+packetSize ) ;
					g_pLog->FastSaveLog( LOG_FILE_1, "Lack of memory ") ;
					return FALSE ;
				}

				//������Ϣ���к�
				pPacket->SetPacketIndex( packetIndex ) ;


				//��Ϣ���ܴ���--Begin
				{
					UINT t_uSize = packetSize;


					m_pSocketInputStream->Skip(PACKET_HEADER_SIZE);


					UINT t_uHead = m_pSocketInputStream->GetHead();

					UINT t_uTail = m_pSocketInputStream->GetTail();
					UINT t_uBufferLen = m_pSocketInputStream->GetBuffLen();
					CHAR* t_szBuffer = m_pSocketInputStream->GetBuff();
					if ( t_uHead < t_uTail ) 
					{
						this->Decrypt_CS(&t_szBuffer[t_uHead], t_uSize, 0);
					} 
					else 
					{
						UINT rightLen = t_uBufferLen - t_uHead ;
						if( t_uSize <= rightLen ) 
						{
							this->Decrypt_CS(&t_szBuffer[t_uHead], t_uSize, 0);
						} 
						else 
						{
							this->Decrypt_CS(&t_szBuffer[t_uHead], rightLen, 0);
							this->Decrypt_CS(t_szBuffer, t_uSize-rightLen, rightLen);
						}
					}
				}
				//��Ϣ���ܴ���--End

				ret = m_pSocketInputStream->ReadPacket( pPacket ) ;
				if( ret==FALSE )
				{//��ȡ��Ϣ���ݴ���
					g_pLog->FastSaveLog( LOG_FILE_1, "ERROR (Contex) Packid is %d%!! " ,packetID) ;
					g_pPacketFactoryManager->RemovePacket( pPacket ) ;
					return FALSE ;
				}

				BOOL bNeedRemove = TRUE ;
				BOOL bException = FALSE ;

				_MY_TRY
				{
					ResetKick( ) ;

					UINT uret ;
					_MY_TRY
					{
						g_pLog->FastSaveLog( LOG_FILE_1, "R Packid is %d%!! " ,packetID) ;
						LONGLONG	lStartTime = g_pTimeManager->GetAccurateTime();
						uret = pPacket->ExecutePacket( this ) ;
						LONGLONG	lEndTime   = g_pTimeManager->GetAccurateTime();
						g_pLog->FastSaveLog( LOG_FILE_14, "%d\t%u\r\n",packetID,(LONGLONG)(((lEndTime-lStartTime)/(double)g_pTimeManager->GetCpuFrequency())*1000*1000));
					}
					_MY_CATCH
					{
						SaveCodeLog( ) ;
						uret = PACKET_EXE_ERROR ;
					}
					if( uret==PACKET_EXE_ERROR )
					{//�����쳣���󣬶Ͽ����������
						g_pLog->FastSaveLog( LOG_FILE_1, "ERROR (Execute) Packid is %d%!! " ,packetID) ;

						if( pPacket ) 
							g_pPacketFactoryManager->RemovePacket( pPacket ) ;
						return FALSE ;
					}
					else if( uret==PACKET_EXE_BREAK )
					{//��ǰ��Ϣ�Ľ���ִ�н�ֹͣ
					 //ֱ���¸�ѭ��ʱ�ż����Ի����е����ݽ�����Ϣ��ʽ
					 //����ִ�С�
					 //����Ҫ���ͻ��˵�ִ�д�һ������ת�Ƶ�����һ������ʱ��
					 //��Ҫ�ڷ���ת����Ϣ��ִ���ڱ��߳���ֹͣ��
						if( pPacket ) 
							g_pPacketFactoryManager->RemovePacket( pPacket ) ;
						break ;
					}
					else if( uret==PACKET_EXE_CONTINUE )
					{//��������ʣ�µ���Ϣ
					}
					else if( uret==PACKET_EXE_NOTREMOVE )
					{//��������ʣ�µ���Ϣ�����Ҳ����յ�ǰ��Ϣ
						bNeedRemove = FALSE ;
					}
					else if( uret == PACKET_EXE_NOTREMOVE_ERROR )
					{
						g_pLog->FastSaveLog( LOG_FILE_1, "ERROR(Execute -- not remove) Packid is %d%!! " ,packetID) ;
						return FALSE ;
					}
					else
					{//δ֪�ķ���ֵ
					}
				}
				_MY_CATCH
				{
					SaveCodeLog( ) ;
					bException = TRUE ;
				}

				if( pPacket && bNeedRemove ) 
					g_pPacketFactoryManager->RemovePacket( pPacket ) ;

				if( bException )
					return FALSE ;
			}
			_MY_CATCH
			{
				SaveCodeLog( ) ;
				return FALSE ;
			}
		}
	}
	_MY_CATCH
	{
		SaveCodeLog( ) ;
		return FALSE ;
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

		UINT ret = m_pSocketOutputStream->Flush( ) ;
		if( (INT)ret <= SOCKET_ERROR )
		{
			g_pLog->FastSaveLog( LOG_FILE_2, "[%d] m_pSocketOutputStream->Flush ret:%d %s", 
				g_pTimeManager->Time2DWORD(), (INT)ret, MySocketError() ) ;
			return FALSE ;
		}
	} 
	_MY_CATCH
	{
		SaveCodeLog( ) ;
		return FALSE ;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}


//#define _DEBUG_CIAO
#ifdef _DEBUG_CIAO
#include "Packet.h"
//==========================================
VOID MyTraceOut( Socket* pSocket, const Packet* pPacket )
{
	HANDLE hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO oldInfo;
	GetConsoleScreenBufferInfo(hStdOut, &oldInfo);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED|FOREGROUND_INTENSITY);


	//--- time
	SYSTEMTIME timeNow;
	::GetLocalTime(&timeNow);
	printf("[%d] %02d:%02d %02d.%03d   ", (INT)(pSocket->getSOCKET()),
		timeNow.wHour, timeNow.wMinute, timeNow.wSecond, timeNow.wMilliseconds);

	//----------------------
	switch(pPacket->GetPacketID())
	{
	case PACKET_GC_CONNECT:
		printf("PACKET_GC_CONNECT\n");
		break;
		
	case PACKET_GC_ENTERSCENE:
		printf("PACKET_GC_ENTERSCENE\n");
		break;
		
	case PACKET_GC_LEAVESCENE:
		printf("PACKET_GC_LEAVESCENE\n");
		break;
		
	case PACKET_GC_NEWPLAYER:
		printf("PACKET_GC_NEWPLAYER\n");
		break;
		
	case PACKET_GC_NEWMONSTER:
		printf("PACKET_GC_NEWMONSTER\n");
		break;
		
	case PACKET_GC_NEWITEM:
		printf("PACKET_GC_NEWITEM\n");
		break;
		
	case PACKET_GC_PLAYERREALMOVE:
		printf("PACKET_GC_PLAYERREALMOVE\n");
		break;
		
	case PACKET_GC_MONSTERREALMOVE:
		printf("PACKET_GC_MONSTERREALMOVE\n");
		break;
		
	case PACKET_GC_MYEQUIPMENT:
		printf("PACKET_GC_MYEQUIPMENT\n");
		break;
		
	case PACKET_GC_OTHEREQUIPMENT:
		printf("PACKET_GC_OTHEREQUIPMENT\n");
		break;
		
	case PACKET_GC_TEST:
		printf("PACKET_GC_TEST\n");
		break;
		
	case PACKET_GC_MOVE:
		printf("PACKET_GC_MOVE\n");
		break;
		
	case PACKET_GC_ARRIVE:
		printf("PACKET_GC_ARRIVE\n");
		break;
		
	case PACKET_GC_ATTACK:
		printf("PACKET_GC_ATTACK\n");
		break;
		
	case PACKET_GC_OTHERATTACK:
		printf("PACKET_GC_OTHERATTACK\n");
		break;
		
	case PACKET_GC_ERRORATTACK:
		printf("PACKET_GC_ERRORATTACK\n");
		break;
		
	case PACKET_GC_SKILL:
		printf("PACKET_GC_SKILL\n");
		break;
		
	case PACKET_GC_OTHERSKILL:
		printf("PACKET_GC_OTHERSKILL\n");
		break;
		
	case PACKET_GC_ERRORSKILL:
		printf("PACKET_GC_ERRORSKILL\n");
		break;

	default:
		printf("[%d]UNKNOWN!!!", pPacket->GetPacketID());
		break;
	}

	SetConsoleTextAttribute(hStdOut, oldInfo.wAttributes);
}
//==========================================
#endif

BOOL Player::SendPacket( Packet* pPacket )
{
__ENTER_FUNCTION

	if( IsDisconnect( ) )
		return TRUE ;

	if( m_pSocketOutputStream!=nullptr )
	{
		Header header;

		pPacket->SetPacketIndex( m_PacketIndex++ ) ;

		header.setPackageId(pPacket->GetPacketID());
		header.setTimestamp(g_pTimeManager->RunTick());
		header.index = pPacket->GetPacketIndex() ;
		header.setLength(pPacket->GetPacketSize());
		header.flag = pPacket->GetPacketRetFlag();

		PacketID_t packetID = pPacket->GetPacketID() ;
		UINT w;
		if ( packetID > PACKET_MAX)//PACKET_LC_MAXCOUNT)
		{
			//w = m_pSocketOutputStream->Write_ex( PACK_COMPART , PACK_COMPART_SIZE ) ;
			g_pLog->FastSaveLog( LOG_FILE_1, "ERROR Packid is %d%!! " ,packetID) ;
			return TRUE;
		}

		

		w = m_pSocketOutputStream->Write( (CHAR*)&header , sizeof(Header) ) ;

		//UINT packetUINT ;
		//UINT packetSize = pPacket->GetPacketSize( ) ;
		//UINT packetIndex = pPacket->GetPacketIndex() ;

		//SET_PACKET_INDEX(packetUINT, packetIndex) ;
		//SET_PACKET_LEN(packetUINT, packetSize) ;

		//w = m_pSocketOutputStream->Write( (CHAR*)&packetUINT, sizeof(UINT) ) ;
		UINT t_uTail_Begin = m_pSocketOutputStream->GetTail();//��ѯ��ǰ��βλ�á���¼д��ǰλ��

		BOOL ret = pPacket->Write( *m_pSocketOutputStream ) ;

		UINT t_uTail_End = m_pSocketOutputStream->GetTail();//��ѯ��ǰ��βλ�á���¼д����λ��

		//��Ϣ���ܴ���--Begin
		{
			UINT t_uSize = header.getLength();
			//UINT t_uHead = m_pSocketOutputStream->GetHead();
			//UINT t_uTail = m_pSocketOutputStream->GetTail();
			UINT t_uBufferLen = m_pSocketOutputStream->GetBuffLen();
			CHAR* t_szBuffer = m_pSocketOutputStream->GetBuff();
			if ( t_uTail_Begin < t_uTail_End ) 
			{
				this->Encrypt_SC(&(t_szBuffer[t_uTail_Begin]), t_uSize, 0);
			} 
			else
			{
				UINT rightLen = t_uBufferLen - t_uTail_Begin ;
				if( t_uSize <= rightLen ) 
				{
					this->Encrypt_SC(&(t_szBuffer[t_uTail_Begin]), t_uSize, 0);
				} 
				else 
				{
					this->Encrypt_SC(&(t_szBuffer[t_uTail_Begin]), rightLen, 0);
					this->Encrypt_SC(t_szBuffer, t_uSize-rightLen, rightLen);
				}
			}
		}
		//��Ϣ���ܴ���--End

		if(pPacket->GetPacketSize() != t_uTail_End-t_uTail_Begin)
		{
			g_pLog->FastSaveLog( LOG_FILE_6, "!!!!!!!PacketSizeError! ID=%d(Write%d,Should%d)", 
				pPacket->GetPacketID(), 
				t_uTail_End-t_uTail_Begin-PACKET_HEADER_SIZE, pPacket->GetPacketSize());
		}

#ifdef _DEBUG_CIAO
//=========================================
	MyTraceOut(m_pSocket, pPacket);
//=========================================
#endif	
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Player::HeartBeat( UINT uTime, INT nFlag )
{
__ENTER_FUNCTION


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

VOID Player::ResetKick( )
{
__ENTER_FUNCTION
__LEAVE_FUNCTION
}


