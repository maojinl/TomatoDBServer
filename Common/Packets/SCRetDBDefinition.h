#ifndef _SCRETDBDEFINITION_H_
#define _SCRETDBDEFINITION_H_
#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class SCRetDBDefinition : public Packet
	{
	public:
		SCRetDBDefinition() :
			m_OperationType(DB_OPERATION_TYPE_NONE),
			m_DatabaseNameSize(MAX_DATABASE_NAME + 1)
		{
		};

		virtual ~SCRetDBDefinition() {};

		virtual BOOL			Read(SocketInputStream& iStream);
		virtual BOOL			Write(SocketOutputStream& oStream) const;
		virtual UINT			Execute(Player* pPlayer);

		virtual PacketID_t		GetPacketID() const { return PACKET_SC_RETDBDEFINITION; }
		virtual UINT			GetPacketSize() const
		{
			return sizeof(DB_OPERATION_TYPE)
				+ sizeof(ASKDBOPERATION_RESULT)
				+ sizeof(BYTE)
				+ sizeof(CHAR) * m_DatabaseNameSize;
		}

	public:
		const					DB_OPERATION_TYPE GetOperationType() const;
		VOID					SetOperationType(DB_OPERATION_TYPE opType);
		ASKDBOPERATION_RESULT	GetResult() const;
		VOID					SetResult(ASKDBOPERATION_RESULT result);
		VOID					SetDatabaseName(const CHAR* pDBName) {
			Assert(pDBName);
			memset(m_DatabaseName, 0, m_DatabaseNameSize);
			memcpy(m_DatabaseName, pDBName, m_DatabaseNameSize);
			m_DatabaseName[m_DatabaseNameSize] = 0;
		}
		CHAR* GetDatabaseName() { return m_DatabaseName; };

	private:
		DB_OPERATION_TYPE		m_OperationType;
		ASKDBOPERATION_RESULT	Result;
		BYTE					m_DatabaseNameSize;
		CHAR					m_DatabaseName[MAX_DATABASE_NAME + 1];
	};

	class SCRetDBDefinitionFactory : public PacketFactory
	{
	public:
		Packet* CreatePacket() { return new SCRetDBDefinition(); }
		PacketID_t	GetPacketID()const { return PACKET_SC_RETDBDEFINITION; }
		UINT		GetPacketMaxSize() const
		{
			return sizeof(DB_OPERATION_TYPE)
				+ sizeof(ASKDBOPERATION_RESULT)
				+ sizeof(CHAR) * (MAX_DATABASE_NAME + 1);
		}
	};


	class SCRetDBDefinitionHandler
	{
	public:
		static UINT Execute(SCRetDBDefinition* pPacket, Player* pPlayer);
	};
};

using namespace Packets;

#endif