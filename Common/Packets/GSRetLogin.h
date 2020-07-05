#ifndef __GCENTERSCENE_H__
#define __GCENTERSCENE_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{

class GCEnterScene : public Packet
{
public:
	GCEnterScene( )
	{
		m_byRet			= 0;
	}
	virtual ~GCEnterScene( ){} ;

	//���ü̳нӿ�
	virtual BOOL			Read( SocketInputStream& iStream ) ;
	virtual BOOL			Write( SocketOutputStream& oStream )const ;
	virtual UINT			Execute( Player* pPlayer ) ;

	virtual PacketID_t		GetPacketID()const { return PACKET_GC_ENTERSCENE ; }
	virtual UINT			GetPacketSize()const { return	sizeof (UINT) +
															sizeof(WorkerID_t)+ 
															sizeof(CHAR)*MAX_CHARACTER_NAME +
															sizeof(UINT) +
															sizeof(UINT) +
                                                            sizeof(CHAR)*MAX_CHARACTER_TITLE +
															sizeof(UINT) +
															sizeof(UINT)
															;} 
	
public:
	//ʹ�����ݽӿ�
	
	inline VOID			setReturn(BYTE byReturn)		{ m_byRet = byReturn; }
	inline BYTE			getReturn(VOID)const			{ return m_byRet; }

	inline VOID			setSceneID(WorkerID_t nSceneID)	{m_nSceneID = nSceneID; }
	inline WorkerID_t	getSceneID(VOID)const			{ return m_nSceneID; }

	VOID				setCharName( const CHAR* szCharName ){ 
							strncpy( m_CharName, szCharName, MAX_CHARACTER_NAME ) ;
							m_CharName[MAX_CHARACTER_NAME] = 0 ;
						}
	CHAR*				getCharName( ){ return m_CharName ; } ;

	VOID				setTitleName( const CHAR* szTitleName ){ 
							strncpy( m_TitleName, szTitleName, MAX_CHARACTER_TITLE ) ;
							m_TitleName[MAX_CHARACTER_TITLE] = 0 ;
						}
	CHAR*				getTitleName( ){ return m_TitleName ; } ;

	VOID				setSex( UINT sex ){ m_iSex = sex ; } ;
	UINT				getSex( ){ return m_iSex ; } ;

	VOID				setIcon( UINT Icon ){ m_iIcon = Icon; }
	UINT				getIcon( ){ return m_iIcon; }

	VOID				setSceneID( UINT iSceneID ){ m_iSceneID = iSceneID; }
	UINT				getSceneID( ){ return m_iSceneID; }

	VOID				setLevel( UINT iLevel ){ m_iLevel = iLevel; }
	UINT				getLevel( ){ return m_iLevel; }


private:
	//����
	BYTE				m_byRet;		//���������ؽ��
										//	0 - ȷ�Ͽ��Խ���ó���
										//  1 - ���û�н���ó��������
										//  2 - �Ƿ��ĳ���ID
										//  3 - ���������Ѿ�����
										//  ....
	WorkerID_t			m_nSceneID;		//����ID

	CHAR				m_CharName[MAX_CHARACTER_NAME];
	UINT				m_iSex;
	UINT				m_iIcon;
	CHAR				m_TitleName[MAX_CHARACTER_TITLE];
	UINT				m_iSceneID;
	UINT				m_iLevel;
};

//// To Try ...
//#define DECLEAR_FACTORY( PacketName, PacketID, PacketSize) \
//class PacketName##Factory : public PacketFactory \
//{ \
//public:\
//	Packet*		CreatePacket() { return new PacketName() ; } \
//	PacketID_t	GetPacketID()const { return Packet::PacketID ; } \
//	UINT		GetPacketMaxSize()const { return PacketSize; } \
//}; 
//
//DECLEAR_FACTORY( GCEnterScene, PACKET_GC_ENTERSCENE, (sizeof(UINT)+ sizeof(WorkerID_t)+2*sizeof(Coord_t)) );


class GCEnterSceneFactory : public PacketFactory 
{
public:
	Packet*		CreatePacket() { return new GCEnterScene() ; }
	PacketID_t	GetPacketID()const { return PACKET_GC_ENTERSCENE ; }
												
	UINT		GetPacketMaxSize()const { return	sizeof (UINT) +
															sizeof(BYTE)+ 
															sizeof(WorkerID_t)+ 
															sizeof(CHAR)*MAX_CHARACTER_NAME +
															sizeof(UINT) +
															sizeof(UINT) +
                                                            sizeof(CHAR)*MAX_CHARACTER_TITLE +
															sizeof(UINT) +
															sizeof(UINT)
															;} 
};

class GCEnterSceneHandler 
{
public:
  static UINT Execute(GCEnterScene* pPacket, Player* pPlayer);
};

}

using namespace Packets;

#endif