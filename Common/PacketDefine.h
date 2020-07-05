#ifndef __PACKET_DEFINE_H__
#define __PACKET_DEFINE_H__


namespace Packets
{
	//��Ϣ����ֵ������ʽ��PACKET_XX_YYYYYY
	//XX��������Ϊ��GC��CG��CL��LC��GL��LG
	//G��Ϸ�������ˡ�C�ͻ��ˡ�L��½�������ˡ�S�������˳��򣨿����ǵ�½��Ҳ��������Ϸ��
	//YYYYYY��ʾ��Ϣ����
	//���磺PACKET_CG_ATTACK ��ʾ�ͻ��˷�����Ϸ�������˹��ڹ�������Ϣ
	enum PACKET_DEFINE
	{
		PACKET_NONE = 0 ,						//0����

	/* ID:1 */PACKET_GC_TEST ,

		PACKET_GC_LEAVESCENE ,										//���������������ͻ���ĳ����뿪����Ϣ

		PACKET_GC_NEWITEM,											//���µĶ�����Ʒ�������Լ�����Ұ��Χ
		PACKET_GC_NEWITEMBOX,
		PACKET_GC_NEWMONSTER,										//���µĹ�������Լ�����Ұ��Χ
		PACKET_GC_NEWMONSTER_DEATH,									//����������OBJ
		PACKET_GC_NEWMONSTER_MOVE,									//�����ƶ���OBJ
	/* ID:10 */
		PACKET_GC_NEWPLAYER_DEATH,									//����������PLAYER
		PACKET_GC_NEWPLAYER_MOVE,									//�����ƶ���PLAYER
		PACKET_GC_PLAYERREALMOVE,									//����
		PACKET_GC_MONSTERREALMOVE,									//����

		PACKET_GC_CHAREQUIPMENT,									//ˢ�½�ɫ��װ����
		PACKET_GC_DIE ,
		PACKET_GC_LEVEUP,
		PACKET_GC_LEVELUPRESULT,									//�����������
	/* ID:20 */PACKET_GC_MANUALATTRRESULT,							//����������
		PACKET_GC_RESETATTRRESULT,									//ϴ����
		PACKET_GC_MYEQUIPMENT,										//����
		PACKET_GC_OTHEREQUIPMENT,									//����
		PACKET_GC_DETAILATTRIB ,									//ˢ�µ�ǰ��������
		PACKET_GC_DETAILEQUIPMENTLIST,								//ˢ�µ�ǰ����װ���б�
		PACKET_GC_DETAILSKILLLIST,									//ˢ�µ�ǰ���Ǽ����б�
		PACKET_GC_DETAILSUBEFFECTLIST,								//ˢ�µ�ǰ���Ǹ��������б�
		PACKET_GC_MYBAGLIST,										//ˢ�����Ǳ���
		PACKET_GC_CHARIDLE,											//֪ͨCLIENT����IDLE״̬
	/* ID:30 */PACKET_GC_CHARJUMP,									//֪ͨCLIENT��Ծһ��

		PACKET_GC_MOVE ,											//����
		PACKET_GC_ARRIVE ,											//����
		PACKET_GC_CHARSKILL_CREATEBULLET,							//�����ӵ�
		PACKET_GC_CHARSKILL_EFFECT,									//��������Ч��(�˺�)
		PACKET_GC_CHARSKILL_GATHER,									//���ܾ���
		PACKET_GC_CHARSKILL_GATHER_MODIFY,							//���ܾ���ʱ����ӳ��ȵ�
		PACKET_GC_CHARSKILL_LEAD,									//��������
		PACKET_GC_CHARSKILL_LEAD_MODIFY,							//��������ʱ������̵ȵ�
	/* ID:40 */PACKET_GC_CHARSKILL_SEND,							//���ܷ���
		PACKET_GC_ATTACK ,											//����
		PACKET_GC_OTHERATTACK ,										//����
		PACKET_GC_ERRORATTACK ,										//����
		PACKET_GC_SKILL ,											//����
		PACKET_GC_OTHERSKILL ,										//����
		PACKET_GC_ERRORSKILL ,										//����
		PACKET_GC_SKILLPREPARE ,									//����
		PACKET_GC_USEITEMRESULT,									//ʹ�õ��߽��
		PACKET_GC_BOXITEMLIST,										//Obj_ItemBox ��Ʒ�б�
	/* ID:50 */PACKET_GC_PICKRESULT,								//��ȡ���
		PACKET_GC_USEEQUIPRESULT,									//װ��װ�����

		PACKET_GC_UNEQUIPRESULT,									//ж��װ�����
		PACKET_GC_DISCARDITEMRESULT,								//������Ʒ���

		PACKET_GC_CHAT,												//˵��

		PACKET_GC_ITEMINFO,											//����������ĳ��װ������ϸ��Ϣ
		PACKET_GC_DETAILEQUIPLIST,									//��������������װ����ϸ��Ϣ
	/* ID:60 */PACKET_GC_NEWPORTAL,									//��һ�����͵���Կ�����
		PACKET_GC_DETAILXINFALIST,									//ˢ�µ�ǰ�����ķ��б�
		PACKET_GC_DISCARDEQUIPRESULT,								//������Ʒ���
		PACKET_GC_NOTIFYEQUIP,										//֪ͨ�ͻ��˰����������װ����
		PACKET_GC_NEWSKILLOBJ,										//����SkillObj����Ϣ
		PACKET_GC_USEGEMRESULT,										//ʹ�ñ�ʯ���
		PACKET_GC_REMOVEGEMRESULT,									//ж�ر�ʯ���
		PACKET_GC_CHARIMPACT,										//��ɫ����Ч��
		PACKET_GC_OPERATE_RESULT,									//�����ķ���
		PACKET_GC_USEEQUIPSKILL_RESULT,
	/* ID:70 */PACKET_GC_TEAMERROR,									//
		PACKET_GC_TEAMASKINVITE,									//
		PACKET_GC_TEAMLEADERASKINVITE,								//
		PACKET_GC_TEAMRESULT,										//
		PACKET_GC_TEAMASKAPPLY,										//
		PACKET_GC_ABILITY_RESULT,									//����ܵĲ������ؽ��
		PACKET_GC_DETAILABILITYINFO,								//�������˷�������������Ϣ
		PACKET_GC_COOLDOWN_UPDATE,									//��ȴʱ�����
		PACKET_GC_ABILITY_ACTION,									//����ܵĲ�������
	/* ID:80 */PACKET_GC_ABILITY_SUCC,								//����ܵĳɹ���Ϣ
		PACKET_GC_NOTIFYTEAMINFO ,									//֪ͨ�ͻ���,��������Ϣ�仯
		PACKET_GC_MISSIONLIST ,										//���������б�
		PACKET_GC_MISSIONADD ,										//����һ������
		PACKET_GC_MISSIONREMOVE ,									//ɾ��һ������
		PACKET_GC_MISSIONMODIFY ,									//����һ���������
		PACKET_GC_CHANNELERROR ,									//
		PACKET_GC_CHANNELRESULT ,									//
		//PACKET_GC_MAIL ,											//
		//PACKET_GC_NOTIFYMAIL ,										//
	/* ID:90 */PACKET_GC_NEWPLATFORM,								//��������̨����Ϣ
		PACKET_GC_ABILITYLEVEL,										//�������Ϣ
		PACKET_GC_ABILITYEXP,										//�������������Ϣ
		PACKET_GC_PRESCRIPTION,										//������䷽��Ϣ
		PACKET_GC_ABANDON_ABILITY,									//���������
		PACKET_GC_ITEMBOXCHANGESTAGE,								//Obj_ItemBox�ı����
		PACKET_GC_CANPICKMISSIONITEMLIST,							//����ʰȡ��������Ʒ�б�
		PACKET_GC_ADDCANPICKMISSIONITEM,							//���һ������ʰȡ��������Ʒ
		PACKET_GC_REMOVECANPICKMISSIONITEM,							//ɾ��һ������ʰȡ��������Ʒ
		PACKET_GC_MODIFYSPEED,										//�����ٶȸı�
	/* ID:100 */PACKET_GC_MONSTERSPEAK,								//��������˵��
		PACKET_GC_TEAMMEMBERINFO,									//���ض�����Ϣ
		PACKET_GC_LOCK_TARGET,										//�������Ŀ��
		PACKET_GC_SHOPMERCHANDISELIST,								//��Ʒ�б�	
		PACKET_GC_SHOPSOLDLIST,										//�ع���Ʒ�б�
		PACKET_GC_SHOPUPDATEMERCHANDISELIST,						//������Ʒ�б�
		PACKET_GC_SHOPBUY,											//֪ͨ�ͻ������Ƿ�ɹ�
		PACKET_GC_SHOPSELL,											//֪ͨ�ͻ������Ƿ�ɹ�
		PACKET_GC_SHOPREPAIR,										//֪ͨ������������Ʒ
		PACKET_GC_MENPAIINFO,										//������Ϣ��ID��
	/* ID:110 */PACKET_GC_JOINMENPAI,								//�������ɵĽ��
		PACKET_GC_XINFASTUDYINFO,									//����ѧϰ���ķ�������������Ϣ
		PACKET_GC_STUDYXINFA_H,										//ѧϰ�Ľ��
		PACKET_GC_ABILITY_STUDYINFO,								//ѧϰ����ܵ���Ϣ
		PACKET_GC_CHARALLTITLES,									//������֪ͨ�ͻ��˴������еĳƺ�
		PACKET_GC_ACTIVETIME_UPDATE,								//����
		PACKET_GC_OBJ_TELEPORT,										//��ɫ˲��
		PACKET_GC_BANKBEGIN,										//֪ͨ�ͻ��˿�ʼ������
		
		
	/* ID:120 */PACKET_GC_BANKREMOVEITEM,							//֪ͨ�ͻ����Ƴ���Ʒ���
		PACKET_GC_BANKSWAPITEM,										//֪ͨ�ͻ��˴��������뱳����װ�����н�����Ʒ�Ľ��
		
		PACKET_GC_DETAILATTRIB_PET,									//�������ϸ����
		PACKET_GC_EXCHANGEERROR,									//���׳���
		PACKET_GC_EXCHANGEAPPLYI,									//���뽻��
		PACKET_GC_EXCHANGEESTABLISHI,								//����ȷ��
		PACKET_GC_EXCHANGESYNCHLOCK,								//����ͬ����
		PACKET_GC_EXCHANGESYNCHCONFIRMII,							//����ͬ��ȷ��
		PACKET_GC_EXCHANGESYNCHII,									//����ͬ��
	/* ID:130 */PACKET_GC_EXCHANGESUCCESSIII,						//���׳ɹ���Ϣ
		PACKET_GC_EXCHANGECANCEL,									//����ȡ��
		PACKET_GC_PLAYER_DIE,										//��������
		PACKET_GC_PLAYER_RELIVE,									//���Ǹ���
		PACKET_GC_MANIPULATEPETRET,									//�����������ķ��ؽ��
		PACKET_GC_ASK_TEAMFOLLOW,									//����Ա���ͽ�����Ӹ�������
		PACKET_GC_RETURN_TEAMFOLLOW,								//���ͻ��˷�����Ӹ���״̬
		PACKET_GC_TEAMFOLLOW_LIST,									//��Ӹ����б�
		PACKET_GC_TEAMFOLLOW_ERROR,									//��Ӹ����µĴ�����Ϣ
		PACKET_GC_MISSIONRESULT,									//����������
	/* ID:140 */PACKET_GC_CHAR_DIRECT_IMPACT, 						//Ч��:һ����Ч��
		PACKET_GC_CHAR_BUFF, 										//Ч��: ������Ч��
		PACKET_GC_DETAIL_BUFF,										//Ч��: ������Ч������ϸ����.��������,ֻ�����Լ�
		PACKET_GC_CHARSKILL_MISSED,									//����: ����û������
		PACKET_GC_CHAR_IMPACT_LIST_UPDATE,							//����Ч���б�(��Ҫ��Ϣ���㲥��)
		PACKET_GC_DETAIL_IMPACT_LIST_UPDATE,						//����Ч���б�(��ϸ��Ϣ��ֻ������Լ���)
		PACKET_GC_DETAIL_HEALS_AND_DAMAGES, 						//HP,MP,Rage,Strike Point�ı仯�����ͻ�����ʾ�˺���������
		PACKET_GC_TARGET_LIST_AND_HIT_FLAGS,						//Ŀ���б�ͻ���������ڿͻ�����ʾ�ӵ��ͻ������
		PACKET_GC_PACKAGE_SWAPITEM,									//�����������������Ʒ�Ľ��
		PACKET_GC_STALLAPPLY,										//������֪ͨ�ͻ��������ڴ˴���̯
	/* ID:150 */PACKET_GC_STALLESTABLISH,							//֪ͨ�ͻ����ڴ˴���̯
		PACKET_GC_STALLOPEN,										//̯λ��Ʒ�б�̯λ��Ϣ
		PACKET_GC_STALLADDITEM,										//���߿ͻ�����̯λ�м���Ʒ
		PACKET_GC_STALLREMOVEITEM,									//֪ͨ�ͻ�����̯λ���ó���Ʒ
		PACKET_GC_STALLITEMPRICE,									//֪ͨ��������̯λ�е���Ʒ�ı��ۼ�
		PACKET_GC_STALLBUY,											//֪ͨ�ͻ��˹��������Ʒ
		PACKET_GC_STALLCLOSE,										//֪ͨ�ͻ����Լ��رյ���
		PACKET_GC_STALLERROR,										//֪ͨ��̯����
		PACKET_GC_BBSMESSAGES,										//���԰����
		PACKET_GC_RELATION,											//��Ϸ��������ͻ��˷��ͺ��������Ϣ
	/* ID:160 */PACKET_GC_GUILD,									//�����Ϣ
		PACKET_GC_GUILDLIST,										//���ذ���б�(UCHAR, {GuildID_t,NAME,Level,UserCount,Status})
		PACKET_GC_GUILDERROR,										//���ذ���������(enum)
		PACKET_GC_GUILDRETURN,										//���ذ��������(enum)
		PACKET_GC_GUILDBASEINFO,									//��������Ϣ
		PACKET_GC_GUILDMEMBERS,										//������Ϣ
		PACKET_GC_GUILDAUTHORITY,									//���Ȩ�ޱ�
		PACKET_GC_ITEMSYNCH,										//��Ʒ�ƶ���Ϣ
		PACKET_GC_ITEMLIST,											//������Ʒ�б���ͻ���
		PACKET_GC_TEAM_LIST,										//���ض�Ա�б�
	/* ID:170 */PACKET_GC_NEWSPECIAL,								//����һ��SpecialObj���ͻ���
		PACKET_GC_UICOMMAND,										//���Ϳͻ��˵�ĳ���û��ӿ�����
		PACKET_GC_SPLITITEMRESULT,									//�����Ʒ
		
		PACKET_GC_SPECIAL_OBJ_ACT_NOW,								//���������ʾ��Ч����
		PACKET_GC_SPECIAL_OBJ_FADE_OUT,								//����������������
		PACKET_GC_PLAYERSHOPERROR,									//����̵�ĳ�����Ϣ
		PACKET_GC_PLAYERSHOPAPPLY,									//������֪ͨ�ͻ��˴�������̵�������ж���Ϣ
		PACKET_GC_PLAYERSHOPESTABLISH,								//����̵��Ƿ����ɹ�
		PACKET_GC_PLAYERSHOPACQUIRESHOPLIST,						//������֪ͨ�ͻ��˴�������̵�������ж���Ϣ
	/* ID:180 */PACKET_GC_PACKUP_PACKET,							//�����������Ľ��
		PACKET_GC_PLAYERSHOPONSALE,									//֪ͨ�ͻ�����Ʒ���¼�
		PACKET_GC_PLAYERSHOPMONEY,									//֪ͨ�ͻ��˽�Ǯ��ȡ

		PACKET_GC_PLAYERSHOPOPENSTALL,								//���Ż�رչ�̨
		PACKET_GC_REMOVEPET,										//�޸��û���������
		PACKET_GC_PETPLACARDLIST,									//���﹫�������
		PACKET_GC_CITYERROR,										//�ͻ��˵ĳ��д�����Ϣ
		PACKET_GC_CITYNOTIFY,										//�ͻ��˵ĳ���֪ͨ
		PACKET_GC_CITYATTR,											//server�ѳ�������ˢ���ͻ���
	/* ID:190 */PACKET_GC_NEWPET,									//���µĳ�������Լ�����Ұ��Χ
		PACKET_GC_NEWPET_DEATH,										//���������ĳ���
		PACKET_GC_NEWPET_MOVE,										//�����ƶ��ĳ���
		PACKET_GC_MINORPASSWD,										//��������

		PACKET_GC_PLAYERSHOPSALEOUT,								//�̳��̵�
		PACKET_GC_PLAYERSHOPBUYSHOP,								//����˵�
		PACKET_GC_CHARSTOPACTION,									//ֹͣAction�߼�
		PACKET_GC_GUILDAPPLY,										//���뽨������
		PACKET_GC_PRIVATEINFO,										//������ϣ�ˢ���ͻ��ˣ�
	/* ID:200 */PACKET_GC_WORLDTIME,								//Server->Client ˢ������ʱ��
		PACKET_GC_CHARACTION,										//��һ������
		PACKET_GC_CHARMODIFYACTION,									//���Ŷ�����ִ��
		PACKET_GC_PLAYER_CALLOF,									//����ȥĳ��
		PACKET_GC_FINGER,											//�������
		PACKET_GC_PLAYERSHOPRECORDLIST,								//��¼�б�
		PACKET_GC_PLAYERSHOPUPDATEPARTNERS,							//���ºϻ����б�
		PACKET_GC_PLAYERSHOPUPDATEFAVORITE,							//�����µ��ղؼ�����ˢ���̵��б�
		PACKET_GC_PLAYERSHOPTYPE,									//֪ͨ�ͻ��˸ı��̵�����
		PACKET_GC_PLAYERSHOPSTALLSTATUS,							//�����������ı�ĳ����̨״̬
	/* ID:210 */PACKET_GC_CHARDOACTION,								//��ĳ��ɫ��һ��ָ������
		PACKET_GC_ADDLOCKOBJ,										//�����������뱣���Ľ��
		PACKET_GC_NOTIFYRMB,										// 
		PACKET_GC_MISSIONDESC,										//������������
		PACKET_GC_FIRSTLOGIN,										//��ҵ�һ�ε�¼
		PACKET_GC_SYSTEMMSG,										//Server��Client����ϵͳ��Ϣ
		PACKET_GC_MAXCOUNT,											//����GC���ĸ���
/*------------------------GC-------------------------------------------------------------------------------------------*/

/*------------------------LC-------------------------------------------------------------------------------------------*/
		aaPACKET_LC_RETLOGIN = 400,									//Login ���ؿͻ��˵�������
	/* ID:401*/PACKET_LC_RETCHARLIST,								//���ؽ�ɫ�б�
		PACKET_LC_STATUS,											//���ؿͻ��˵��Ŷ�״̬

		PACKET_LC_RETCONNECT,										//Login����Client����������
		PACKET_LC_MAXCOUNT,											//����LC���ĸ���
/*------------------------LC-------------------------------------------------------------------------------------------*/

/*------------------------CL-------------------------------------------------------------------------------------------*/
		aaaPACKET_CL_ASKLOGIN = 450,									//�ͻ�������Login��¼
	/* ID:451*/PACKET_CL_ASKCHARLIST,								//�����ɫ�б�

		PACKET_CL_CONNECT,											//Client����Login����
/*------------------------CL-------------------------------------------------------------------------------------------*/

/*------------------------CG��GW��WG��SS��LB��BL��LW��WL---------------------------------------------------------------*/
		PACKET_CG_TEST = 500,
	/* ID:501 */
		PACKET_CG_HEARTBEAT ,										//������Ϣ

		PACKET_CG_LEAVESCENE ,										//�ͻ�����ͼ�뿪ĳ������ʱ������������������Ϣ
		PACKET_CG_ENVREQUEST ,										//�ͻ������������������Χ������Ϣ

		PACKET_CG_CHARASKEQUIPMENT,									//��ȡ��װ����
		PACKET_CG_REQLEVELUP,										//��������
		PACKET_CG_REQMANUALATTR,									//�����������
		PACKET_CG_REQRESETATTR,										//ϴ������
	/* ID:511 */PACKET_CG_MYEQUIPMENT,								//����
		PACKET_CG_OTHEREQUIPMENT,									//����
		PACKET_CG_ASKDETAILATTRIB ,									//������µ�ǰ��������
		PACKET_CG_ASKDETAILEQUIPMENTLIST,							//������µ�ǰ����װ���б�
		PACKET_CG_ASKDETAILSKILLLIST,								//������µ�ǰ���Ǽ����б�
		PACKET_CG_ASKDETAILSUBEFFECTLIST,							//������µ�ǰ���Ǹ��������б�
		PACKET_CG_ASKMYBAGLIST,										//����ˢ�µ�ǰ����
		PACKET_CG_CHARIDLE,											//֪ͨSERVER����IDLE״̬
		PACKET_CG_CHARJUMP,											//֪ͨSERVER��Ծһ��

	/* ID:521 */PACKET_CG_MOVE ,									//����
		PACKET_CG_CHARUSESKILL,										//֪ͨSERVERʹ�ü���
		PACKET_CG_ATTACK ,											//����
		PACKET_CG_SKILL ,											//����
		PACKET_CG_OPENITEMBOX,										//��Obj_ItemBox
		PACKET_CG_PICKBOXITEM,										//��ȡObj_ItemBox���һ����Ʒ
		PACKET_CG_USEEQUIP,											//װ��������װ��
		PACKET_CG_UNEQUIP,											//ж��װ��
		PACKET_CG_USEITEM,											//ʹ�õ���
		PACKET_CG_DISCARDITEM,										//�������������Ʒ
	/* ID:531 */PACKET_CG_DISCARDEQUIP,								//��������װ��
		PACKET_SS_CONNECT ,											//������֮����������ʱ��ĵ�һ��֪ͨ��Ϣ
		PACKET_GS_ASKDATA ,											//��Դ�������˳���Ҫ��õ�Player����
		PACKET_SG_RETDATA ,											//��GameServer�˳������û�����
		PACKET_GW_ASKUSERDATA ,										//���������ݷ�����Ҫ���û�����
		PACKET_WG_RETUSERDATA ,										//�����û�������Ϣ
		PACKET_GW_ASKCHANGESCENE ,									//���������ݷ����������û����ϣ�Ҫ��ת�Ƴ���
		PACKET_WG_RETCHANGESCENE ,									//����ת�Ƴ��������Ϣ
		PACKET_GW_NOTIFYUSER ,										//��Ϸ������֪ͨ����������û�״̬��Ҫ�ı�
		PACKET_WG_NOTIFYUSER ,										//���������֪ͨ��Ϸ�������û�״̬�仯
	/* ID:541 */PACKET_CG_COMMAND ,									//�ͻ����������������Ϸ�޸�ָ��

		PACKET_CG_ASKITEMINFO,										//����ĳ����Ʒ����ϸ��Ϣ
		PACKET_CG_ASKDETAILEQUIPLIST,								//��������װ������ϸ��Ϣ
		PACKET_CG_CHAT,												//˵��
		PACKET_CG_ASKDETAILXINFALIST,								//������µ�ǰ�����ķ��б�
		PACKET_CG_USEGEM,											//ʹ�ñ�ʯ
		PACKET_CG_REMOVEGEM,										//ж�ر�ʯ
		PACKET_CG_USEEQUIPSKILL,							
	/* ID:551 */PACKET_CG_USEABILITY,								//���䷽�������ָ��
		PACKET_CG_TEAMINVITE,										//�������
		PACKET_GW_TEAMINVITE,										//
		PACKET_WG_TEAMERROR,										//
		PACKET_WG_TEAMRESULT,										//
		PACKET_WG_NOTIFYTEAMINFO,									//
		PACKET_WG_TEAMASKINVITE,									//
		PACKET_CG_TEAMRETINVITE,									//��ӻ�Ӧ
		PACKET_GW_TEAMRETINVITE,									//
		PACKET_WG_TEAMLEADERASKINVITE,								//
	/* ID:561 */PACKET_CG_TEAMLEADERRETINVITE,						//�ӳ���Ӧ
		PACKET_GW_TEAMLEADERRETINVITE,								//
		PACKET_CG_TEAMLEAVE,										//���
		PACKET_GW_TEAMLEAVE,										//
		PACKET_CG_TEAMDISMISS,										//��ɢ����
		PACKET_GW_TEAMDISMISS,										//
		PACKET_CG_TEAMKICK,											//�߳���Ա
		PACKET_GW_TEAMKICK,											//
		PACKET_CG_TEAMAPPLY,										//�����������
		PACKET_GW_TEAMAPPLY,										//
	/* ID:571 */PACKET_WG_TEAMASKAPPLY,								//
		PACKET_GW_TEAMRETAPPLY,										//
		PACKET_CG_TEAMRETAPPLY,										//
		PACKET_CG_ASKDETAILABILITYINFO, 							//�ͻ�����ҵ��������Ϣ
		PACKET_CG_TEAMAPPOINT ,										//�����¶ӳ�
		PACKET_GW_TEAMAPPOINT ,										//
		PACKET_CG_ABILITYGAMBLE,									//��������䷽�ϳ�ָ��
		PACKET_CG_ASK_COOLDOWN_UPDATE,								//�ͻ������������ȴʱ����Ϣ --���ڲ�����.
		PACKET_CG_DOEVENT,											//�ͻ���ѡ���¼��б��е�ĳ��ִ��
		PACKET_CG_MISSIONACCEPT ,									//��������
	/* ID:581 */PACKET_CG_MISSIONREFUSE ,							//�ܾ�����
		PACKET_CG_MISSIONABANDON ,									//��������
		PACKET_CG_MISSIONCONTINUE ,									//��������
		PACKET_CG_MISSIONSUBMIT ,									//�ݽ�����
	
		PACKET_CG_ASKMISSIONLIST ,									//�����б��ѯ
		//PACKET_CG_ASKMAIL ,											//
		PACKET_CG_CHANNELCREATE ,									//
		PACKET_CG_CHANNELDISMISS ,									//
		PACKET_CG_CHANNELINVITE ,									//
	/* ID:591 */PACKET_CG_CHANNELKICK ,								//
		//PACKET_CG_MAIL ,											//
		PACKET_GW_CHANNELCREATE ,									//
		PACKET_GW_CHANNELDISMISS ,									//
		PACKET_GW_CHANNELINVITE ,									//
		PACKET_GW_CHANNELKICK ,										//
		PACKET_GW_CHAT ,											//
		//PACKET_GW_MAIL ,											//
		PACKET_WG_CHANNELERROR ,									//
		PACKET_WG_CHANNELRESULT ,									//
	/* ID:601 */PACKET_WG_CHAT ,									//
		//PACKET_WG_MAIL ,											//
		PACKET_CG_GEM_COMPOUND,										//��ʯ�ϳ���Ϣ
		//PACKET_GW_ASKMAIL ,											// 
		//PACKET_WG_NOTIFYMAIL ,										//
		PACKET_CG_QUERYITEMBOXSTAGE,								//����Itembox���
		PACKET_CG_ASKTEAMINFO,										//���������Ϣ
		PACKET_GW_ASKTEAMINFO,										//���������Ϣ
		PACKET_CG_ASKTEAMMEMBERINFO,								//���������Ϣ
		PACKET_CG_LOCK_TARGET,										//�������Ŀ��
	/* ID:611 */PACKET_GW_ASKTEAMMEMBERINFO,						//���������Ϣ
		PACKET_WG_TEAMMEMBERINFO,									//���ض�����Ϣ
		PACKET_CG_SHOPBUY,											//��Ҵ���Ʒ�б�ѡ�������Ʒ
		PACKET_CG_SHOPSELL,											//��Ҵ���Ʒ�б�ѡ��Ҫ������Ʒ
		PACKET_CG_SHOPREPAIR,										//֪ͨ������������Ʒ
		PACKET_CG_SHOPCLOSE,										//֪ͨ�ͻ��˽��״��ڹرչر�
		PACKET_CG_ASKJOINMENPAI,									//��������
		PACKET_CG_ASKSTUDYXINFA,									//����ѧϰĳ��ĳ���ķ�
		PACKET_CG_ASKSTUDYABILITY,									//��������ύ����ѧϰ����ܵ���Ϣ
		PACKET_CG_CHARALLTITLES,									//�ͻ��������������������еĳƺ�
	/* ID:621 */PACKET_CG_CHARUPDATECURTITLE,						//������֪ͨ�ͻ��˴������еĳƺ�
		PACKET_CG_ASK_ACTIVETIME_UPDATE,							//�ͻ���������¼�����Чʱ����Ϣ
		PACKET_GW_TEAMMEMBERENTERSCENE,								//��Ա�����³���
		
		
		PACKET_CG_BANKREMOVEITEM,									//֪ͨ���������������Ƴ���Ʒ
		PACKET_CG_BANKSWAPITEM,										//֪ͨ���������������뱳����װ�����н�����Ʒ
		
		PACKET_CG_BANKCLOSE,										//֪ͨ�������رմ�������
		PACKET_CG_EXCHANGEAPPLYI,									//���״�
	/* ID:631 */PACKET_CG_EXCHANGEREPLYI,							//���״�����
		PACKET_CG_EXCHANGESYNCHLOCK,								//����ͬ����
		PACKET_CG_EXCHANGESYNCHITEMII,								//����ͬ����Ʒ
		PACKET_CG_EXCHANGESYNCHMONEYII,								//����ͬ����Ǯ
		PACKET_CG_EXCHANGEOKIII,									//����ͬ����Ϣ
		PACKET_CG_EXCHANGECANCEL,									//����ȡ��
		PACKET_GW_LEVEUP,											//��Ա�������¼���ˢ�µ� World ����
		PACKET_CG_PLAYER_DIE_RESULT,								//���������Ĳ������
		PACKET_GW_ASKSCENEDATA,										//��Ϸ�������������ݷ��������󳡾�������Ϣ
		PACKET_WG_RETSCENEDATA,										//�������ݷ������򳡾����ͳ���������Ϣ
	/* ID:641 */PACKET_GG_SCENENOTIFY,								//����֪ͨ��Ϣ
		PACKET_CG_SET_PETATTRIB,									//֪ͨ�����������ĳ�������
		PACKET_CG_MANIPULATEPET,									//������������,���ٻ�,�ջ�,�����Ȳ���
		PACKET_CG_ASK_TEAMFOLLOW,									//�ӳ����������Ӹ���
		PACKET_CG_STOP_TEAMFOLLOW,									//ĳ��Ա������ֹͣ�������״̬
		PACKET_CG_RETURN_TEAMFOLLOW,								//��Ա�ظ��Ƿ������Ӹ���״̬
		PACKET_GW_ENTER_TEAMFOLLOW,									//ĳ��Ա����������״̬
		PACKET_GW_STOP_TEAMFOLLOW,									//ĳ��Աֹͣ�������״̬
		PACKET_WG_TEAMFOLLOW_LIST,									//������Ӹ����б�
		PACKET_CG_MISSIONCHECK,										//��֤�����Ƿ��Ѿ����
	/* ID:651 */PACKET_CG_DISPEL_BUFF,								//�ͻ�������ȡ��������Ч��
		PACKET_CG_CHAR_STOP_LOGIC,									//�ͻ���������ֹ��ǰ�߼�
		PACKET_CG_PACKAGE_SWAPITEM,									//Ҫ�󽻻��������������Ʒ
		PACKET_CG_STALLAPPLY,										//������������ڴ˴���̯
		PACKET_CG_STALLESTABLISH,									//�ͻ��˽���̯λ����˰��
		PACKET_CG_STALLOPEN,										//�����������̯λ��Ʒ�б�
		PACKET_CG_STALLADDITEM,										//֪ͨ��������̯λ�м���Ʒ
		PACKET_CG_STALLREMOVEITEM,									//֪ͨ��������̯λ���ó���Ʒ
		PACKET_CG_STALLITEMPRICE,									//֪ͨ��������̯λ�е���Ʒ�ı��ۼ�
		PACKET_CG_STALLSHOPNAME,									//֪ͨ���������̸���
	/* ID:661 */PACKET_CG_STALLBUY,									//֪ͨ���������������Ʒ
		PACKET_CG_STALLCLOSE,										//֪ͨ�������Լ��رյ���
		PACKET_CG_BBSSYCHMESSAGES,									//���԰����
		PACKET_CG_BBSAPPLY,											//���԰����
		PACKET_CG_RELATION,											//�ͻ�������Ϸ���������ͺ��������Ϣ
		PACKET_GW_RELATION,											//��Ϸ���������������ݷ��������ͺ��������Ϣ

		PACKET_GW_RELATION_ENEMY,									//��Ϸ���������������ݷ��������ͳ�����ص���Ϣ

		PACKET_WG_RELATION,											//�������ݷ���������Ϸ���������ͺ��������Ϣ

		PACKET_CG_GUILD,											//�����Ϣ
		PACKET_GW_GUILD,											//�����Ϣ
		PACKET_WG_GUILD,											//�����Ϣ
	/* ID:671 */PACKET_WG_GUILDLIST,								//���ذ���б�(PlayerID_t, UCHAR, {GuildID_t,NAME,Level,UserCount,Status})
		PACKET_WG_GUILDERROR,										//���ذ���������(PlayerID_t, enum)
		PACKET_WG_GUILDRETURN,										//���ذ��������(PlayerID_t, enum)
		PACKET_WG_GUILDBASEINFO,									//��������Ϣ
		PACKET_WG_GUILDMEMBERS,										//������Ϣ
		PACKET_WG_GUILDAUTHORITY,									//���Ȩ�ޱ�
		PACKET_CG_ITEMSYNCH,										//��Ʒ�ƶ���Ϣ
		PACKET_LB_ASKAUTH,											//Login ����BillingSystem��֤
		PACKET_BL_RETAUTH,											//BillingSystem ������֤���
		PACKET_LW_ASKCHARLOGIN,										//�����ɫ��¼

		PACKET_LW_NOTIFY_CHARCHANGE,								//��ɫ�䶯֪ͨ(����/ɾ��)

	/* ID:681 */PACKET_WL_RETCHARLOGIN,								//World�����ɫ��¼
		PACKET_WG_TEAM_LIST,										//���ض�Ա�б�
		PACKET_CG_EXECUTESCRIPT,									//����ִ�з������˵�ĳ���ű�����
		PACKET_SS_SCENEPLAYERCOUNT,									//�������ݷ�����֪ͨ��Ϸ�������͵�½�����������е�������Ϣ
		PACKET_CG_SPLITITEM,										//�����Ʒ
		PACKET_CG_PLAYERSHOPAPPLY,									//����������봴������̵�
		PACKET_CG_PLAYERSHOPESTABLISH,								//�ͻ�ȷ���ж���Ϣ���ݽ��������
		PACKET_CG_PLAYERSHOPACQUIRESHOPLIST,						//����������봴������̵�
		PACKET_CG_PLAYERSHOPACQUIREITEMLIST,						//�ͻ�ȷ���ж���Ϣ���ݽ��������
		PACKET_GW_COMMAND,											//��Ҫ�������ݷ����������GMָ��
	/* ID:691 */PACKET_CG_PACKUP_PACKET,							//����������
		PACKET_CG_PLAYERSHOPONSALE,									//֪ͨ��������Ʒ���¼�
		PACKET_CG_PLAYERSHOPBUYITEM,								//֪ͨ������������Ʒ
		PACKET_CG_PLAYERSHOPMONEY,									//֪ͨ��������Ǯ��ȡ


		PACKET_CG_PLAYERSHOPNAME,									//�޸�����̵����
		PACKET_CG_PLAYERSHOPDESC,									//�޸�����̵������
		PACKET_CG_PLAYERSHOPOPENSTALL,								//���Ż�رչ�̨
		//PACKET_GW_BATCHMAIL,										//����������Ϣ
	/* ID:701 */PACKET_GW_CITYAPPLYNEWCITY,							//��World�������뽨���µĳ���
		PACKET_WG_CITYAPPLYNEWCITY,									//�ظ�Server�������뽨���µĳ���
		PACKET_WG_CITYERROR,										//�ظ�Server���д�����Ϣ
		PACKET_WG_CITYATTR,											//worldˢ�³�������
		PACKET_CG_CITYASKATTR,										//������������������
		PACKET_GW_CITYASKINITINFO,									//����ʱ�������������г�ʼ����Ϣ
		PACKET_GW_CITYCLOSE,										//�رճ���
		PACKET_GW_CITYCLOSESUCCESS,									//�رճ��гɹ�
		PACKET_WG_CITYCLOSE,										//�رճ��гɹ�
		PACKET_WG_CITYCLOSESUCCESS,									//�رճ��гɹ�
	/* ID:711 */PACKET_WG_CITYINITINFO,								//���������Ϣ
		PACKET_GW_CITYOPT,											//���в���
		PACKET_CG_ISSUEPETPLACARD,									//�������﹫��
		PACKET_CG_STALLFIRSTPAGE,									//��̯�ĳ�ʼҳ��
		PACKET_CG_MINORPASSWD,										//��������
		PACKET_CG_CHARPOSITIONWARP,									//λ��ƫ���������
		PACKET_CG_PLAYERSHOPSALEOUT,								//�̳��̵�
		PACKET_CG_PLAYERSHOPBUYSHOP,								//����˵�
		PACKET_CG_GUILDAPPLY,										//���뽨������
		PACKET_CG_GUILDJOIN,										//������빤��
	/* ID:721 */PACKET_CG_GUILDASKMEMBERINFO,						//�쿴�����Ա
		PACKET_GW_CHANGEMENPAI,										//�ı�����
		PACKET_GW_UPDATETITLE,										//���³ƺ�
		PACKET_CG_ASKPRIVATEINFO,									//������ϣ�����
		PACKET_CG_APPLYPRIVATEINFO,									//����޸��������
		PACKET_WG_WORLDTIME,										//World->Server ˢ������ʱ��
		PACKET_CG_CHARSIT,											//�������
		PACKET_CG_PLAYER_CALLOF_RESULT,								//����ȥĳ�صĲ������
		PACKET_GW_CALLOFHUMAN,										//���˵���Ϣ
		PACKET_WG_CALLOFHUMAN,										//���˵���Ϣ
	/* ID:731 */PACKET_CG_STALL_DEFAULT_PAGE,						//��̯ȱʡҳ���ύ
		PACKET_CG_SETMOODTOHEAD,									//����������ʾ
		PACKET_CG_FINGER,											//�������
		PACKET_GW_FINGER,											//������ҵĽ��
		PACKET_WG_FINGER,											//������ҵĽ��
		PACKET_CG_PLAYERSHOPASKFORRECORD,							//��������̵꽻�׼�¼��������¼
		PACKET_CG_PLAYERSHOPPARTNER,								//�������
		PACKET_CG_PLAYERSHOPFAVORITE,								//�����ɾ���ղؼ�
		PACKET_CG_PLAYERSHOPTYPE,									//����������ı��̵�����
		PACKET_CG_PLAYERSHOPSIZE,									//�����������ı��̵��С
	/* ID:741 */PACKET_CG_CGASKLOCKOBJ,								//��������һ��Obj
		PACKET_CG_CHARMOODSTATE,									// �����¼�
		PACKET_GW_HEARTBEAT,										//������ҵ�������Ϣ��World
		PACKET_CG_MISSIONDESC,										//�õ���������
		PACKET_CG_FIRSTLOGIN,								
		PACKET_LW_ASKDELETECHAR,									//����ɾ����ɫ
		PACKET_WL_RETDELETECHAR,									//World����ɾ����ɫ
		PACKET_BW_CONNECT,											//Web��������Billing��������һ����֤KEY����Ϣ
		PACKET_BW_VALIDATEUSER,										//Billing����������Web��֤�û���������
		PACKET_WB_RET_VALIDATEUSER,									//Billing����������Web��֤�û���������
		PACKET_WG_SYSTEMMSG,								//World��Server����ϵͳ��Ϣ
		PACKET_GW_SYSTEMMSG,										//Server��World����ϵͳ��Ϣ



		PACKET_LoginCharPacketBegin		= 0x1100,

		PACKET_CS_ASKLOGIN				= PACKET_LoginCharPacketBegin + 151,				//Ask Login
	
																							//����õ��û���������
	

//------Controller = 5  NPC ����ϵͳ   ---------------------------------------
		//NPC�ͽ���ϵͳ
		// ServerSide
		PACKET_NPC_SHOP_BEGIN			= 0x1400,
		PACKET_GC_SCRIPTCOMMAND			= PACKET_NPC_SHOP_BEGIN + 1,									//�ű����ͻ��˵�ָ��
		PACKET_GC_CHARMISSIONSTATE      = PACKET_NPC_SHOP_BEGIN + 3,                                    //��������״̬
		PACKET_ZGC_NPCSHOPLIST			= PACKET_NPC_SHOP_BEGIN + 9,									//Lua�ű�����:NPC�����̵���б�
		PACKET_zGC_SHOPBUY				= PACKET_NPC_SHOP_BEGIN + 10,
		PACKET_zGC_SHOPSELL				= PACKET_NPC_SHOP_BEGIN + 11,
		PACKET_GC_RECIPE				= PACKET_NPC_SHOP_BEGIN + 12,									//�ϳ���Ʒ
		PACKET_GC_TRADESHOP				= PACKET_NPC_SHOP_BEGIN + 30,								//ó���̵꿪��
		PACKET_GC_TRADECONTAINER		= PACKET_NPC_SHOP_BEGIN + 31,								//ó�ף����빺����
		PACKET_GC_TRADEBALANCE			= PACKET_NPC_SHOP_BEGIN + 32,								//ó�ף�����
		PACKET_GC_POPITEMS				= PACKET_NPC_SHOP_BEGIN + 33,								//����������Ʒ

        // DGH added [10/29/2010 dgh]
		PACKET_GC_NOTIFY_RECIPE_ID      = PACKET_NPC_SHOP_BEGIN + 40,								//���� �ӹ����ϵ�ID

		//ClientSide
		PACKET_CG_CHARDEFAULTEVENT      = PACKET_NPC_SHOP_BEGIN + 120 +1 ,								//ȱʡ�¼�
		PACKET_CG_EVENTREQUEST			= PACKET_NPC_SHOP_BEGIN + 120 +2 ,								//��ѯһ���ű��¼�
		PACKET_zCG_SHOPBUY				= PACKET_NPC_SHOP_BEGIN + 130,
		PACKET_zCG_SHOPSELL				= PACKET_NPC_SHOP_BEGIN + 131,
		PACKET_CG_RECIPE				= PACKET_NPC_SHOP_BEGIN + 132,									//�ϳ���Ʒ
		PACKET_CG_TRADECONTAINER		= PACKET_NPC_SHOP_BEGIN + 120 + 31,								//ó�ף����빺����
		PACKET_CG_TRADEBALANCE			= PACKET_NPC_SHOP_BEGIN + 120 + 32,								//ó�ף�����
//--------------------------����ϵͳ����---------------------------------------


		//ս�� 15/6
		PACKET_BATTLE_BEGIN				= 0x1500,	//6 + 15
		PACKET_GC_RETBATTLESTART		= PACKET_BATTLE_BEGIN + 1,							//ս����ʼ
		PACKET_GC_RETROUNDBEING			= PACKET_BATTLE_BEGIN + 2,							//�غϿ�ʼ���ͻ��˵���ʱ
		PACKET_GC_BATTLE_ROUND_RESULT	= PACKET_BATTLE_BEGIN + 3,							//ս���غϽ����
		PACKET_GC_BATTLE_FINA_RESULT	= PACKET_BATTLE_BEGIN + 4,							//ս�����������

		PACKET_GC_RET_CC_REQUEST		= PACKET_BATTLE_BEGIN + 5,							//�ͻ��˼������

		PACKET_CG_ASKBATTLESTART		= PACKET_BATTLE_BEGIN + 121,						//ս����ʼ
		PACKET_CG_ASKROUNDBEGIN			= PACKET_BATTLE_BEGIN + 122,						//�غϿ�ʼ���ͻ��˵���ʱ
		PACKET_CG_BATTLE_ACTION			= PACKET_BATTLE_BEGIN + 123,						//������ҹ���ָ��

		PACKET_CG_ASK_CC_REQUEST		= PACKET_BATTLE_BEGIN + 125,							//�ͻ��˼������


		//��� 16/7
		PACKET_TeamPacketBegin			= 0x1600,
		PACKET_zGC_TEAMASKINVITE		= PACKET_TeamPacketBegin + 1,						//�ͻ����յ�����������
		PACKET_zGC_TEAMRESULT			= PACKET_TeamPacketBegin + 2,						//������Ϣ���أ��������Ӷ�Ա���л��ӳ����˶ӣ����ˣ���ɢ��
		PACKET_zGC_TEAMERROR			= PACKET_TeamPacketBegin + 10,						//����еĴ���

		PACKET_zCG_TEAMINVITE			= PACKET_TeamPacketBegin + 121,						//�������˼������
		PACKET_zCG_TEAMRETINVITE		= PACKET_TeamPacketBegin + 122,						//�յ���Ӻ�Ļ�Ӧ
		PACKET_zCG_TEAMAPPOINT			= PACKET_TeamPacketBegin + 123,						//ָ���¶ӳ�
		PACKET_zCG_TEAMLEAVE			= PACKET_TeamPacketBegin + 124,						//�˳�����
		PACKET_zCG_TEAMDISMISS			= PACKET_TeamPacketBegin + 125,						//��ɢ����
		PACKET_zCG_TEAMKICK				= PACKET_TeamPacketBegin + 126,						//����

		//������� 17/8
		PACKET_ShipYardManageBegin      = 0x1700,
		PACKET_GC_RETSHIPLIST			= PACKET_ShipYardManageBegin + 1,					//���ش�����Ϣ
		PACKET_GC_RETSHIPINFO			= PACKET_ShipYardManageBegin + 2,					//���ؽ�����Ϣ
		PACKET_GC_RETSETCURSHIP         = PACKET_ShipYardManageBegin + 3,                   //�������õ�ǰ����
		PACKET_GC_RETSELLSHIP			= PACKET_ShipYardManageBegin + 4,                   //���س��۽���
		PACKET_GC_RETWARESHIPITEM		= PACKET_ShipYardManageBegin + 5,                   //����װ����������
		PACKET_GC_TAKEOFFALLITEM        = PACKET_ShipYardManageBegin + 6,					//һ��ж�ؽ���װ���ĵ���
		PACKET_GC_RETADDSHIPYARD		= PACKET_ShipYardManageBegin + 10,					//���ؿ�ͨ�´���
		PACKET_GC_RETFIXSHIPCOST		= PACKET_ShipYardManageBegin + 11,					//�����������ķ���
		PACKET_GC_RETFIXSHIP			= PACKET_ShipYardManageBegin + 12,					//����������

		PACKET_zCG_ASKSHIPLIST          = PACKET_ShipYardManageBegin + 121,                 //��ȡ������Ϣ
		PACKET_zCG_SETCURSHIP           = PACKET_ShipYardManageBegin + 123,                 //�����û���ǰ����
		PACKET_CG_SELLSHIP				= PACKET_ShipYardManageBegin + 124,                 //���۽���
		PACKET_CG_ASKWARESHIPITEM		= PACKET_ShipYardManageBegin + 120 + 5,             //װ����������
		PACKET_CG_TAKEOFFALLITEM        = PACKET_ShipYardManageBegin + 120 + 6,             //һ��ж�ؽ���װ���ĵ���
		PACKET_CG_ASKADDSHIPYARD		= PACKET_ShipYardManageBegin + 120 + 10,            //��ͨ�´��� 
		PACKET_CG_ASKFIXSHIP			= PACKET_ShipYardManageBegin + 120 + 12,            //ȷ��������

		

		//�������߹��� 18/9      added by ���� 2010 6-24--------------------------------
		//����--�������߲��뵽NPC������
		//����--װ��������Ҫ����װ�����߽ӿ�
		//��̨����ǰ̨
		PACKET_ITEM_BEGIN               = 0x1800,     //24
		PACKET_zGC_SETITEM              = PACKET_ITEM_BEGIN	+  1,                           //�趨����   ע:ǰ̨ʹ��Index�ж���Bag,Cargo,Bank
		PACKET_zGC_DELITEM				= PACKET_ITEM_BEGIN +  2,                           //ɾ������
		PACKET_zGC_USEITEM				= PACKET_ITEM_BEGIN +  4,							//ʹ�õ��߽��  GCUserItemResult
		PACKET_zGC_SPLITITEM			= PACKET_ITEM_BEGIN +  5,                           //���صĲ�ֵ��߽�� GCSplitItemResult
		PACKET_zGC_SWAPITEM				= PACKET_ITEM_BEGIN +  6,							//���ؽ�������λ�ý�� GCPackage_SwapItem
		PACKET_zGC_RETASKMYBAG          = PACKET_ITEM_BEGIN +  10,                          //���ر���,Cargo,Bank�����б�  GCMyBagList
		PACKET_zGC_SETCONTAINERSIZE		= PACKET_ITEM_BEGIN +  11,							//������չ����,������չ�ֿ���
		PACKET_GC_SETCARGOSIZE			= PACKET_ITEM_BEGIN +  12,							//�趨Cargo��С


		PACKET_GC_BANKACQUIRELIST       = PACKET_ITEM_BEGIN +  21,							//�����е���Ʒ���͸��ͻ���
		PACKET_GC_BANKADDITEM           = PACKET_ITEM_BEGIN +  22,							//֪ͨ�ͻ��˼���Ʒ���
		PACKET_GC_BANKITEMINFO          = PACKET_ITEM_BEGIN +  23,							//������Ʒ��Ϣ		
		PACKET_GC_BANKMONEY             = PACKET_ITEM_BEGIN +  24,  						//֪ͨ�ͻ��˴�ǮȡǮ���
		PACKET_GC_ADDBANKCAPACITY       = PACKET_ITEM_BEGIN +  25,			                //�������е�����
		
		PACKET_zGC_SETITEMLIST			= PACKET_ITEM_BEGIN +  30,							//�����趨��,�б��
		PACKET_GC_CARGOACQUIRELIST		= PACKET_ITEM_BEGIN +  31,							//�����е���Ʒ���͸��ͻ���
		
		PACKET_zGC_RECEIVEITEMINFO		= PACKET_ITEM_BEGIN +  40,							//��ʾ�յ���Ʒ��Ϣ

		PACKET_GC_RET_ITEM_EXTRA_INFO   = PACKET_ITEM_BEGIN +  46,                          //��ȡ��Ʒǿ����Ϣ

		PACKET_zGC_TRANSFORM_RETURN			=	PACKET_ITEM_BEGIN	+	47,		//GCTransformItemRet
	
		

		//ǰ̨������̨
		PACKET_zCG_USEITEM				= PACKET_ITEM_BEGIN +  120,                         //ʹ�õ���  CGUserItem
		PACKET_zCG_DROPITEM				= PACKET_ITEM_BEGIN +  121,                         //��������  CGDiscardItem
		PACKET_zCG_SPLITITEM            = PACKET_ITEM_BEGIN +  122,                         //��ֵ���  CGSplitItem
		PACKET_zCG_EQUIPITEM            = PACKET_ITEM_BEGIN +  124,							//ʹ��װ��(װ��ָ�������ڵ�װ�������) CGUserEquip
		PACKET_zCG_SWAPITEM				= PACKET_ITEM_BEGIN +  125,							//��������λ�� CGPackage_SWapItem
		PACKET_zCG_ASKMYBAG             = PACKET_ITEM_BEGIN +  130,							//��ȡ��ǰ�û�������Ϣ CGAskBagList
		PACKET_zCG_EXTBAG				= PACKET_ITEM_BEGIN +  131,                         //��չ��ǰ�û�����   ����
		PACKET_zCG_REORGNIZEBAG			= PACKET_ITEM_BEGIN +  132,							//����ǰ�û�����   CGPackUpPacket
		

		PACKET_CG_BANKACQUIRELIST       = PACKET_ITEM_BEGIN +  120 + 21,					//���������ȡ�洢���б�
		PACKET_CG_BANKADDITEM           = PACKET_ITEM_BEGIN +  120 + 22,					//֪ͨ�������������м���Ʒ
		PACKET_CG_BANKMONEY             = PACKET_ITEM_BEGIN +  120 + 24,					//֪ͨ��������ǮȡǮ
		PACKET_CG_ADDBANKCAPACITY       = PACKET_ITEM_BEGIN +  120 + 25,                    //�������е�����
		PACKET_CG_CARGOACQUIRELIST		= PACKET_ITEM_BEGIN +  120 + 31,					//�����е���Ʒ���͸��ͻ���


		PACKET_CG_ASK_ITEM_EXTRA_INFO   = PACKET_ITEM_BEGIN +  120 + 46,                     //��ȡ��Ʒǿ����Ϣ
		PACKET_zCG_TRANSFORM_REQUEST	= PACKET_ITEM_BEGIN	+  120 + 47,				     //CGTransformItem

		//-----------------------------------��������End--------------------------------------


		//����&�츳 1A/11
		PACKET_TALENT_SKILL_BEGIN		= 0x1A00,	//11 + 15
		PACKET_zGC_ASKSTUDYTALENT		= PACKET_TALENT_SKILL_BEGIN + 1,					//ѧϰ�츳����
		PACKET_zGC_ASKSTUDYSKILL		= PACKET_TALENT_SKILL_BEGIN + 2,					//ѧϰ���ܷ���
		PACKET_zGC_DETAILTALENTLIST		= PACKET_TALENT_SKILL_BEGIN + 3,					//��ѧ�츳�����ܣ�����
		//PACKET_zGC_DETAILSKILL			= PACKET_TALENT_SKILL_BEGIN + 4,					//��ѧ���ܷ���
		PACKET_GC_MAPBUFF				= PACKET_TALENT_SKILL_BEGIN + 5,					//��ѧ�츳�����ܣ�����
		PACKET_GC_GATHER_GOODS			= PACKET_TALENT_SKILL_BEGIN + 6,					//�ɼ���Ʒ����

		PACKET_zCG_ASKSTUDYTALENT		= PACKET_TALENT_SKILL_BEGIN + 121,					//ѧϰ�츳
		PACKET_zCG_ASKSTUDYSKILL		= PACKET_TALENT_SKILL_BEGIN + 122,					//ѧϰ����
		PACKET_zCG_DETAILTALENTLIST		= PACKET_TALENT_SKILL_BEGIN + 123,					//������ѧ�츳�����ܣ�
		PACKET_CG_RESETTALENT			= PACKET_TALENT_SKILL_BEGIN + 124,					//�����츳
		PACKET_CG_MAPBUFF				= PACKET_TALENT_SKILL_BEGIN + 125,					//�����ͼbuff
		PACKET_CG_GATHER_GOODS			= PACKET_TALENT_SKILL_BEGIN + 126,					//�ɼ���Ʒ
		PACKET_CG_CANCEL_MAPBUFF		= PACKET_TALENT_SKILL_BEGIN + 127,					//ȡ����ͼbuff


		//����--------------------------------------
		PACKET_RELATION_OPT_BEGIN			= 0x1B00,	//12 + 15

		PACKET_zGC_RELATIONOPT		= PACKET_RELATION_OPT_BEGIN + 1,		//���غ��Ѳ���

		PACKET_zCG_RELATIONOPT		= PACKET_RELATION_OPT_BEGIN + 121,	//������Ѳ���
		//------------------------------------------


////////////////////////////////////////////////////////////////////////
//     ����:  added by DGH
//          Controller��13 ( 0x1C00 )
///////////////////////////////////////////////////////////////////////
        PACKET_RANGE_DATA_BEGIN         = 0x1C00,// 13+15
//////////////////////////////////////////////////////////////
// Server responent
//////////////////////////////////////////////////////////////
        PACKET_GC_RANGE_DATA_RESPONENT   =  PACKET_RANGE_DATA_BEGIN + 1,		//������������
//////////////////////////////////////////////////////////////
// From client
/////////////////////////////////////////////////////////////
        PACKET_CG_RANGE_DATA_REQUEST			=  PACKET_RANGE_DATA_BEGIN + 1 + 120, //��ȡ��������
		PACKET_CG_RANGE_DATA_QUERYBYNAME		=  PACKET_RANGE_DATA_BEGIN + 2 + 120, //��ѯָ����ҵ�����


		PACKET_GW_GET_RANGELIST, // G-->W ��ȡ��ҵ���������
		PACKET_WG_GET_RANGELIST, // W-->G ������Ҳ�ѯ����������

//-------------------------------���������ʼ---------------------------------------------------------
		//�������  0x1D00 / 14 ------------------- addedBy ���� 2010-7-2
		PACKET_GUILD_BEGIN				= 0x1D00,
		//��������
		//Server Side
		PACKET_zGC_GUILD			  =	 PACKET_GUILD_BEGIN + 1,  // ������Ϣ������ GCGuild
		PACKET_zGC_GUILDRETURN		  =	 PACKET_GUILD_BEGIN + 2,  // ������������� GCGuildReturn
		PACKET_zGC_GUILDERROR		  =  PACKET_GUILD_BEGIN + 10, // ����������󷵻��� GCGuildError

	//Client Side
		PACKET_zCG_GUILDAPPLY		  =  PACKET_GUILD_BEGIN + 121,  // �ͻ��˹��ᴴ������  GCGuildApply
		PACKET_zCG_GUILD			  =  PACKET_GUILD_BEGIN + 122,  // �ͻ��˹������      CGGuild
		PACKET_zCG_GUILDJOIN		  =  PACKET_GUILD_BEGIN + 123,  // �ͻ�����Ӧ�������  CGGuildJoin
	

//------------------------------�����������------------------------------------------------------------

		//����������� 0x1E00 / 15
		PACKET_SHIP_BUILD_BEGIN         = 0x1E00,
		PACKET_GC_RETBUILDSHIPINFO      = PACKET_SHIP_BUILD_BEGIN + 1,
		PACKET_GC_RETBUILDSHIP          = PACKET_SHIP_BUILD_BEGIN + 2,
		PACKET_GC_GETBUILDSHIP          = PACKET_SHIP_BUILD_BEGIN + 3,   
		PACKET_GC_RETRECASTSHIPINFO     = PACKET_SHIP_BUILD_BEGIN + 4,						 //���������ȡ������Ϣ
		PACKET_GC_RETRECASTSHIP         = PACKET_SHIP_BUILD_BEGIN + 5,						 //��������


		PACKET_CG_ASKBUILDSHIPINFO		= PACKET_SHIP_BUILD_BEGIN + 120 + 1,                 //��ȡ���콢������Ϣ
		PACKET_CG_ASKBUILDSHIP          = PACKET_SHIP_BUILD_BEGIN + 120 + 2,                 //���콢��
		PACKET_CG_TAKEBUILDSHIP         = PACKET_SHIP_BUILD_BEGIN + 120 + 3,                 //��ȡ����Ĵ�ֻ
		PACKET_CG_ASKRECASTSHIPINFO     = PACKET_SHIP_BUILD_BEGIN + 120 + 4,				 //���������ȡ������Ϣ
		PACKET_CG_ASKRECASTSHIP         = PACKET_SHIP_BUILD_BEGIN + 120 + 5,				 //��������



		PACKET_GW_SHIPBUILD ,																//��Ϸ������֪ͨ�����������ʱ֪ͨ���
		PACKET_WG_SHIPBUILD ,

/************************************************************************/
/* ����ϵͳ
	ָ��Controller 16
	ָ��Start     0x1F00
*/
/************************************************************************/
	    PACKET_EXCHANGE_BEGIN			= 0x1F00, //0x2000,

		//����˷���
		PACKET_zGC_EXCHANGEAPPLY		= PACKET_EXCHANGE_BEGIN	+	1,			//�������������ҽ��� GC_ExchangeApplyI
		PACKET_zGC_EXCHANGEESTABLISH	= PACKET_EXCHANGE_BEGIN	+	2,			//��ʼ��������	GC_ExchangeEstablish
		PACKET_zGC_EXCHANGESYNC			= PACKET_EXCHANGE_BEGIN +	3,          //�����е���,��Ǯ�Ķ�ͬ�� GC_ExchangeSynch
		PACKET_zGC_EXCHANGESYNCLOCK		= PACKET_EXCHANGE_BEGIN +   4,			//�����жԷ���ȷ�� GC_ExchangeSynchLock
		PACKET_zGC_EXCHANGECONFIRM		= PACKET_EXCHANGE_BEGIN +	5,			//������"����"��ť��״̬ GC_ExchangeSyncConfirm
		PACKET_zGC_EXCHANGESUCCESS		= PACKET_EXCHANGE_BEGIN +	10,			//���׳ɹ�		GC_ExchangeSuccess
		PACKET_zGC_EXCHANGECANCEL		= PACKET_EXCHANGE_BEGIN	+	15,			//�Է�ȡ������ GC_ExchangeCancel
		PACKET_zGC_EXCHANGEERROR		= PACKET_EXCHANGE_BEGIN	+	20,			//�����еĴ�����ʾ


		//�ͻ��˷���
		PACKET_zCG_EXCHANGEAPPLY		= PACKET_EXCHANGE_BEGIN +   121,		//Ҫ��������ҽ��� CGExchangeApplyI
		PACKET_zCG_EXCHANGEREPLY		= PACKET_EXCHANGE_BEGIN +	122,		//ͬ����н���	 CGExchangeReply
		PACKET_zCG_EXCHANGESYNCITEM		= PACKET_EXCHANGE_BEGIN +	123,		//���׵��߽��� CGExchangeSyncItemII
		PACKET_zCG_EXCHANGESYNCMONEY	= PACKET_EXCHANGE_BEGIN +	124,		//�����н�Ǯ�ı�� CGExchangeSyncMoneyII
		PACKET_zCG_EXCHANGESYNCLOCK		= PACKET_EXCHANGE_BEGIN	+	125,		//�����е�"ȷ��"��ť CGExchangeSynclock
		PACKET_zCG_EXCHANGEOK			= PACKET_EXCHANGE_BEGIN +	130,		//�����е�"����"��ť CGExchangeOkIII
		PACKET_zCG_EXCHANGECANCEL		= PACKET_EXCHANGE_BEGIN +	135,		//�����е�"ȡ��"��ť,���߹رս��׽��� CGExchangeCancel

		//���׵ĳ�ʱ
		PACKET_GW_EXCHANGETIMER			= PACKET_EXCHANGE_BEGIN +   200,
		PACKET_WG_EXCHANGETIMER,


/************************************************************************/
/* ����ϵͳ����                                                                     */
/************************************************************************/


//=======================================================================
//�ʼ�ϵͳ��control = 17   added by DGH
//=======================================================================
 PACKET_MAIL_BEGIN = 0x2000,

 //��̨�ظ�ָ��
 PACKET_GC_MAIL			= PACKET_MAIL_BEGIN +1,//��������ʼ��б�

 //PACKET_GC_READMAIL		= PACKET_MAIL_BEGIN+2,//��ȡδ���ʼ�
 //PACKET_GC_DELETEMAIL	= PACKET_MAIL_BEGIN+3,//ɾ���ʼ�����ָ���Ѿ����ڣ�����ԭָ����и��ǣ�) 
 //PACKET_GC_MAIL			= PACKET_MAIL_BEGIN+4,//�����ʼ��󷵻�

 PACKET_GC_GETMAILGIFT	= PACKET_MAIL_BEGIN	+5, //��ȡ�ʼ�����
 PACKET_GC_NOTIFYMAIL   = PACKET_MAIL_BEGIN	+10,//֪ͨ��ң���ǰ���ʼ��ɽ���
 PACKET_GC_MAIL_RESULT  = PACKET_MAIL_BEGIN	+20,//�ʼ������������(���ͣ�ɾ�������ñ�־)�����ش�����Ϊ0��ʾ�����ɹ���

 //ǰ̨����ָ��
 PACKET_CG_ASKMAIL      = PACKET_MAIL_BEGIN +1 +120,//��ȡ�ʼ��б�  
 PACKET_CG_SETMAILFLAG	= PACKET_MAIL_BEGIN +2 +120,//�����ʼ���־(�����ʼ�δ����־)
 PACKET_CG_DELETEMAIL	= PACKET_MAIL_BEGIN +3 +120,//ɾ���ʼ�
 PACKET_CG_MAIL			= PACKET_MAIL_BEGIN +4 +120,//�������ʼ�
//��ȡ�ʼ���Ʒ
 PACKET_CG_GETMAILGIFT	= PACKET_MAIL_BEGIN +5 +120,//��ȡ�ʼ�����
//��ѯ��������
PACKET_CG_MAILLISTSIZE	= PACKET_MAIL_BEGIN +6 +120,//��ȡ��������(����95���ʼ�ʱ,����)

 //world��������game������������
 //----------------------------------------
 //PACKET_CG_ASKMAIL ��صİ�:
 PACKET_GW_ASKMAIL ,											// game server �� world ��ȡ�ʼ��б� 

 PACKET_GW_READ_MAIL,                                           // G --> W :��Ҷ�ȡ���ʼ�(�޸��ʼ��ڷ���˵�״̬)

 PACKET_GW_DELETE_MAIL,											// G --> W :���ɾ���ʼ�

 PACKET_WG_MAIL ,											    // world������֪ͨgame server �����ʼ��б�

 PACKET_WG_NOTIFYMAIL ,                                         // world  �� game server ������Ϣ���ʼ�(��¼���һ����Ϣ�ʼ���) 
 //----------------------------------------
 PACKET_GW_MAIL ,                                               // game server ֪ͨ world ,��ҷ������ʼ�;

 PACKET_GW_GET_PRESENT,                                         // GAME --> WORLD ��ȡ�ʼ�����;

 PACKET_GW_CLEAR_MAIL_PARAM,									// game --> world ������ȡ�ɹ�������ʼ�����;

 PACKET_WG_GET_PRESENT,											//WORLD --> GAME ʵ�ָ�����ȡ����

 PACKET_WG_MAIL_RESPONSE,                                       // WORLD ֪ͨ SERVER �ʼ��������(����,ɾ��,�鿴,��ȡ)

 PACKET_GW_BATCHMAIL,											// ����������Ϣ(�����к��ѷ����ʼ�) 

 PACKET_GW_MAILLISTSIZE	,										//��world����ǰ�����������
 PACKET_WG_MAILLISTSIZE ,										//����game��ǰ�����������

//=======================================================================
//�ʼ�����	
//=======================================================================

//--�̳�ϵͳ-----Controller:18 -----------------------------------------------

		PACKET_MALL_BEGIN	=	0x2100,

		//����˷���
		PACKET_zGC_MALLLIST		=	PACKET_MALL_BEGIN	+	1,	//GCMallList
		PACKET_zGC_MALLNOTICE	=	PACKET_MALL_BEGIN	+	2,	//GCMallNotice
		PACKET_zGC_MALLRESULT	=	PACKET_MALL_BEGIN	+	3,	//GCMallResult

		//�ͻ��˷���
		PACKET_zCG_MALLLIST		=	PACKET_MALL_BEGIN	+	121,	//CGMallList
		PACKET_zCG_MALLNOTICE	=	PACKET_MALL_BEGIN	+	122,	//CGMallNotice
		PACKET_zCG_MALLBUY		=	PACKET_MALL_BEGIN	+	123,	//CGMallBuy
		PACKET_zCG_MALLGIFT		=	PACKET_MALL_BEGIN	+	124,	//CGMallGift

//--�̳�ϵͳ����--------------------------------------------------------


//=======================================================================
//������� added by  oj 2010-8-9	
//=======================================================================
		PACKET_MISSION_BEGIN	=	0x2200,

		//����˷���
		PACKET_zGC_ASKMISSIONLIST		=	PACKET_MISSION_BEGIN	+ 1,		//���������б�
		PACKET_zGC_MISSIONDESC			=	PACKET_MISSION_BEGIN	+ 2,		//��������		
		PACKET_zGC_MISSIONADD			=	PACKET_MISSION_BEGIN	+ 3,		//�������
		PACKET_zGC_MISSIONABANDON		=	PACKET_MISSION_BEGIN	+ 5,		//��������
		PACKET_zGC_MISSIONMODIFY		=	PACKET_MISSION_BEGIN	+ 9,		//�����޸�
		PACKET_zGC_MISSIONNOTIFYSTATE	=	PACKET_MISSION_BEGIN	+ 10,		//����Ŀ��״̬

//-----------------------------------------------------------------------

		//�ͻ��˷���
		PACKET_zCG_ASKMISSIONLIST		=	PACKET_MISSION_BEGIN	+	121,	//��ѯ�����б�
		PACKET_zCG_MISSIONDESC			=	PACKET_MISSION_BEGIN	+	122,	//��ѯ��������		
		PACKET_zCG_MISSIONACCEPT		=	PACKET_MISSION_BEGIN	+	123,	//��������
		PACKET_zCG_MISSIONREFUSE		=	PACKET_MISSION_BEGIN	+	124,	//�ܾ�����
		PACKET_zCG_MISSIONABANDON		=	PACKET_MISSION_BEGIN	+	125,	//��������
		PACKET_zCG_MISSIONCONTINUE		=	PACKET_MISSION_BEGIN	+	126,	//�������
		PACKET_zCG_MISSIONSUBMIT		=	PACKET_MISSION_BEGIN	+	128,	//�������


//=======================================================================
//�������		
//=======================================================================
		
//=======================================================================
//���߹һ�	 Controller 20	zhonglei
//=======================================================================
	 PACKET_OFFLINE_BEGIN	=	0x2300,

	 //����˷���
	 PACKET_zGC_RetAskOfflineExp	=		PACKET_OFFLINE_BEGIN	+	1,	//�������߹һ��ľ���,ʱ��
	 PACKET_zGC_RetWithdrawExp		=		PACKET_OFFLINE_BEGIN	+	2,	//������ȡ���߹һ�������
//-----------------------------------------------------------------------
	// �ͻ��˷���
	 PACKET_zCG_AskOfflineExp		=		PACKET_OFFLINE_BEGIN	+	121,	//�������߹һ�ʱ�侭��
	 PACKET_zCG_WithdrawExp			=		PACKET_OFFLINE_BEGIN	+	122,	//��ȡ���߹һ�����

//=======================================================================
//���߹һ�����
//=======================================================================

//////////////////////////////////////////////////////////////////////////
//����ָ�� Controller 21 DGH added
//  [11/19/2010 dgh]
//////////////////////////////////////////////////////////////////////////
        PACKET_GUIDE_STEP_BEGIN	= 0x2400,
		//�������ذ� 
		PACKET_GC_GetGuideStep  = PACKET_GUIDE_STEP_BEGIN  +1,        //���ص�ǰ���ֲ����
		//�ͻ��˷���
		PACKET_CG_GuideStepSet  = PACKET_GUIDE_STEP_BEGIN   + 120 +1, //�ύ���ֲ���


    



		PACKET_MAX																			//��Ϣ���͵����ֵ
	};
};


#endif

