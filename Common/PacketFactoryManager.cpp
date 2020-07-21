#include "stdafx.h"

#include "PacketFactoryManager.h"

#if defined(_TMT_WORLD) && defined(_TMT_SERVER)
#include "WGMail.h"
#include "WGSystemMsg.h"
#include "GWSystemMsg.h"
#include "GWAskMail.h"
#endif

#if defined(_TMT_CLIENT) && defined(_TMT_SERVER)
#include "SSConnect.h"
#include "CSAskLogin.h"
#include "SCRetLogin.h"
#include "CSAskDBDefinition.h"
#include "SCRetDBDefinition.h"
#include "CSAskDBManipulate.h"
#include "SCRetDBManipulate.h"
#include "CSAskDBQuery.h"
#include "SCRetDBQuery.h"

#endif

using namespace Packets;

PacketFactoryManager* g_pPacketFactoryManager = nullptr ;

PacketFactoryManager::PacketFactoryManager( ) 
{
__ENTER_FUNCTION

	m_Factories = nullptr ;
	m_Size = PACKET_MAX ;

	Assert( m_Size>0 ) ;
	
	m_Factories = new PacketFactory*[ m_Size ];
	Assert( m_Factories ) ;
	m_pPacketAllocCount = new UINT[m_Size] ;
	Assert( m_pPacketAllocCount ) ;
	
	for( INT i=0; i<m_Size; i++ ) 
	{
		m_Factories[i] = nullptr ;
		m_pPacketAllocCount[i] = 0 ;
	}
			
__LEAVE_FUNCTION
}

PacketFactoryManager::~PacketFactoryManager( ) 
{
__ENTER_FUNCTION
		
	Assert( m_Factories!=nullptr ) ;

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

#if defined(_TMT_CLIENT) && defined(_TMT_SERVER)
//CS && SC
	AddFactory( new CSAskLoginFactory()) ;
	AddFactory( new SCRetLoginFactory()) ;
	AddFactory(new CSAskDBDefinitionFactory());
	AddFactory(new SCRetDBDefinitionFactory());
	AddFactory(new CSAskDBManipulateFactory());
	AddFactory(new SCRetDBManipulateFactory());
	AddFactory(new CSAskDBQueryFactory());
	AddFactory(new SCRetDBQueryFactory());
#endif

#if defined(_TMT_WORLD) && defined(_TMT_SERVER)
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
		
	if( m_Factories[pFactory->GetPacketID()]!=nullptr ) 
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

	if( packetID>=m_Size || m_Factories[packetID]==nullptr ) 
	{
		Assert(FALSE) ;
		return nullptr ;
	}

	Packet* pPacket = nullptr ;
	Lock() ;
	_MY_TRY
	{
		pPacket = m_Factories[packetID]->CreatePacket();
		m_pPacketAllocCount[packetID]++ ;
	}
	_MY_CATCH
	{
		pPacket = nullptr ;
	}
	Unlock() ;

	return pPacket ;
			
__LEAVE_FUNCTION

	return nullptr ;
}

UINT PacketFactoryManager::GetPacketMaxSize( PacketID_t packetID ) 
{
__ENTER_FUNCTION


	if( packetID>=m_Size || m_Factories[packetID]==nullptr ) 
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

	if( pPacket==nullptr )
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



