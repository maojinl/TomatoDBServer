#ifndef __CGENTERSCENE_H__
#define __CGENTERSCENE_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{

#define ENTER_TYPE_FIRST		(0)	//0 ��¼���һ�ν��볡��
#define ENTER_TYPE_FROM_OTHER	(1)	//1 ����������ת��

class CGEnterScene : public Packet
{
public:
	CGEnterScene( ){} ;
	virtual ~CGEnterScene( ){} ;

	//���ü̳нӿ�
	virtual BOOL			Read( SocketInputStream& iStream ) ;
	virtual BOOL			Write( SocketOutputStream& oStream )const ;
	virtual UINT			Execute( Player* pPlayer ) ;

	virtual PacketID_t		GetPacketID()const { return PACKET_CG_ENTERSCENE ; }
        virtual UINT GetPacketSize() const {
          return sizeof(BYTE) + sizeof(WorkerID_t); }
	
public:
	//ʹ�����ݽӿ�
	VOID			setEnterType(BYTE byEnterType) { m_byEnterType = byEnterType; }
	BYTE			getEnterType(VOID)const { return m_byEnterType; }
	
	VOID			setSceneID(WorkerID_t nSceneID) { m_nSceneID = nSceneID; }
	WorkerID_t		getSceneID(VOID)const { return m_nSceneID; }

private:
	//����
	BYTE			m_byEnterType;	//��������
									//#define ENTER_TYPE_FIRST		(0)	 ��¼���һ�ν��볡��
									//#define ENTER_TYPE_FROM_OTHER	(1)	 ����������ת��
									//...
	WorkerID_t		m_nSceneID;		//����ID
};

class CGEnterSceneFactory : public PacketFactory 
{
public:
	Packet*		CreatePacket() { return new CGEnterScene() ; }
	PacketID_t	GetPacketID()const { return PACKET_CG_ENTERSCENE ; }
        UINT GetPacketMaxSize() const {
          return sizeof(BYTE) + sizeof(WorkerID_t);
										}
};

class CGEnterSceneHandler 
{
public:
	static UINT Execute( CGEnterScene* pPacket, Player* pPlayer ) ;
};

}

using namespace Packets;

#endif