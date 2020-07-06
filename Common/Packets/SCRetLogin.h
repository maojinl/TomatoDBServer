#ifndef _LCRET_LOGIN_H_
#define _LCRET_LOGIN_H_
#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"


namespace Packets
{


	class SCRetLogin : public Packet 
	{
	public:
		SCRetLogin( ){} ;
		virtual ~SCRetLogin( ){} ;

		//公用继承接口
		virtual BOOL			Read( SocketInputStream& iStream ) ;
		virtual BOOL			Write( SocketOutputStream& oStream ) const ;
		virtual UINT			Execute( Player* pPlayer ) ;

		virtual PacketID_t		GetPacketID() const { return PACKET_SC_RETLOGIN ; }
		virtual UINT			GetPacketSize() const 
		{
			return	sizeof(LOGIN_RESULT) +
				sizeof(CHAR) * MAX_CHARACTER_NAME +
				sizeof(CHAR) * MAX_CHARACTER_TITLE +
				sizeof(UINT);
		}

	public:
		//使用数据接口
		//const	CHAR*			GetAccount()	const;
		//VOID					SetAccount(const CHAR*	pAccount);
		LOGIN_RESULT			GetResult() const;
		VOID					SetResult(LOGIN_RESULT result);
		VOID					SetCharName(const CHAR* szCharName) {
			strncpy(m_CharName, szCharName, MAX_CHARACTER_NAME);
			m_CharName[MAX_CHARACTER_NAME - 1] = 0;
		}
		CHAR*					GetCharName() { return m_CharName; };

		VOID					SetTitleName(const CHAR* szTitleName) {
			strncpy(m_TitleName, szTitleName, MAX_CHARACTER_TITLE);
			m_TitleName[MAX_CHARACTER_TITLE - 1] = 0;
		}
		CHAR* GetTitleName() { return m_TitleName; };

		VOID				SetLevel(UINT iLevel) { m_iLevel = iLevel; }
		UINT				GetLevel() { return m_iLevel; }
	private:
		//数据
		//没有开BillingSystem 前使用客户端自己算GUID
		LOGIN_RESULT			Result;
		//CHAR					szAccount[MAX_ACCOUNT+1];	//用户名称
		CHAR				m_CharName[MAX_CHARACTER_NAME];
		CHAR				m_TitleName[MAX_CHARACTER_TITLE];
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