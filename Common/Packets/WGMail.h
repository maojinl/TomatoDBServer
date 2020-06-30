
/************************************************************************
*  ����ʱ�� 2010.7.23
*  ������:  DGH
*  �ļ���:	WGMail.h
*  ����:	worldת���ʼ���server��
*			ִ�нű�����(ִ�������еĽű��ʼ�)��
*			ʵ����ͨ�ʼ�(ϵͳ�ʼ�)ת��;
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

		//���ü̳нӿ�
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
		//ʹ�����ݽӿ�
		VOID		SetPlayerID( PlayerID_t pid ){ m_PlayerID = pid ; } ;
		PlayerID_t	GetPlayerID( ){ return m_PlayerID ; } ;

		VOID		SetGUID( GUID_t guid ){	m_GUID = guid ; }
		GUID_t		GetGUID( ){ return m_GUID ; }

		VOID  SetPageIndex(UINT index){m_PageIndex = index;}
		UINT  GetPageIndex(){return m_PageIndex;}

		VOID  SetPageRowCount(UINT rowCnt){ m_PageRowCount = rowCnt; }
		UINT  GetPageRowCount(){ return m_PageRowCount; }
	private:
		//����
		PlayerID_t	m_PlayerID ;//�����˵�PlayerID
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
