#include "stdafx.h"

#include "PacketFactoryManager.h"

#if defined(_JSF_WORLD) && defined(_JSF_SERVER)
#include "WGMail.h"
#include "WGSystemMsg.h"
#include "GWSystemMsg.h"
#include "GWAskMail.h"
#endif

#if defined(_JSF_CLIENT) && defined(_JSF_SERVER)
#include "SSConnect.h"
#include "CGEnterScene.h"
#include "GCEnterScene.h"
#endif

using namespace Packets;

PacketFactoryManager* g_pPacketFactoryManager = NULL ;

PacketFactoryManager::PacketFactoryManager( ) 
{
__ENTER_FUNCTION

	m_Factories = NULL ;
	m_Size = PACKET_MAX ;

	Assert( m_Size>0 ) ;
	
	m_Factories = new PacketFactory*[ m_Size ];
	Assert( m_Factories ) ;
	m_pPacketAllocCount = new UINT[m_Size] ;
	Assert( m_pPacketAllocCount ) ;
	
	for( INT i=0; i<m_Size; i++ ) 
	{
		m_Factories[i] = NULL ;
		m_pPacketAllocCount[i] = 0 ;
	}
			
__LEAVE_FUNCTION
}

PacketFactoryManager::~PacketFactoryManager( ) 
{
__ENTER_FUNCTION
		
	Assert( m_Factories!=NULL ) ;

	for( INT i=0; i<m_Size; i++ ) 
	{
		SAFE_DELETE(m_Factories[i]) ;
	}
	
	SAFE_DELETE_ARRAY(m_Factories) ;
	SAFE_DELETE_ARRAY(m_pPacketAllocCount) ;
			
__LEAVE_FUNCTION
}

BOOL PacketFactoryManager::Init( )
{
__ENTER_FUNCTION

#if defined(_JSF_CLIENT) && defined(_JSF_SERVER)
//CG && GC
	AddFactory( new CGEnterSceneFactory()) ;
	AddFactory( new GCEnterSceneFactory()) ;
#endif

#if defined(_JSF_WORLD) && defined(_JSF_SERVER)
//GW && WG
    AddFactory(new WGSystemMsgFactory());
	AddFactory( new GWSystemMsgFactory());
	AddFactory( new WGMailFactory()) ;
    AddFactory(new GWAskMailFactory());
	return TRUE ;
#endif

__LEAVE_FUNCTION

	return FALSE ;
}

VOID PacketFactoryManager::AddFactory( PacketFactory* pFactory ) 
{
__ENTER_FUNCTION
		
	if( m_Factories[pFactory->GetPacketID()]!=NULL ) 
	{//重复设定
        UINT I=pFactory->GetPacketID();
		Assert( FALSE ) ;
		return ;
	}
	
	m_Factories[pFactory->GetPacketID()] = pFactory ;
			
__LEAVE_FUNCTION
}

Packet* PacketFactoryManager::CreatePacket( PacketID_t packetID ) 
{
__ENTER_FUNCTION

	if( packetID>=m_Size || m_Factories[packetID]==NULL ) 
	{
		Assert(FALSE) ;
		return NULL ;
	}

	Packet* pPacket = NULL ;
	Lock() ;
	_MY_TRY
	{
		pPacket = m_Factories[packetID]->CreatePacket();
		m_pPacketAllocCount[packetID]++ ;
	}
	_MY_CATCH
	{
		pPacket = NULL ;
	}
	Unlock() ;

	return pPacket ;
			
__LEAVE_FUNCTION

	return NULL ;
}

UINT PacketFactoryManager::GetPacketMaxSize( PacketID_t packetID ) 
{
__ENTER_FUNCTION


	if( packetID>=m_Size || m_Factories[packetID]==NULL ) 
	{
		char buff[256] = {0};
		sprintf(buff,"PacketID= %d 消息没有注册到PacketFactoryManager上",packetID);
		AssertEx(FALSE,buff) ;
		return 0 ;
	}

	Lock() ;
	UINT iRet = m_Factories[packetID]->GetPacketMaxSize( ) ;
	Unlock() ;

	return iRet ;
			
__LEAVE_FUNCTION

	return 0 ;
}

VOID PacketFactoryManager::RemovePacket( Packet* pPacket )
{
__ENTER_FUNCTION

	if( pPacket==NULL )
	{
		Assert(FALSE) ;
		return ;
	}

	PacketID_t packetID = pPacket->GetPacketID() ;

	if( packetID>=m_Size ) 
	{
		Assert(FALSE) ;
		return ;
	}

	Lock() ;
	_MY_TRY
	{
		SAFE_DELETE( pPacket ) ;
		m_pPacketAllocCount[packetID] -- ;
	}
	_MY_CATCH
	{
	}
	Unlock() ;
	return ;

__LEAVE_FUNCTION

	return ;
}



