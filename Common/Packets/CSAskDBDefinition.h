#ifndef __CSASKDBDEFINITION_H__
#define __CSASKDBDEFINITION_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class CSAskDBDefinition : public Packet
	{
	public:
		CSAskDBDefinition() :
			m_OperationType(DB_OPERATION_TYPE_NONE)
		{
			memset(m_DatabaseName, 0, sizeof(CHAR) * (MAX_DATABASE_NAME));
		};
		virtual ~CSAskDBDefinition() {};

		//公用继承接口
		virtual BOOL			Read(SocketInputStream& iStream);
		virtual BOOL			Write(SocketOutputStream& oStream) const;
		virtual UINT			Execute(Player* pPlayer);

		virtual PacketID_t		GetPacketID() const { return PACKET_CS_ASKDBDEFINITION; }
		virtual UINT			GetPacketSize() const
		{
			return	sizeof(DB_OPERATION_TYPE) +
				sizeof(CHAR) * (MAX_DATABASE_NAME + 1);
		}

	public:
		const					DB_OPERATION_TYPE GetOperationType() const;
		VOID					SetOperationType(DB_OPERATION_TYPE opType);
		const					CHAR* GetDatabaseName()	const;
		VOID					SetDatabaseName(CHAR* pDBName);
	private:
		DB_OPERATION_TYPE		m_OperationType;
		CHAR					m_DatabaseName[MAX_DATABASE_NAME + 1];	//database name
	};

	class CSAskDBDefinitionFactory : public PacketFactory
	{
	public:
		Packet* CreatePacket() { return new CSAskDBDefinition(); }
		PacketID_t	GetPacketID()const { return PACKET_CS_ASKDBDEFINITION; }
		UINT		GetPacketMaxSize() const
		{
			return	sizeof(DB_OPERATION_TYPE) +
				sizeof(CHAR) * (MAX_DATABASE_NAME + 1);
		}
	};

	class CSAskDBDefinitionHandler
	{
	public:
		static UINT Execute(CSAskDBDefinition* pPacket, Player* pPlayer);
	};
};

using namespace Packets;

#endif