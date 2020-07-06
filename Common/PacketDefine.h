﻿#ifndef __PACKET_DEFINE_H__
#define __PACKET_DEFINE_H__


namespace Packets
{
	enum PACKET_DEFINE
	{
		PACKET_NONE = 0,

	/* ID:1 */PACKET_GC_TEST ,
		PACKET_SS_CONNECT,
		PACKET_WG_SYSTEMMSG,							
		PACKET_GW_SYSTEMMSG,
		PACKET_GW_ASKMAIL,
		PACKET_WG_MAIL,
		PACKET_GC_SYSTEMMSG,
		PACKET_CS_ASKLOGIN,								//Ask Login
		PACKET_SC_RETLOGIN,								//Ret Login

		PACKET_CS_ASKCREATEDB,
		PACKET_SC_RETCREATEDB,
		PACKET_MAX
	};
};


#endif

