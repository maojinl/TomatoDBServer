
/************************************************************************
*  更新时间 2010.7.23
*  更新人:  DGH
*  文件名:	WGMail.h
*  功能:	world转发邮件给server。
*			执行脚本内容(执行完所有的脚本邮件)；
*			实现普通邮件(系统邮件)转发;
************************************************************************/

#ifndef __WGMAIL_H__
#define __WGMAIL_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class WGMail : public Packet 
	{
	public:
		WGMail( ){} ;
		virtual ~WGMail( ){} ;

		//公用继承接口
		virtual BOOL			Read( SocketInputStream& iStream ) ;
		virtual BOOL			Write( SocketOutputStream& oStream )const ;
		virtual UINT			Execute( Player* pPlayer ) ;

		virtual PacketID_t		GetPacketID()const { return PACKET_WG_MAIL ; }
		virtual UINT			GetPacketSize()const 
		{ 
			return	sizeof(PlayerID_t)+
					sizeof(m_GUID)+
					sizeof(UINT)*2 ;
		}

	public:
		//使用数据接口
		VOID		SetPlayerID( PlayerID_t pid ){ m_PlayerID = pid ; } ;
		PlayerID_t	GetPlayerID( ){ return m_PlayerID ; } ;

		VOID		SetGUID( GUID_t guid ){	m_GUID = guid ; }
		GUID_t		GetGUID( ){ return m_GUID ; }

		VOID  SetPageIndex(UINT index){m_PageIndex = index;}
		UINT  GetPageIndex(){return m_PageIndex;}

		VOID  SetPageRowCount(UINT rowCnt){ m_PageRowCount = rowCnt; }
		UINT  GetPageRowCount(){ return m_PageRowCount; }
	private:
		//数据
		PlayerID_t	m_PlayerID ;//收信人的PlayerID
		GUID_t		m_GUID ;

		UINT  m_PageIndex;
		UINT  m_PageRowCount;

	};


	class WGMailFactory : public PacketFactory 
	{
	public:
		Packet*		CreatePacket() { return new WGMail() ; }
		PacketID_t	GetPacketID()const { return PACKET_WG_MAIL ; }
		UINT		GetPacketMaxSize()const { return	sizeof(PlayerID_t)+
														sizeof(GUID_t)+
														sizeof(UINT)*2; }
	};


	class WGMailHandler 
	{
	public:
          static UINT Execute(WGMail* pPacket, Player* pPlayer);
	};

};

using namespace Packets ;

#endif
