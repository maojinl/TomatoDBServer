#ifndef __CSASKDBQUERY_H__
#define __CSASKDBQUERY_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class CSAskDBQuery : public Packet
	{
	public:
		CSAskDBQuery() :
			m_QueryType(DB_QUERY_TYPE_NONE),
			m_DatabaseNameSize(MAX_DATABASE_NAME + 1),
			m_KeySize(MAX_DATABASE_KEY + 1)
		{
		};

		virtual ~CSAskDBQuery() {};

		virtual BOOL			Read(SocketInputStream& iStream);
		virtual BOOL			Write(SocketOutputStream& oStream) const;
		virtual UINT			Execute(Player* pPlayer);

		virtual PacketID_t		GetPacketID() const { return PACKET_CS_ASKDBQUERY; }
		virtual UINT			GetPacketSize() const
		{
			return	sizeof(DB_QUERY_TYPE)
				+ sizeof(BYTE)
				+ sizeof(CHAR) * m_DatabaseNameSize
				+ sizeof(BYTE)
				+ sizeof(CHAR) * m_KeySize;
		}

	public:
		const					DB_QUERY_TYPE GetQueryType() const;
		VOID					SetQueryType(DB_QUERY_TYPE qrType);
		const					CHAR* GetDatabaseName()	const;
		VOID					SetDatabaseName(CHAR* pDBName);
		const					CHAR* GetDatabaseKey()	const;
		VOID					SetDatabaseKey(CHAR* pKey);
	private:
		DB_QUERY_TYPE			m_QueryType;
		BYTE					m_DatabaseNameSize;
		CHAR					m_DatabaseName[MAX_DATABASE_NAME + 1];	//database name
		BYTE					m_KeySize;
		CHAR					m_Key[MAX_DATABASE_KEY + 1];	//key
	};

	class CSAskDBQueryFactory : public PacketFactory
	{
	public:
		Packet* CreatePacket() { return new CSAskDBQuery(); }
		PacketID_t	GetPacketID() const { return PACKET_CS_ASKDBQUERY; }
		UINT		GetPacketMaxSize() const
		{
			return	sizeof(DB_OPERATION_TYPE)
				+ sizeof(BYTE)
				+ sizeof(CHAR) * (MAX_DATABASE_NAME + 1)
				+ sizeof(BYTE)
				+ sizeof(CHAR) * (MAX_DATABASE_KEY + 1);
		}
	};

	class CSAskDBQueryHandler
	{
	public:
		static UINT Execute(CSAskDBQuery* pPacket, Player* pPlayer);
	};

};

using namespace Packets;

#endif