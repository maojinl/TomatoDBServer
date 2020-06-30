

#ifndef __GWASKMAIL_H__
#define __GWASKMAIL_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"


namespace Packets
{
	class GWAskMail : public Packet 
	{
	public:
		GWAskMail( ){} ;
		virtual ~GWAskMail( ){} ;

		//公用继承接口
		virtual BOOL			Read( SocketInputStream& iStream ) ;
		virtual BOOL			Write( SocketOutputStream& oStream )const ;
		virtual UINT			Execute( Player* pPlayer ) ;

		virtual PacketID_t		GetPacketID()const { return PACKET_GW_ASKMAIL ; }
		virtual UINT			GetPacketSize()const { return	sizeof(GUID_t)+
																sizeof(UINT)*3 ; }

	public :

	public:
		//使用数据接口
		VOID				SetGUID( GUID_t guid ){	m_GUID = guid ; }
		GUID_t				GetGUID( ){ return m_GUID ; }

		VOID				SetAskType( UINT /*BYTE*/ type ){ m_AskType = type ; }
		UINT /*BYTE*/		GetAskType( ){ return m_AskType ; }

		VOID  SetPageIndex(UINT pageIndex ){ m_PageIndex = pageIndex ; }
		UINT  GetPageIndex(){ return m_PageIndex; }

		VOID  SetPageRowCount(UINT rowCnt) {m_PageRowCount=rowCnt;}
		UINT  GetPageRowCount(){return m_PageRowCount;}

	private:
		//数据
		GUID_t				m_GUID ;
		UINT /*BYTE*/		m_AskType ;// enum ASK_TYPE
		UINT  m_PageIndex;
		UINT  m_PageRowCount;       

	};


	class GWAskMailFactory : public PacketFactory 
	{
	public:
		Packet*		CreatePacket() { return new GWAskMail() ; }
		PacketID_t	GetPacketID()const { return PACKET_GW_ASKMAIL ; }
		UINT		GetPacketMaxSize()const { return sizeof(GUID_t)+
													  sizeof(UINT)*3 ; }
	};


	class GWAskMailHandler 
	{
	public:
          static UINT Execute(GWAskMail* pPacket, Player* pPlayer);
	};
};

using namespace Packets ;

#endif
