#ifndef _SCRETLOGIN_H_
#define _SCRETLOGIN_H_
#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"


namespace Packets
{
	class SCRetLogin : public Packet 
	{
	public:
		SCRetLogin( ) {};
		virtual ~SCRetLogin( ) {};

		virtual BOOL			Read( SocketInputStream& iStream );
		virtual BOOL			Write( SocketOutputStream& oStream ) const;
		virtual UINT			Execute( Player* pPlayer );

		virtual PacketID_t		GetPacketID() const { return PACKET_SC_RETLOGIN; }
		virtual UINT			GetPacketSize() const 
		{
			return	sizeof(LOGIN_RESULT)
				+ sizeof(CHAR) * (MAX_CHARACTER_NAME + 1)
				+ sizeof(CHAR) * (MAX_CHARACTER_TITLE + 1)
				+ sizeof(UINT);
		}

	public:
		LOGIN_RESULT			GetResult() const;
		VOID					SetResult(LOGIN_RESULT result);
		VOID					SetCharName(const CHAR* szCharName) {
			strncpy(m_CharName, szCharName, MAX_CHARACTER_NAME);
			m_CharName[MAX_CHARACTER_NAME] = 0;
		}
		CHAR*					GetCharName() { return m_CharName; };

		VOID					SetTitleName(const CHAR* szTitleName) {
			strncpy(m_TitleName, szTitleName, MAX_CHARACTER_TITLE);
			m_TitleName[MAX_CHARACTER_TITLE] = 0;
		}
		CHAR* GetTitleName() { return m_TitleName; };

		VOID				SetLevel(UINT iLevel) { m_iLevel = iLevel; }
		UINT				GetLevel() { return m_iLevel; }
	private:
		LOGIN_RESULT			Result;
		CHAR				m_CharName[MAX_CHARACTER_NAME + 1];
		CHAR				m_TitleName[MAX_CHARACTER_TITLE + 1];
		UINT				m_iLevel;
	};

	class SCRetLoginFactory : public PacketFactory 
	{
	public:
		Packet*		CreatePacket() { return new SCRetLogin() ; }
		PacketID_t	GetPacketID()const { return PACKET_SC_RETLOGIN ; }
		UINT		GetPacketMaxSize() const
		{
			return	sizeof(LOGIN_RESULT) +
				sizeof(CHAR) * MAX_CHARACTER_NAME +
				sizeof(CHAR) * MAX_CHARACTER_TITLE +
				sizeof(UINT);
		}
	};

	class SCRetLoginHandler 
	{
	public:
		static UINT Execute(SCRetLogin* pPacket, Player* pPlayer ) ;
	};
};

using namespace Packets ;

#endif