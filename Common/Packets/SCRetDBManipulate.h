#ifndef _SCRETDBMANIPULATE_H_
#define _SCRETDBMANIPULATE_H_
#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class SCRetDBManipulate : public Packet
	{
	public:
		SCRetDBManipulate() {};
		virtual ~SCRetDBManipulate() {};

		virtual BOOL			Read(SocketInputStream& iStream);
		virtual BOOL			Write(SocketOutputStream& oStream) const;
		virtual UINT			Execute(Player* pPlayer);

		virtual PacketID_t		GetPacketID() const { return PACKET_SC_RETDBMANIPULATE; }
		virtual UINT			GetPacketSize() const
		{
			return sizeof(DB_MANIPULATE_TYPE)
				+ sizeof(ASKDBOPERATION_RESULT);
		}

	public:
		const					DB_MANIPULATE_TYPE GetManipulateType() const;
		VOID					SetManipulateType(DB_MANIPULATE_TYPE manType);
		ASKDBOPERATION_RESULT	GetResult() const;
		VOID					SetResult(ASKDBOPERATION_RESULT result);
	private:
		DB_MANIPULATE_TYPE		m_ManipulateType;
		ASKDBOPERATION_RESULT	Result;
	};

	class SCRetDBManipulateFactory : public PacketFactory
	{
	public:
		Packet* CreatePacket() { return new SCRetDBManipulate(); }
		PacketID_t	GetPacketID()const { return PACKET_SC_RETDBMANIPULATE; }
		UINT		GetPacketMaxSize() const
		{
			return sizeof(DB_MANIPULATE_TYPE)
				+ sizeof(ASKDBOPERATION_RESULT);
		}
	};


	class SCRetDBManipulateHandler
	{
	public:
		static UINT Execute(SCRetDBManipulate* pPacket, Player* pPlayer);
	};
};

using namespace Packets;

#endif