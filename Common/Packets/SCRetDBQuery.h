#ifndef _SCRETDBQUERY_H_
#define _SCRETDBQUERY_H_
#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class SCRetDBQuery : public Packet
	{
	public:
		SCRetDBQuery() :
			m_QueryType(DB_QUERY_TYPE_NONE),
			m_Values()
		{};

		virtual ~SCRetDBQuery() {};

		//公用继承接口
		virtual BOOL			Read(SocketInputStream& iStream);
		virtual BOOL			Write(SocketOutputStream& oStream) const;
		virtual UINT			Execute(Player* pPlayer);

		virtual PacketID_t		GetPacketID() const { return PACKET_SC_RETDBQUERY; }
		virtual UINT			GetPacketSize() const
		{
			UINT sz = sizeof(DB_QUERY_TYPE)
				+ sizeof(ASKDBOPERATION_RESULT)
				+ sizeof(UINT);
			int valueSize = m_Values.size();
			for (int i = 0; i < valueSize; i++)
			{
				sz += sizeof(size_t);
				sz += sizeof(CHAR) * m_Values[i].size();
			}
			return sz;
		}

	public:
		const					DB_QUERY_TYPE GetQueryType() const;
		VOID					SetQueryType(DB_QUERY_TYPE opType);
		ASKDBOPERATION_RESULT	GetResult() const;
		VOID					SetResult(ASKDBOPERATION_RESULT result);
		vector<string>&			GetValues();
		VOID					SetValues(const vector<string>& values);
	private:
		DB_QUERY_TYPE			m_QueryType;
		ASKDBOPERATION_RESULT	Result;
		vector<string>			m_Values;
	};

	class SCRetDBQueryFactory : public PacketFactory
	{
	public:
		Packet* CreatePacket() { return new SCRetDBQuery(); }
		PacketID_t	GetPacketID()const { return PACKET_SC_RETDBQUERY; }
		UINT		GetPacketMaxSize() const
		{
			UINT sz = 0xFFFFFFFF;
			return sz;
		}
	};


	class SCRetDBQueryHandler
	{
	public:
		static UINT Execute(SCRetDBQuery* pPacket, Player* pPlayer);
	};
};

using namespace Packets;

#endif