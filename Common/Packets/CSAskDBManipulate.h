#ifndef __CSASKDBMANIPULATE_H__
#define __CSASKDBMANIPULATE_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class CSAskDBManipulate : public Packet
	{
	public:
		CSAskDBManipulate() :
			m_OperationType(DB_OPERATION_TYPE_NONE),
			m_DatabaseNameSize(MAX_DATABASE_NAME + 1),
			m_KeySize(MAX_DATABASE_KEY + 1),
			m_ValueSize(MAX_DATABASE_VALUE + 1)
		{
		};

		virtual ~CSAskDBManipulate() {};

		virtual BOOL			Read(SocketInputStream& iStream);
		virtual BOOL			Write(SocketOutputStream& oStream) const;
		virtual UINT			Execute(Player* pPlayer);

		virtual PacketID_t		GetPacketID() const { return PACKET_CS_ASKDBMANIPULATE; }
		virtual UINT			GetPacketSize() const
		{
			return	sizeof(DB_OPERATION_TYPE)
				+ sizeof(BYTE)
				+ sizeof(CHAR) * m_DatabaseNameSize
				+ sizeof(BYTE)
				+ sizeof(CHAR) * m_KeySize
				+ sizeof(UINT)
				+ sizeof(CHAR) * m_ValueSize;
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
		BYTE					m_DatabaseNameSize;
		CHAR					m_DatabaseName[MAX_DATABASE_NAME + 1];	//database name
		BYTE					m_KeySize;
		CHAR					m_Key[MAX_DATABASE_KEY + 1];	//key
		UINT					m_ValueSize;
		CHAR					m_Value[MAX_DATABASE_VALUE + 1];	//database name
	};

	class CSAskDBManipulateFactory : public PacketFactory
	{
	public:
		Packet* CreatePacket() { return new CSAskDBManipulate(); }
		PacketID_t	GetPacketID() const { return PACKET_CS_ASKDBMANIPULATE; }
		UINT		GetPacketMaxSize() const
		{
			return	sizeof(DB_OPERATION_TYPE)
				+ sizeof(BYTE)
				+ sizeof(CHAR) * (MAX_DATABASE_NAME + 1)
				+ sizeof(BYTE)
				+ sizeof(CHAR) * (MAX_DATABASE_KEY + 1)
				+ sizeof(UINT)
				+ sizeof(CHAR) * (MAX_DATABASE_VALUE + 1);
		}
	};

	class CSAskDBManipulateHandler
	{
	public:
		static UINT Execute(CSAskDBManipulate* pPacket, Player* pPlayer);
	};

};

using namespace Packets;

#endif