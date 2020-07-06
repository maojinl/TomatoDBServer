#ifndef __PACKET_DEFINE_H__
#define __PACKET_DEFINE_H__


namespace Packets
{
	//ÏûÏ¢ÀàÐÍÖµÃèÊö¸ñÊ½£ºPACKET_XX_YYYYYY
	//XX¿ÉÒÔÃèÊöÎª£ºGC¡¢CG¡¢CL¡¢LC¡¢GL¡¢LG
	//GÓÎÏ··þÎñÆ÷¶Ë¡¢C¿Í»§¶Ë¡¢LµÇÂ½·þÎñÆ÷¶Ë¡¢S·þÎñÆ÷¶Ë³ÌÐò£¨¿ÉÒÔÊÇµÇÂ½£¬Ò²¿ÉÒÔÊÇÓÎÏ·£©
	//YYYYYY±íÊ¾ÏûÏ¢ÄÚÈÝ
	//ÀýÈç£ºPACKET_CG_ATTACK ±íÊ¾¿Í»§¶Ë·¢¸øÓÎÏ··þÎñÆ÷¶Ë¹ØÓÚ¹¥»÷µÄÏûÏ¢
	enum PACKET_DEFINE
	{
		PACKET_NONE = 0 ,						//0£¬¿Õ

	/* ID:1 */PACKET_GC_TEST ,
		PACKET_SS_CONNECT,
		PACKET_WG_SYSTEMMSG,								//WorldÏòServer·¢ËÍÏµÍ³ÏûÏ¢
		PACKET_GW_SYSTEMMSG,										//ServerÏòWorld·¢ËÍÏµÍ³ÏûÏ
		PACKET_GW_ASKMAIL,
		PACKET_WG_MAIL,
		PACKET_GC_SYSTEMMSG,
		PACKET_CS_ASKLOGIN,								//Ask Login
		PACKET_SC_RETLOGIN,								//Ret Login

		PACKET_MAX
	};
};


#endif

