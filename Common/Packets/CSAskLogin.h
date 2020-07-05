#ifndef __CSASKLOGIN_H__
#define __CSASKLOGIN_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class CSAskLogin : public Packet
	{
	public:
		CSAskLogin() {
			memset(szPassKey, 0, sizeof(CHAR) * (MAX_ACCOUNT + 1));

		};
		virtual ~CSAskLogin() {};

		//���ü̳нӿ�
		virtual BOOL			Read(SocketInputStream& iStream);
		virtual BOOL			Write(SocketOutputStream& oStream) const;
		virtual UINT			Execute(Player* pPlayer);

		virtual PacketID_t		GetPacketID() const { return PACKET_CS_ASKLOGIN; }
		virtual UINT			GetPacketSize() const
		{
			return	sizeof(CHAR) * (MAX_ACCOUNT + 1) * 2;
		}

	public:
		//ʹ�����ݽӿ�
		const	CHAR* GetAccount()	const;
		VOID					SetAccount(CHAR* pAccount);
		UINT					GetVersion() const;
		VOID					SetVersion(UINT version);

		CHAR* GetPassKey() { return szPassKey; }

	private:
		//����
		CHAR					szAccount[MAX_ACCOUNT + 1];	//�û�����
		CHAR					szPassKey[MAX_ACCOUNT + 1];	//ͨ��֤
		UINT					uVersion;					//�ͻ��˰汾
	};

	class CLAskLoginFactory : public PacketFactory
	{
	public:
		Packet* CreatePacket() { return new CSAskLogin(); }
		PacketID_t	GetPacketID()const { return PACKET_CS_ASKLOGIN; }
		UINT		GetPacketMaxSize() const
		{
			return	sizeof(CHAR) * (MAX_ACCOUNT + 1) * 2;
		}
	};


	class CSAskLoginHandler
	{
	public:
		static UINT Execute(CSAskLogin* pPacket, Player* pPlayer);
	};

};

using namespace Packets;

#endif