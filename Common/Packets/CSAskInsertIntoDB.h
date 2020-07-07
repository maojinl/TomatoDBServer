#ifndef __CSASKINSERTINTODB_H__
#define __CSASKINSERTINTODB_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class CSAskInsertIntoDB : public Packet
	{
	public:
		CSAskInsertIntoDB() {
			memset(m_DatabaseName, 0, sizeof(CHAR) * (MAX_DATABASE_NAME + 1));

		};
		virtual ~CSAskInsertIntoDB() {};

		//公用继承接口
		virtual BOOL			Read(SocketInputStream& iStream);
		virtual BOOL			Write(SocketOutputStream& oStream) const;
		virtual UINT			Execute(Player* pPlayer);

		virtual PacketID_t		GetPacketID() const { return PACKET_CS_ASKINSERTINTODB; }
		virtual UINT			GetPacketSize() const
		{
			return	sizeof(CHAR) * (MAX_DATABASE_NAME);
		}

	public:
		//使用数据接口
		const					CHAR* GetDatabaseName()	const;
		VOID					SetDatabaseName(CHAR* pAccount);
	private:
		//数据
		CHAR					m_DatabaseName[MAX_DATABASE_NAME + 1];	//database name
	};

	class CSAskInsertIntoDBFactory : public PacketFactory
	{
	public:
		Packet* CreatePacket() { return new CSAskInsertIntoDB(); }
		PacketID_t	GetPacketID()const { return PACKET_CS_ASKINSERTINTODB; }
		UINT		GetPacketMaxSize() const
		{
			return	sizeof(CHAR) * (MAX_DATABASE_NAME + 1);
		}
	};


	class CSAskInsertIntoDBHandler
	{
	public:
		static UINT Execute(CSAskInsertIntoDB* pPacket, Player* pPlayer);
	};

};

using namespace Packets;

#endif