#ifndef _SCRETCREATEDB_H_
#define _SCRETCREATEDB_H_
#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class SCRetCreateDB : public Packet
	{
	public:
		SCRetCreateDB() {};
		virtual ~SCRetCreateDB() {};

		//公用继承接口
		virtual BOOL			Read(SocketInputStream& iStream);
		virtual BOOL			Write(SocketOutputStream& oStream) const;
		virtual UINT			Execute(Player* pPlayer);

		virtual PacketID_t		GetPacketID() const { return PACKET_SC_RETCREATEDB; }
		virtual UINT			GetPacketSize() const
		{
			return	sizeof(ASKCREATEDB_RESULT) +
				sizeof(CHAR) * (MAX_DATABASE_NAME);
		}

	public:
		ASKCREATEDB_RESULT		GetResult() const;
		VOID					SetResult(ASKCREATEDB_RESULT result);
		VOID					SetDatabaseName(const CHAR* szDBName) {
			strncpy(m_DatabaseName, szDBName, MAX_DATABASE_NAME);
			m_DatabaseName[MAX_DATABASE_NAME - 1] = 0;
		}
		CHAR* GetDatabaseName() { return m_DatabaseName; };


	private:
		ASKCREATEDB_RESULT	Result;
		CHAR				m_DatabaseName[MAX_DATABASE_NAME];
	};

	class SCRetCreateDBFactory : public PacketFactory
	{
	public:
		Packet* CreatePacket() { return new SCRetCreateDB(); }
		PacketID_t	GetPacketID()const { return PACKET_SC_RETCREATEDB; }
		UINT		GetPacketMaxSize() const
		{
			return	sizeof(ASKCREATEDB_RESULT) +
				sizeof(CHAR) * (MAX_DATABASE_NAME);
		}
	};


	class SCRetCreateDBHandler
	{
	public:
		static UINT Execute(SCRetCreateDB* pPacket, Player* pPlayer);
	};
};

using namespace Packets;

#endif