#ifndef __CSASKCREATEDB_H__
#define __CSASKCREATEDB_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class CSAskCreateDB : public Packet
	{
	public:
		CSAskCreateDB() {
			memset(m_DatabaseName, 0, sizeof(CHAR) * (MAX_DATABASE_NAME));

		};
		virtual ~CSAskCreateDB() {};

		//���ü̳нӿ�
		virtual BOOL			Read(SocketInputStream& iStream);
		virtual BOOL			Write(SocketOutputStream& oStream) const;
		virtual UINT			Execute(Player* pPlayer);

		virtual PacketID_t		GetPacketID() const { return PACKET_CS_ASKCREATEDB; }
		virtual UINT			GetPacketSize() const
		{
			return	sizeof(CHAR) * (MAX_DATABASE_NAME);
		}

	public:
		//ʹ�����ݽӿ�
		const					CHAR* GetDatabaseName()	const;
		VOID					SetDatabaseName(CHAR* pAccount);
	private:
		//����
		CHAR					m_DatabaseName[MAX_DATABASE_NAME];	//database name
	};

	class CSAskCreateDBFactory : public PacketFactory
	{
	public:
		Packet* CreatePacket() { return new CSAskCreateDB(); }
		PacketID_t	GetPacketID()const { return PACKET_CS_ASKCREATEDB; }
		UINT		GetPacketMaxSize() const
		{
			return	sizeof(CHAR) * (MAX_DATABASE_NAME);
		}
	};


	class CSAskCreateDBHandler
	{
	public:
		static UINT Execute(CSAskCreateDB* pPacket, Player* pPlayer);
	};

};

using namespace Packets;

#endif