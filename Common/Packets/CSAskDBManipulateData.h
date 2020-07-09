#ifndef __CSASKDBMANIPULATEDATA_H__
#define __CSASKDBMANIPULATEDATA_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class CSAskDBManipulateData : public Packet
	{
	public:
		CSAskDBManipulateData() :
			m_OperationType(DB_OPERATION_TYPE_NONE)
		{
			memset(m_DatabaseName, 0, sizeof(CHAR) * (MAX_DATABASE_NAME + 1));
			memset(m_Key, 0, sizeof(CHAR) * (MAX_DATABASE_KEY + 1));
			memset(m_Value, 0, sizeof(CHAR) * (MAX_DATABASE_VALUE + 1));
		};
		virtual ~CSAskDBManipulateData() {};

		virtual BOOL			Read(SocketInputStream& iStream);
		virtual BOOL			Write(SocketOutputStream& oStream) const;
		virtual UINT			Execute(Player* pPlayer);

		virtual PacketID_t		GetPacketID() const { return PACKET_CS_ASKDBMANIPULATEDATA; }
		virtual UINT			GetPacketSize() const
		{
			return	sizeof(DB_OPERATION_TYPE)
				+ sizeof(CHAR) * (MAX_DATABASE_NAME + 1)
				+ sizeof(CHAR) * (MAX_DATABASE_KEY + 1)
				+ sizeof(CHAR) * (MAX_DATABASE_VALUE + 1);
		}

	public:
		const					DB_OPERATION_TYPE GetOperationType() const;
		VOID					SetOperationType(DB_OPERATION_TYPE opType);
		const					CHAR* GetDatabaseName()	const;
		VOID					SetDatabaseName(CHAR* pDBName);
		const					CHAR* GetDatabaseKey()	const;
		VOID					SetDatabaseKey(CHAR* pKey);
		const					CHAR* GetDatabaseValue()	const;
		VOID					SetDatabaseValue(CHAR* pValue);
	private:
		DB_OPERATION_TYPE		m_OperationType;
		CHAR					m_DatabaseName[MAX_DATABASE_NAME + 1];	//database name
		CHAR					m_Key[MAX_DATABASE_KEY + 1];	//key
		CHAR					m_Value[MAX_DATABASE_VALUE + 1];	//database name
	};

	class CSAskDBManipulateDataFactory : public PacketFactory
	{
	public:
		Packet* CreatePacket() { return new CSAskDBManipulateData(); }
		PacketID_t	GetPacketID()const { return PACKET_CS_ASKDBMANIPULATEDATA; }
		UINT		GetPacketMaxSize() const
		{
			return	sizeof(DB_OPERATION_TYPE)
				+ sizeof(CHAR) * (MAX_DATABASE_NAME + 1)
				+ sizeof(CHAR) * (MAX_DATABASE_KEY + 1)
				+ sizeof(CHAR) * (MAX_DATABASE_VALUE + 1);
		}
	};


	class CSAskDBManipulateDataHandler
	{
	public:
		static UINT Execute(CSAskDBManipulateData* pPacket, Player* pPlayer);
	};

};

using namespace Packets;

#endif