#ifndef __PACKET_DEFINE_H__
#define __PACKET_DEFINE_H__


namespace Packets
{
	//消息类型值描述格式：PACKET_XX_YYYYYY
	//XX可以描述为：GC、CG、CL、LC、GL、LG
	//G游戏服务器端、C客户端、L登陆服务器端、S服务器端程序（可以是登陆，也可以是游戏）
	//YYYYYY表示消息内容
	//例如：PACKET_CG_ATTACK 表示客户端发给游戏服务器端关于攻击的消息
	enum PACKET_DEFINE
	{
		PACKET_NONE = 0 ,						//0，空

	/* ID:1 */PACKET_GC_TEST ,

		PACKET_GC_LEAVESCENE ,										//服务器发给其他客户端某玩家离开的消息

		PACKET_GC_NEWITEM,											//有新的独立物品出现在自己的视野范围
		PACKET_GC_NEWITEMBOX,
		PACKET_GC_NEWMONSTER,										//有新的怪物进入自己的视野范围
		PACKET_GC_NEWMONSTER_DEATH,									//创建死亡的OBJ
		PACKET_GC_NEWMONSTER_MOVE,									//创建移动的OBJ
	/* ID:10 */
		PACKET_GC_NEWPLAYER_DEATH,									//创建死亡的PLAYER
		PACKET_GC_NEWPLAYER_MOVE,									//创建移动的PLAYER
		PACKET_GC_PLAYERREALMOVE,									//废弃
		PACKET_GC_MONSTERREALMOVE,									//废弃

		PACKET_GC_CHAREQUIPMENT,									//刷新角色简单装备表
		PACKET_GC_DIE ,
		PACKET_GC_LEVEUP,
		PACKET_GC_LEVELUPRESULT,									//请求升级结果
	/* ID:20 */PACKET_GC_MANUALATTRRESULT,							//点数分配结果
		PACKET_GC_RESETATTRRESULT,									//洗点结果
		PACKET_GC_MYEQUIPMENT,										//废弃
		PACKET_GC_OTHEREQUIPMENT,									//废弃
		PACKET_GC_DETAILATTRIB ,									//刷新当前主角属性
		PACKET_GC_DETAILEQUIPMENTLIST,								//刷新当前主角装备列表
		PACKET_GC_DETAILSKILLLIST,									//刷新当前主角技能列表
		PACKET_GC_DETAILSUBEFFECTLIST,								//刷新当前主角附加属性列表
		PACKET_GC_MYBAGLIST,										//刷新主角背包
		PACKET_GC_CHARIDLE,											//通知CLIENT进入IDLE状态
	/* ID:30 */PACKET_GC_CHARJUMP,									//通知CLIENT跳跃一次

		PACKET_GC_MOVE ,											//废弃
		PACKET_GC_ARRIVE ,											//废弃
		PACKET_GC_CHARSKILL_CREATEBULLET,							//创建子弹
		PACKET_GC_CHARSKILL_EFFECT,									//技能作用效果(伤害)
		PACKET_GC_CHARSKILL_GATHER,									//技能聚气
		PACKET_GC_CHARSKILL_GATHER_MODIFY,							//技能聚气时间的延长等等
		PACKET_GC_CHARSKILL_LEAD,									//技能引导
		PACKET_GC_CHARSKILL_LEAD_MODIFY,							//技能引导时间的缩短等等
	/* ID:40 */PACKET_GC_CHARSKILL_SEND,							//技能发招
		PACKET_GC_ATTACK ,											//废弃
		PACKET_GC_OTHERATTACK ,										//废弃
		PACKET_GC_ERRORATTACK ,										//废弃
		PACKET_GC_SKILL ,											//废弃
		PACKET_GC_OTHERSKILL ,										//废弃
		PACKET_GC_ERRORSKILL ,										//废弃
		PACKET_GC_SKILLPREPARE ,									//废弃
		PACKET_GC_USEITEMRESULT,									//使用道具结果
		PACKET_GC_BOXITEMLIST,										//Obj_ItemBox 物品列表
	/* ID:50 */PACKET_GC_PICKRESULT,								//捡取结果
		PACKET_GC_USEEQUIPRESULT,									//装配装备结果

		PACKET_GC_UNEQUIPRESULT,									//卸下装备结果
		PACKET_GC_DISCARDITEMRESULT,								//丢弃物品结果

		PACKET_GC_CHAT,												//说话

		PACKET_GC_ITEMINFO,											//服务器返回某件装备的详细信息
		PACKET_GC_DETAILEQUIPLIST,									//服务器返回自身装备详细信息
	/* ID:60 */PACKET_GC_NEWPORTAL,									//有一个传送点可以看见了
		PACKET_GC_DETAILXINFALIST,									//刷新当前主角心法列表
		PACKET_GC_DISCARDEQUIPRESULT,								//丢弃物品结果
		PACKET_GC_NOTIFYEQUIP,										//通知客户端包裹里添加新装备了
		PACKET_GC_NEWSKILLOBJ,										//创建SkillObj的消息
		PACKET_GC_USEGEMRESULT,										//使用宝石结果
		PACKET_GC_REMOVEGEMRESULT,									//卸载宝石结果
		PACKET_GC_CHARIMPACT,										//角色附加效果
		PACKET_GC_OPERATE_RESULT,									//操作的返回
		PACKET_GC_USEEQUIPSKILL_RESULT,
	/* ID:70 */PACKET_GC_TEAMERROR,									//
		PACKET_GC_TEAMASKINVITE,									//
		PACKET_GC_TEAMLEADERASKINVITE,								//
		PACKET_GC_TEAMRESULT,										//
		PACKET_GC_TEAMASKAPPLY,										//
		PACKET_GC_ABILITY_RESULT,									//生活技能的操作返回结果
		PACKET_GC_DETAILABILITYINFO,								//服务器端发送玩家生活技能信息
		PACKET_GC_COOLDOWN_UPDATE,									//冷却时间更新
		PACKET_GC_ABILITY_ACTION,									//生活技能的操作动作
	/* ID:80 */PACKET_GC_ABILITY_SUCC,								//生活技能的成功消息
		PACKET_GC_NOTIFYTEAMINFO ,									//通知客户端,队伍中信息变化
		PACKET_GC_MISSIONLIST ,										//返回任务列表
		PACKET_GC_MISSIONADD ,										//增加一个任务
		PACKET_GC_MISSIONREMOVE ,									//删除一个任务
		PACKET_GC_MISSIONMODIFY ,									//更改一个任务参数
		PACKET_GC_CHANNELERROR ,									//
		PACKET_GC_CHANNELRESULT ,									//
		//PACKET_GC_MAIL ,											//
		//PACKET_GC_NOTIFYMAIL ,										//
	/* ID:90 */PACKET_GC_NEWPLATFORM,								//创建操作台的消息
		PACKET_GC_ABILITYLEVEL,										//生活技能信息
		PACKET_GC_ABILITYEXP,										//生活技能熟练度信息
		PACKET_GC_PRESCRIPTION,										//生活技能配方信息
		PACKET_GC_ABANDON_ABILITY,									//放弃生活技能
		PACKET_GC_ITEMBOXCHANGESTAGE,								//Obj_ItemBox改变外观
		PACKET_GC_CANPICKMISSIONITEMLIST,							//可以拾取的任务物品列表
		PACKET_GC_ADDCANPICKMISSIONITEM,							//添加一个可以拾取的任务物品
		PACKET_GC_REMOVECANPICKMISSIONITEM,							//删除一个可以拾取的任务物品
		PACKET_GC_MODIFYSPEED,										//对象速度改变
	/* ID:100 */PACKET_GC_MONSTERSPEAK,								//怪物泡泡说话
		PACKET_GC_TEAMMEMBERINFO,									//返回队友信息
		PACKET_GC_LOCK_TARGET,										//玩家锁定目标
		PACKET_GC_SHOPMERCHANDISELIST,								//商品列表	
		PACKET_GC_SHOPSOLDLIST,										//回购商品列表
		PACKET_GC_SHOPUPDATEMERCHANDISELIST,						//更新商品列表
		PACKET_GC_SHOPBUY,											//通知客户端买是否成功
		PACKET_GC_SHOPSELL,											//通知客户端卖是否成功
		PACKET_GC_SHOPREPAIR,										//通知服务器修理物品
		PACKET_GC_MENPAIINFO,										//门派信息（ID）
	/* ID:110 */PACKET_GC_JOINMENPAI,								//加入门派的结果
		PACKET_GC_XINFASTUDYINFO,									//可以学习的心法（包括级别）信息
		PACKET_GC_STUDYXINFA_H,										//学习的结果
		PACKET_GC_ABILITY_STUDYINFO,								//学习生活技能的信息
		PACKET_GC_CHARALLTITLES,									//服务器通知客户端此人所有的称号
		PACKET_GC_ACTIVETIME_UPDATE,								//废弃
		PACKET_GC_OBJ_TELEPORT,										//角色瞬移
		PACKET_GC_BANKBEGIN,										//通知客户端开始打开银行
		
		
	/* ID:120 */PACKET_GC_BANKREMOVEITEM,							//通知客户端移除物品结果
		PACKET_GC_BANKSWAPITEM,										//通知客户端从银行中与背包或装备栏中交换物品的结果
		
		PACKET_GC_DETAILATTRIB_PET,									//宠物的详细属性
		PACKET_GC_EXCHANGEERROR,									//交易出错
		PACKET_GC_EXCHANGEAPPLYI,									//申请交易
		PACKET_GC_EXCHANGEESTABLISHI,								//交易确定
		PACKET_GC_EXCHANGESYNCHLOCK,								//交易同步锁
		PACKET_GC_EXCHANGESYNCHCONFIRMII,							//交易同步确定
		PACKET_GC_EXCHANGESYNCHII,									//交易同步
	/* ID:130 */PACKET_GC_EXCHANGESUCCESSIII,						//交易成功消息
		PACKET_GC_EXCHANGECANCEL,									//交易取消
		PACKET_GC_PLAYER_DIE,										//主角死亡
		PACKET_GC_PLAYER_RELIVE,									//主角复活
		PACKET_GC_MANIPULATEPETRET,									//请求操作宠物的返回结果
		PACKET_GC_ASK_TEAMFOLLOW,									//给队员发送进入组队跟随请求
		PACKET_GC_RETURN_TEAMFOLLOW,								//给客户端发送组队跟随状态
		PACKET_GC_TEAMFOLLOW_LIST,									//组队跟随列表
		PACKET_GC_TEAMFOLLOW_ERROR,									//组队跟随下的错误消息
		PACKET_GC_MISSIONRESULT,									//任务完成与否
	/* ID:140 */PACKET_GC_CHAR_DIRECT_IMPACT, 						//效果:一次性效果
		PACKET_GC_CHAR_BUFF, 										//效果: 持续性效果
		PACKET_GC_DETAIL_BUFF,										//效果: 持续性效果的详细数据.数据量大,只发给自己
		PACKET_GC_CHARSKILL_MISSED,									//技能: 技能没有命中
		PACKET_GC_CHAR_IMPACT_LIST_UPDATE,							//更新效果列表(简要信息，广播用)
		PACKET_GC_DETAIL_IMPACT_LIST_UPDATE,						//更新效果列表(详细信息，只给玩家自己发)
		PACKET_GC_DETAIL_HEALS_AND_DAMAGES, 						//HP,MP,Rage,Strike Point的变化，供客户端显示伤害和治疗用
		PACKET_GC_TARGET_LIST_AND_HIT_FLAGS,						//目标列表和击中与否，用于客户端演示子弹和击中与否
		PACKET_GC_PACKAGE_SWAPITEM,									//交换包裹里的两个物品的结果
		PACKET_GC_STALLAPPLY,										//服务器通知客户端申请在此处摆摊
	/* ID:150 */PACKET_GC_STALLESTABLISH,							//通知客户端在此处摆摊
		PACKET_GC_STALLOPEN,										//摊位物品列表摊位信息
		PACKET_GC_STALLADDITEM,										//告诉客户端向摊位中加物品
		PACKET_GC_STALLREMOVEITEM,									//通知客户器从摊位中拿出物品
		PACKET_GC_STALLITEMPRICE,									//通知服务器从摊位中的物品改变售价
		PACKET_GC_STALLBUY,											//通知客户端购买店铺物品
		PACKET_GC_STALLCLOSE,										//通知客户端自己关闭店铺
		PACKET_GC_STALLERROR,										//通知摆摊错误
		PACKET_GC_BBSMESSAGES,										//留言板更新
		PACKET_GC_RELATION,											//游戏服务器向客户端发送好友相关消息
	/* ID:160 */PACKET_GC_GUILD,									//帮会消息
		PACKET_GC_GUILDLIST,										//返回帮会列表(UCHAR, {GuildID_t,NAME,Level,UserCount,Status})
		PACKET_GC_GUILDERROR,										//返回帮会操作错误(enum)
		PACKET_GC_GUILDRETURN,										//返回帮会操作结果(enum)
		PACKET_GC_GUILDBASEINFO,									//帮会基本信息
		PACKET_GC_GUILDMEMBERS,										//帮众信息
		PACKET_GC_GUILDAUTHORITY,									//帮会权限表
		PACKET_GC_ITEMSYNCH,										//物品移动消息
		PACKET_GC_ITEMLIST,											//发送物品列表给客户端
		PACKET_GC_TEAM_LIST,										//返回队员列表
	/* ID:170 */PACKET_GC_NEWSPECIAL,								//创建一个SpecialObj到客户端
		PACKET_GC_UICOMMAND,										//发送客户端的某个用户接口命令
		PACKET_GC_SPLITITEMRESULT,									//拆分物品
		
		PACKET_GC_SPECIAL_OBJ_ACT_NOW,								//特殊对象演示特效或动作
		PACKET_GC_SPECIAL_OBJ_FADE_OUT,								//特殊对象死亡或解体
		PACKET_GC_PLAYERSHOPERROR,									//玩家商店的出错信息
		PACKET_GC_PLAYERSHOPAPPLY,									//服务器通知客户端创建玩家商店所需的判定信息
		PACKET_GC_PLAYERSHOPESTABLISH,								//玩家商店是否建立成功
		PACKET_GC_PLAYERSHOPACQUIRESHOPLIST,						//服务器通知客户端创建玩家商店所需的判定信息
	/* ID:180 */PACKET_GC_PACKUP_PACKET,							//返回整理背包的结果
		PACKET_GC_PLAYERSHOPONSALE,									//通知客户端商品上下架
		PACKET_GC_PLAYERSHOPMONEY,									//通知客户端金钱存取

		PACKET_GC_PLAYERSHOPOPENSTALL,								//开张或关闭柜台
		PACKET_GC_REMOVEPET,										//修改用户设置数据
		PACKET_GC_PETPLACARDLIST,									//宠物公告板数据
		PACKET_GC_CITYERROR,										//客户端的城市错误信息
		PACKET_GC_CITYNOTIFY,										//客户端的城市通知
		PACKET_GC_CITYATTR,											//server把城市属性刷到客户端
	/* ID:190 */PACKET_GC_NEWPET,									//有新的宠物进入自己的视野范围
		PACKET_GC_NEWPET_DEATH,										//创建死亡的宠物
		PACKET_GC_NEWPET_MOVE,										//创建移动的宠物
		PACKET_GC_MINORPASSWD,										//二级密码

		PACKET_GC_PLAYERSHOPSALEOUT,								//盘出商店
		PACKET_GC_PLAYERSHOPBUYSHOP,								//盘入此店
		PACKET_GC_CHARSTOPACTION,									//停止Action逻辑
		PACKET_GC_GUILDAPPLY,										//申请建立工会
		PACKET_GC_PRIVATEINFO,										//玩家资料（刷给客户端）
	/* ID:200 */PACKET_GC_WORLDTIME,								//Server->Client 刷新世界时间
		PACKET_GC_CHARACTION,										//做一个动作
		PACKET_GC_CHARMODIFYACTION,									//干扰动作的执行
		PACKET_GC_PLAYER_CALLOF,									//邀请去某地
		PACKET_GC_FINGER,											//查找玩家
		PACKET_GC_PLAYERSHOPRECORDLIST,								//记录列表
		PACKET_GC_PLAYERSHOPUPDATEPARTNERS,							//更新合伙人列表
		PACKET_GC_PLAYERSHOPUPDATEFAVORITE,							//根据新的收藏家内容刷新商店列表
		PACKET_GC_PLAYERSHOPTYPE,									//通知客户端改变商店类型
		PACKET_GC_PLAYERSHOPSTALLSTATUS,							//向服务器请求改变某个柜台状态
	/* ID:210 */PACKET_GC_CHARDOACTION,								//让某角色做一个指定动作
		PACKET_GC_ADDLOCKOBJ,										//返回请求密码保护的结果
		PACKET_GC_NOTIFYRMB,										// 
		PACKET_GC_MISSIONDESC,										//返回任务描述
		PACKET_GC_FIRSTLOGIN,										//玩家第一次登录
		PACKET_GC_SYSTEMMSG,										//Server向Client发送系统消息
		PACKET_GC_MAXCOUNT,											//所有GC包的个数
/*------------------------GC-------------------------------------------------------------------------------------------*/

/*------------------------LC-------------------------------------------------------------------------------------------*/
		aaPACKET_LC_RETLOGIN = 400,									//Login 返回客户端的请求结果
	/* ID:401*/PACKET_LC_RETCHARLIST,								//返回角色列表
		PACKET_LC_STATUS,											//返回客户端当排队状态

		PACKET_LC_RETCONNECT,										//Login返回Client连接请求结果
		PACKET_LC_MAXCOUNT,											//所有LC包的个数
/*------------------------LC-------------------------------------------------------------------------------------------*/

/*------------------------CL-------------------------------------------------------------------------------------------*/
		aaaPACKET_CL_ASKLOGIN = 450,									//客户端请求Login登录
	/* ID:451*/PACKET_CL_ASKCHARLIST,								//请求角色列表

		PACKET_CL_CONNECT,											//Client请求Login连接
/*------------------------CL-------------------------------------------------------------------------------------------*/

/*------------------------CG、GW、WG、SS、LB、BL、LW、WL---------------------------------------------------------------*/
		PACKET_CG_TEST = 500,
	/* ID:501 */
		PACKET_CG_HEARTBEAT ,										//心跳消息

		PACKET_CG_LEAVESCENE ,										//客户端试图离开某个场景时发给服务器的请求消息
		PACKET_CG_ENVREQUEST ,										//客户端请求服务器发送周围环境信息

		PACKET_CG_CHARASKEQUIPMENT,									//获取简单装备表
		PACKET_CG_REQLEVELUP,										//请求升级
		PACKET_CG_REQMANUALATTR,									//请求点数分配
		PACKET_CG_REQRESETATTR,										//洗点请求
	/* ID:511 */PACKET_CG_MYEQUIPMENT,								//废弃
		PACKET_CG_OTHEREQUIPMENT,									//废弃
		PACKET_CG_ASKDETAILATTRIB ,									//请求更新当前主角属性
		PACKET_CG_ASKDETAILEQUIPMENTLIST,							//请求更新当前主角装备列表
		PACKET_CG_ASKDETAILSKILLLIST,								//请求更新当前主角技能列表
		PACKET_CG_ASKDETAILSUBEFFECTLIST,							//请求更新当前主角附加属性列表
		PACKET_CG_ASKMYBAGLIST,										//请求刷新当前背包
		PACKET_CG_CHARIDLE,											//通知SERVER进入IDLE状态
		PACKET_CG_CHARJUMP,											//通知SERVER跳跃一次

	/* ID:521 */PACKET_CG_MOVE ,									//废弃
		PACKET_CG_CHARUSESKILL,										//通知SERVER使用技能
		PACKET_CG_ATTACK ,											//废弃
		PACKET_CG_SKILL ,											//废弃
		PACKET_CG_OPENITEMBOX,										//打开Obj_ItemBox
		PACKET_CG_PICKBOXITEM,										//捡取Obj_ItemBox里的一件物品
		PACKET_CG_USEEQUIP,											//装配包裹里的装备
		PACKET_CG_UNEQUIP,											//卸下装备
		PACKET_CG_USEITEM,											//使用道具
		PACKET_CG_DISCARDITEM,										//丢弃包裹里的物品
	/* ID:531 */PACKET_CG_DISCARDEQUIP,								//丢弃身上装备
		PACKET_SS_CONNECT ,											//服务器之间内网连接时候的第一个通知消息
		PACKET_GS_ASKDATA ,											//向源服务器端程序要求得到Player数据
		PACKET_SG_RETDATA ,											//向GameServer端程序发送用户数据
		PACKET_GW_ASKUSERDATA ,										//向世界数据服务器要求用户资料
		PACKET_WG_RETUSERDATA ,										//返回用户资料信息
		PACKET_GW_ASKCHANGESCENE ,									//向世界数据服务器发送用户资料，要求转移场景
		PACKET_WG_RETCHANGESCENE ,									//返回转移场景结果信息
		PACKET_GW_NOTIFYUSER ,										//游戏服务器通知世界服务器用户状态需要改变
		PACKET_WG_NOTIFYUSER ,										//世界服务器通知游戏服务器用户状态变化
	/* ID:541 */PACKET_CG_COMMAND ,									//客户端向服务器发送游戏修改指令

		PACKET_CG_ASKITEMINFO,										//请求某件物品的详细信息
		PACKET_CG_ASKDETAILEQUIPLIST,								//请求自身装备的详细信息
		PACKET_CG_CHAT,												//说话
		PACKET_CG_ASKDETAILXINFALIST,								//请求更新当前主角心法列表
		PACKET_CG_USEGEM,											//使用宝石
		PACKET_CG_REMOVEGEM,										//卸载宝石
		PACKET_CG_USEEQUIPSKILL,							
	/* ID:551 */PACKET_CG_USEABILITY,								//有配方的生活技能指令
		PACKET_CG_TEAMINVITE,										//邀请组队
		PACKET_GW_TEAMINVITE,										//
		PACKET_WG_TEAMERROR,										//
		PACKET_WG_TEAMRESULT,										//
		PACKET_WG_NOTIFYTEAMINFO,									//
		PACKET_WG_TEAMASKINVITE,									//
		PACKET_CG_TEAMRETINVITE,									//组队回应
		PACKET_GW_TEAMRETINVITE,									//
		PACKET_WG_TEAMLEADERASKINVITE,								//
	/* ID:561 */PACKET_CG_TEAMLEADERRETINVITE,						//队长回应
		PACKET_GW_TEAMLEADERRETINVITE,								//
		PACKET_CG_TEAMLEAVE,										//离队
		PACKET_GW_TEAMLEAVE,										//
		PACKET_CG_TEAMDISMISS,										//解散队伍
		PACKET_GW_TEAMDISMISS,										//
		PACKET_CG_TEAMKICK,											//踢除队员
		PACKET_GW_TEAMKICK,											//
		PACKET_CG_TEAMAPPLY,										//加入队伍申请
		PACKET_GW_TEAMAPPLY,										//
	/* ID:571 */PACKET_WG_TEAMASKAPPLY,								//
		PACKET_GW_TEAMRETAPPLY,										//
		PACKET_CG_TEAMRETAPPLY,										//
		PACKET_CG_ASKDETAILABILITYINFO, 							//客户端玩家的生活技能信息
		PACKET_CG_TEAMAPPOINT ,										//任命新队长
		PACKET_GW_TEAMAPPOINT ,										//
		PACKET_CG_ABILITYGAMBLE,									//生活技能无配方合成指令
		PACKET_CG_ASK_COOLDOWN_UPDATE,								//客户端请求更新冷却时间信息 --现在不用了.
		PACKET_CG_DOEVENT,											//客户端选择事件列表中的某项执行
		PACKET_CG_MISSIONACCEPT ,									//接受任务
	/* ID:581 */PACKET_CG_MISSIONREFUSE ,							//拒绝任务
		PACKET_CG_MISSIONABANDON ,									//放弃任务
		PACKET_CG_MISSIONCONTINUE ,									//继续任务
		PACKET_CG_MISSIONSUBMIT ,									//递交任务
	
		PACKET_CG_ASKMISSIONLIST ,									//任务列表查询
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
		PACKET_CG_GEM_COMPOUND,										//宝石合成消息
		//PACKET_GW_ASKMAIL ,											// 
		//PACKET_WG_NOTIFYMAIL ,										//
		PACKET_CG_QUERYITEMBOXSTAGE,								//请求Itembox外观
		PACKET_CG_ASKTEAMINFO,										//请求队伍信息
		PACKET_GW_ASKTEAMINFO,										//请求队伍信息
		PACKET_CG_ASKTEAMMEMBERINFO,								//请求队友信息
		PACKET_CG_LOCK_TARGET,										//玩家锁定目标
	/* ID:611 */PACKET_GW_ASKTEAMMEMBERINFO,						//请求队伍信息
		PACKET_WG_TEAMMEMBERINFO,									//返回队友信息
		PACKET_CG_SHOPBUY,											//玩家从商品列表选择购买的物品
		PACKET_CG_SHOPSELL,											//玩家从商品列表选择要卖的物品
		PACKET_CG_SHOPREPAIR,										//通知服务器修理物品
		PACKET_CG_SHOPCLOSE,										//通知客户端交易窗口关闭关闭
		PACKET_CG_ASKJOINMENPAI,									//加入门派
		PACKET_CG_ASKSTUDYXINFA,									//请求学习某个某级心法
		PACKET_CG_ASKSTUDYABILITY,									//向服务器提交请求学习生活技能的消息
		PACKET_CG_CHARALLTITLES,									//客户端向服务器请求此人所有的称号
	/* ID:621 */PACKET_CG_CHARUPDATECURTITLE,						//服务器通知客户端此人所有的称号
		PACKET_CG_ASK_ACTIVETIME_UPDATE,							//客户端请求更新技能有效时间信息
		PACKET_GW_TEAMMEMBERENTERSCENE,								//队员进入新场景
		
		
		PACKET_CG_BANKREMOVEITEM,									//通知服务器从银行中移除物品
		PACKET_CG_BANKSWAPITEM,										//通知服务器从银行中与背包或装备栏中交换物品
		
		PACKET_CG_BANKCLOSE,										//通知服务器关闭此人银行
		PACKET_CG_EXCHANGEAPPLYI,									//交易答复
	/* ID:631 */PACKET_CG_EXCHANGEREPLYI,							//交易答复请求
		PACKET_CG_EXCHANGESYNCHLOCK,								//交易同步锁
		PACKET_CG_EXCHANGESYNCHITEMII,								//交易同步物品
		PACKET_CG_EXCHANGESYNCHMONEYII,								//交易同步金钱
		PACKET_CG_EXCHANGEOKIII,									//交易同意消息
		PACKET_CG_EXCHANGECANCEL,									//交易取消
		PACKET_GW_LEVEUP,											//队员升级，新级别刷新到 World 备考
		PACKET_CG_PLAYER_DIE_RESULT,								//主角死亡的操作结果
		PACKET_GW_ASKSCENEDATA,										//游戏场景向世界数据服务器请求场景附加信息
		PACKET_WG_RETSCENEDATA,										//世界数据服务器向场景发送场景附加信息
	/* ID:641 */PACKET_GG_SCENENOTIFY,								//场景通知消息
		PACKET_CG_SET_PETATTRIB,									//通知服务器，更改宠物属性
		PACKET_CG_MANIPULATEPET,									//操作宠物请求,如召唤,收回,放生等操作
		PACKET_CG_ASK_TEAMFOLLOW,									//队长请求进入组队跟随
		PACKET_CG_STOP_TEAMFOLLOW,									//某队员（长）停止队伍跟随状态
		PACKET_CG_RETURN_TEAMFOLLOW,								//队员回复是否进入组队跟随状态
		PACKET_GW_ENTER_TEAMFOLLOW,									//某队员进入队伍跟随状态
		PACKET_GW_STOP_TEAMFOLLOW,									//某队员停止队伍跟随状态
		PACKET_WG_TEAMFOLLOW_LIST,									//发送组队跟随列表
		PACKET_CG_MISSIONCHECK,										//验证任务是否已经完成
	/* ID:651 */PACKET_CG_DISPEL_BUFF,								//客户端请求取消持续性效果
		PACKET_CG_CHAR_STOP_LOGIC,									//客户端请求中止当前逻辑
		PACKET_CG_PACKAGE_SWAPITEM,									//要求交换包裹里的两个物品
		PACKET_CG_STALLAPPLY,										//向服务器申请在此处摆摊
		PACKET_CG_STALLESTABLISH,									//客户端接受摊位费与税费
		PACKET_CG_STALLOPEN,										//向服务器请求摊位物品列表
		PACKET_CG_STALLADDITEM,										//通知服务器向摊位中加物品
		PACKET_CG_STALLREMOVEITEM,									//通知服务器从摊位中拿出物品
		PACKET_CG_STALLITEMPRICE,									//通知服务器从摊位中的物品改变售价
		PACKET_CG_STALLSHOPNAME,									//通知服务器店铺改名
	/* ID:661 */PACKET_CG_STALLBUY,									//通知服务器购买店铺物品
		PACKET_CG_STALLCLOSE,										//通知服务器自己关闭店铺
		PACKET_CG_BBSSYCHMESSAGES,									//留言板更新
		PACKET_CG_BBSAPPLY,											//留言板更新
		PACKET_CG_RELATION,											//客户端向游戏服务器发送好友相关消息
		PACKET_GW_RELATION,											//游戏服务器向世界数据服务器发送好友相关消息

		PACKET_GW_RELATION_ENEMY,									//游戏服务器向世界数据服务器发送仇人相关的消息

		PACKET_WG_RELATION,											//世界数据服务器向游戏服务器发送好友相关消息

		PACKET_CG_GUILD,											//帮会消息
		PACKET_GW_GUILD,											//帮会消息
		PACKET_WG_GUILD,											//帮会消息
	/* ID:671 */PACKET_WG_GUILDLIST,								//返回帮会列表(PlayerID_t, UCHAR, {GuildID_t,NAME,Level,UserCount,Status})
		PACKET_WG_GUILDERROR,										//返回帮会操作错误(PlayerID_t, enum)
		PACKET_WG_GUILDRETURN,										//返回帮会操作结果(PlayerID_t, enum)
		PACKET_WG_GUILDBASEINFO,									//帮会基本信息
		PACKET_WG_GUILDMEMBERS,										//帮众信息
		PACKET_WG_GUILDAUTHORITY,									//帮会权限表
		PACKET_CG_ITEMSYNCH,										//物品移动消息
		PACKET_LB_ASKAUTH,											//Login 请求BillingSystem验证
		PACKET_BL_RETAUTH,											//BillingSystem 返回验证结果
		PACKET_LW_ASKCHARLOGIN,										//请求角色登录

		PACKET_LW_NOTIFY_CHARCHANGE,								//角色变动通知(新增/删除)

	/* ID:681 */PACKET_WL_RETCHARLOGIN,								//World允许角色登录
		PACKET_WG_TEAM_LIST,										//返回队员列表
		PACKET_CG_EXECUTESCRIPT,									//请求执行服务器端的某个脚本函数
		PACKET_SS_SCENEPLAYERCOUNT,									//世界数据服务器通知游戏服务器和登陆服务器场景中的人数信息
		PACKET_CG_SPLITITEM,										//拆分物品
		PACKET_CG_PLAYERSHOPAPPLY,									//向服务器申请创建玩家商店
		PACKET_CG_PLAYERSHOPESTABLISH,								//客户确定判定信息，递交最后申请
		PACKET_CG_PLAYERSHOPACQUIRESHOPLIST,						//向服务器申请创建玩家商店
		PACKET_CG_PLAYERSHOPACQUIREITEMLIST,						//客户确定判定信息，递交最后申请
		PACKET_GW_COMMAND,											//需要世界数据服务器处理的GM指令
	/* ID:691 */PACKET_CG_PACKUP_PACKET,							//请求整理背包
		PACKET_CG_PLAYERSHOPONSALE,									//通知服务器商品上下架
		PACKET_CG_PLAYERSHOPBUYITEM,								//通知服务器购买商品
		PACKET_CG_PLAYERSHOPMONEY,									//通知服务器金钱存取


		PACKET_CG_PLAYERSHOPNAME,									//修改玩家商店店名
		PACKET_CG_PLAYERSHOPDESC,									//修改玩家商店的描述
		PACKET_CG_PLAYERSHOPOPENSTALL,								//开张或关闭柜台
		//PACKET_GW_BATCHMAIL,										//发送批量消息
	/* ID:701 */PACKET_GW_CITYAPPLYNEWCITY,							//向World请求申请建立新的城市
		PACKET_WG_CITYAPPLYNEWCITY,									//回复Server请求申请建立新的城市
		PACKET_WG_CITYERROR,										//回复Server城市错误信息
		PACKET_WG_CITYATTR,											//world刷新城市属性
		PACKET_CG_CITYASKATTR,										//向服务器请求城市属性
		PACKET_GW_CITYASKINITINFO,									//启动时向服务器申请城市初始化信息
		PACKET_GW_CITYCLOSE,										//关闭城市
		PACKET_GW_CITYCLOSESUCCESS,									//关闭城市成功
		PACKET_WG_CITYCLOSE,										//关闭城市成功
		PACKET_WG_CITYCLOSESUCCESS,									//关闭城市成功
	/* ID:711 */PACKET_WG_CITYINITINFO,								//请求城市信息
		PACKET_GW_CITYOPT,											//城市操作
		PACKET_CG_ISSUEPETPLACARD,									//发布宠物公告
		PACKET_CG_STALLFIRSTPAGE,									//摆摊的初始页面
		PACKET_CG_MINORPASSWD,										//二级密码
		PACKET_CG_CHARPOSITIONWARP,									//位置偏差发往服务器
		PACKET_CG_PLAYERSHOPSALEOUT,								//盘出商店
		PACKET_CG_PLAYERSHOPBUYSHOP,								//盘入此店
		PACKET_CG_GUILDAPPLY,										//申请建立工会
		PACKET_CG_GUILDJOIN,										//申请加入工会
	/* ID:721 */PACKET_CG_GUILDASKMEMBERINFO,						//察看工会成员
		PACKET_GW_CHANGEMENPAI,										//改变门派
		PACKET_GW_UPDATETITLE,										//更新称号
		PACKET_CG_ASKPRIVATEINFO,									//玩家资料（请求）
		PACKET_CG_APPLYPRIVATEINFO,									//玩家修改玩家资料
		PACKET_WG_WORLDTIME,										//World->Server 刷新世界时间
		PACKET_CG_CHARSIT,											//玩家坐下
		PACKET_CG_PLAYER_CALLOF_RESULT,								//邀请去某地的操作结果
		PACKET_GW_CALLOFHUMAN,										//拉人的消息
		PACKET_WG_CALLOFHUMAN,										//拉人的消息
	/* ID:731 */PACKET_CG_STALL_DEFAULT_PAGE,						//摆摊缺省页面提交
		PACKET_CG_SETMOODTOHEAD,									//设置心情显示
		PACKET_CG_FINGER,											//查找玩家
		PACKET_GW_FINGER,											//查找玩家的结果
		PACKET_WG_FINGER,											//查找玩家的结果
		PACKET_CG_PLAYERSHOPASKFORRECORD,							//请求玩家商店交易记录，或管理记录
		PACKET_CG_PLAYERSHOPPARTNER,								//合作伙伴
		PACKET_CG_PLAYERSHOPFAVORITE,								//加入或删除收藏夹
		PACKET_CG_PLAYERSHOPTYPE,									//请求服务器改变商店类型
		PACKET_CG_PLAYERSHOPSIZE,									//向服务器请求改变商店大小
	/* ID:741 */PACKET_CG_CGASKLOCKOBJ,								//请求锁定一个Obj
		PACKET_CG_CHARMOODSTATE,									// 表情事件
		PACKET_GW_HEARTBEAT,										//发送玩家的心跳消息给World
		PACKET_CG_MISSIONDESC,										//得到任务描述
		PACKET_CG_FIRSTLOGIN,								
		PACKET_LW_ASKDELETECHAR,									//请求删除角色
		PACKET_WL_RETDELETECHAR,									//World允许删除角色
		PACKET_BW_CONNECT,											//Web服务器与Billing服务器第一次验证KEY的消息
		PACKET_BW_VALIDATEUSER,										//Billing服务器请求Web验证用户名与密码
		PACKET_WB_RET_VALIDATEUSER,									//Billing服务器请求Web验证用户名与密码
		PACKET_WG_SYSTEMMSG,								//World向Server发送系统消息
		PACKET_GW_SYSTEMMSG,										//Server向World发送系统消息



		PACKET_LoginCharPacketBegin		= 0x1100,

		PACKET_CS_ASKLOGIN				= PACKET_LoginCharPacketBegin + 151,				//Ask Login
	
																							//请求得到用户设置数据
	

//------Controller = 5  NPC 交易系统   ---------------------------------------
		//NPC和交易系统
		// ServerSide
		PACKET_NPC_SHOP_BEGIN			= 0x1400,
		PACKET_GC_SCRIPTCOMMAND			= PACKET_NPC_SHOP_BEGIN + 1,									//脚本到客户端的指令
		PACKET_GC_CHARMISSIONSTATE      = PACKET_NPC_SHOP_BEGIN + 3,                                    //返回任务状态
		PACKET_ZGC_NPCSHOPLIST			= PACKET_NPC_SHOP_BEGIN + 9,									//Lua脚本调用:NPC贩卖商店和列表
		PACKET_zGC_SHOPBUY				= PACKET_NPC_SHOP_BEGIN + 10,
		PACKET_zGC_SHOPSELL				= PACKET_NPC_SHOP_BEGIN + 11,
		PACKET_GC_RECIPE				= PACKET_NPC_SHOP_BEGIN + 12,									//合成物品
		PACKET_GC_TRADESHOP				= PACKET_NPC_SHOP_BEGIN + 30,								//贸易商店开关
		PACKET_GC_TRADECONTAINER		= PACKET_NPC_SHOP_BEGIN + 31,								//贸易，放入购物篮
		PACKET_GC_TRADEBALANCE			= PACKET_NPC_SHOP_BEGIN + 32,								//贸易，结算
		PACKET_GC_POPITEMS				= PACKET_NPC_SHOP_BEGIN + 33,								//城市流行商品

        // DGH added [10/29/2010 dgh]
		PACKET_GC_NOTIFY_RECIPE_ID      = PACKET_NPC_SHOP_BEGIN + 40,								//返回 加工配料单ID

		//ClientSide
		PACKET_CG_CHARDEFAULTEVENT      = PACKET_NPC_SHOP_BEGIN + 120 +1 ,								//缺省事件
		PACKET_CG_EVENTREQUEST			= PACKET_NPC_SHOP_BEGIN + 120 +2 ,								//查询一个脚本事件
		PACKET_zCG_SHOPBUY				= PACKET_NPC_SHOP_BEGIN + 130,
		PACKET_zCG_SHOPSELL				= PACKET_NPC_SHOP_BEGIN + 131,
		PACKET_CG_RECIPE				= PACKET_NPC_SHOP_BEGIN + 132,									//合成物品
		PACKET_CG_TRADECONTAINER		= PACKET_NPC_SHOP_BEGIN + 120 + 31,								//贸易，放入购物篮
		PACKET_CG_TRADEBALANCE			= PACKET_NPC_SHOP_BEGIN + 120 + 32,								//贸易，结算
//--------------------------交易系统结束---------------------------------------


		//战斗 15/6
		PACKET_BATTLE_BEGIN				= 0x1500,	//6 + 15
		PACKET_GC_RETBATTLESTART		= PACKET_BATTLE_BEGIN + 1,							//战斗开始
		PACKET_GC_RETROUNDBEING			= PACKET_BATTLE_BEGIN + 2,							//回合开始，客户端倒计时
		PACKET_GC_BATTLE_ROUND_RESULT	= PACKET_BATTLE_BEGIN + 3,							//战斗回合结果包
		PACKET_GC_BATTLE_FINA_RESULT	= PACKET_BATTLE_BEGIN + 4,							//战斗整场结果包

		PACKET_GC_RET_CC_REQUEST		= PACKET_BATTLE_BEGIN + 5,							//客户端间请求包

		PACKET_CG_ASKBATTLESTART		= PACKET_BATTLE_BEGIN + 121,						//战斗开始
		PACKET_CG_ASKROUNDBEGIN			= PACKET_BATTLE_BEGIN + 122,						//回合开始，客户端倒计时
		PACKET_CG_BATTLE_ACTION			= PACKET_BATTLE_BEGIN + 123,						//返回玩家攻击指令

		PACKET_CG_ASK_CC_REQUEST		= PACKET_BATTLE_BEGIN + 125,							//客户端间请求包


		//组队 16/7
		PACKET_TeamPacketBegin			= 0x1600,
		PACKET_zGC_TEAMASKINVITE		= PACKET_TeamPacketBegin + 1,						//客户端收到邀请加入队伍
		PACKET_zGC_TEAMRESULT			= PACKET_TeamPacketBegin + 2,						//队伍信息返回，包括增加队员，切换队长，退队，踢人，解散等
		PACKET_zGC_TEAMERROR			= PACKET_TeamPacketBegin + 10,						//组队中的错误

		PACKET_zCG_TEAMINVITE			= PACKET_TeamPacketBegin + 121,						//邀请他人加入队伍
		PACKET_zCG_TEAMRETINVITE		= PACKET_TeamPacketBegin + 122,						//收到组队后的回应
		PACKET_zCG_TEAMAPPOINT			= PACKET_TeamPacketBegin + 123,						//指定新队长
		PACKET_zCG_TEAMLEAVE			= PACKET_TeamPacketBegin + 124,						//退出队伍
		PACKET_zCG_TEAMDISMISS			= PACKET_TeamPacketBegin + 125,						//解散队伍
		PACKET_zCG_TEAMKICK				= PACKET_TeamPacketBegin + 126,						//踢人

		//船坞管理 17/8
		PACKET_ShipYardManageBegin      = 0x1700,
		PACKET_GC_RETSHIPLIST			= PACKET_ShipYardManageBegin + 1,					//返回船坞信息
		PACKET_GC_RETSHIPINFO			= PACKET_ShipYardManageBegin + 2,					//返回舰船信息
		PACKET_GC_RETSETCURSHIP         = PACKET_ShipYardManageBegin + 3,                   //返回设置当前舰船
		PACKET_GC_RETSELLSHIP			= PACKET_ShipYardManageBegin + 4,                   //返回出售舰船
		PACKET_GC_RETWARESHIPITEM		= PACKET_ShipYardManageBegin + 5,                   //返回装备舰船道具
		PACKET_GC_TAKEOFFALLITEM        = PACKET_ShipYardManageBegin + 6,					//一键卸载舰船装备的道具
		PACKET_GC_RETADDSHIPYARD		= PACKET_ShipYardManageBegin + 10,					//返回开通新船坞
		PACKET_GC_RETFIXSHIPCOST		= PACKET_ShipYardManageBegin + 11,					//返回修理舰船的费用
		PACKET_GC_RETFIXSHIP			= PACKET_ShipYardManageBegin + 12,					//返回修理舰船

		PACKET_zCG_ASKSHIPLIST          = PACKET_ShipYardManageBegin + 121,                 //获取船坞信息
		PACKET_zCG_SETCURSHIP           = PACKET_ShipYardManageBegin + 123,                 //设置用户当前舰船
		PACKET_CG_SELLSHIP				= PACKET_ShipYardManageBegin + 124,                 //出售舰船
		PACKET_CG_ASKWARESHIPITEM		= PACKET_ShipYardManageBegin + 120 + 5,             //装备舰船道具
		PACKET_CG_TAKEOFFALLITEM        = PACKET_ShipYardManageBegin + 120 + 6,             //一键卸载舰船装备的道具
		PACKET_CG_ASKADDSHIPYARD		= PACKET_ShipYardManageBegin + 120 + 10,            //开通新船坞 
		PACKET_CG_ASKFIXSHIP			= PACKET_ShipYardManageBegin + 120 + 12,            //确认修理舰船

		

		//背包道具管理 18/9      added by 钟雷 2010 6-24--------------------------------
		//更改--买卖道具并入到NPC操作中
		//需求--装备道具需要舰船装备道具接口
		//后台发往前台
		PACKET_ITEM_BEGIN               = 0x1800,     //24
		PACKET_zGC_SETITEM              = PACKET_ITEM_BEGIN	+  1,                           //设定道具   注:前台使用Index判断是Bag,Cargo,Bank
		PACKET_zGC_DELITEM				= PACKET_ITEM_BEGIN +  2,                           //删除道具
		PACKET_zGC_USEITEM				= PACKET_ITEM_BEGIN +  4,							//使用道具结果  GCUserItemResult
		PACKET_zGC_SPLITITEM			= PACKET_ITEM_BEGIN +  5,                           //返回的拆分道具结果 GCSplitItemResult
		PACKET_zGC_SWAPITEM				= PACKET_ITEM_BEGIN +  6,							//返回交换道具位置结果 GCPackage_SwapItem
		PACKET_zGC_RETASKMYBAG          = PACKET_ITEM_BEGIN +  10,                          //返回背包,Cargo,Bank道具列表  GCMyBagList
		PACKET_zGC_SETCONTAINERSIZE		= PACKET_ITEM_BEGIN +  11,							//购买扩展背包,购买扩展仓库结果
		PACKET_GC_SETCARGOSIZE			= PACKET_ITEM_BEGIN +  12,							//设定Cargo大小


		PACKET_GC_BANKACQUIRELIST       = PACKET_ITEM_BEGIN +  21,							//银行中的物品发送给客户端
		PACKET_GC_BANKADDITEM           = PACKET_ITEM_BEGIN +  22,							//通知客户端加物品结果
		PACKET_GC_BANKITEMINFO          = PACKET_ITEM_BEGIN +  23,							//银行物品信息		
		PACKET_GC_BANKMONEY             = PACKET_ITEM_BEGIN +  24,  						//通知客户端存钱取钱结果
		PACKET_GC_ADDBANKCAPACITY       = PACKET_ITEM_BEGIN +  25,			                //增加银行的容量
		
		PACKET_zGC_SETITEMLIST			= PACKET_ITEM_BEGIN +  30,							//道具设定包,列表版
		PACKET_GC_CARGOACQUIRELIST		= PACKET_ITEM_BEGIN +  31,							//货舱中的物品发送给客户端
		
		PACKET_zGC_RECEIVEITEMINFO		= PACKET_ITEM_BEGIN +  40,							//提示收到物品信息

		PACKET_GC_RET_ITEM_EXTRA_INFO   = PACKET_ITEM_BEGIN +  46,                          //获取物品强化信息

		PACKET_zGC_TRANSFORM_RETURN			=	PACKET_ITEM_BEGIN	+	47,		//GCTransformItemRet
	
		

		//前台发往后台
		PACKET_zCG_USEITEM				= PACKET_ITEM_BEGIN +  120,                         //使用道具  CGUserItem
		PACKET_zCG_DROPITEM				= PACKET_ITEM_BEGIN +  121,                         //丢弃道具  CGDiscardItem
		PACKET_zCG_SPLITITEM            = PACKET_ITEM_BEGIN +  122,                         //拆分道具  CGSplitItem
		PACKET_zCG_EQUIPITEM            = PACKET_ITEM_BEGIN +  124,							//使用装备(装备指定背包内的装备类道具) CGUserEquip
		PACKET_zCG_SWAPITEM				= PACKET_ITEM_BEGIN +  125,							//交换道具位置 CGPackage_SWapItem
		PACKET_zCG_ASKMYBAG             = PACKET_ITEM_BEGIN +  130,							//获取当前用户背包信息 CGAskBagList
		PACKET_zCG_EXTBAG				= PACKET_ITEM_BEGIN +  131,                         //扩展当前用户背包   尚无
		PACKET_zCG_REORGNIZEBAG			= PACKET_ITEM_BEGIN +  132,							//整理当前用户背包   CGPackUpPacket
		

		PACKET_CG_BANKACQUIRELIST       = PACKET_ITEM_BEGIN +  120 + 21,					//向服务器获取存储物列表
		PACKET_CG_BANKADDITEM           = PACKET_ITEM_BEGIN +  120 + 22,					//通知服务器往银行中加物品
		PACKET_CG_BANKMONEY             = PACKET_ITEM_BEGIN +  120 + 24,					//通知服务器存钱取钱
		PACKET_CG_ADDBANKCAPACITY       = PACKET_ITEM_BEGIN +  120 + 25,                    //增加银行的容量
		PACKET_CG_CARGOACQUIRELIST		= PACKET_ITEM_BEGIN +  120 + 31,					//货舱中的物品发送给客户端


		PACKET_CG_ASK_ITEM_EXTRA_INFO   = PACKET_ITEM_BEGIN +  120 + 46,                     //获取物品强化信息
		PACKET_zCG_TRANSFORM_REQUEST	= PACKET_ITEM_BEGIN	+  120 + 47,				     //CGTransformItem

		//-----------------------------------航海背包End--------------------------------------


		//技能&天赋 1A/11
		PACKET_TALENT_SKILL_BEGIN		= 0x1A00,	//11 + 15
		PACKET_zGC_ASKSTUDYTALENT		= PACKET_TALENT_SKILL_BEGIN + 1,					//学习天赋返回
		PACKET_zGC_ASKSTUDYSKILL		= PACKET_TALENT_SKILL_BEGIN + 2,					//学习技能返回
		PACKET_zGC_DETAILTALENTLIST		= PACKET_TALENT_SKILL_BEGIN + 3,					//已学天赋（技能）返回
		//PACKET_zGC_DETAILSKILL			= PACKET_TALENT_SKILL_BEGIN + 4,					//已学技能返回
		PACKET_GC_MAPBUFF				= PACKET_TALENT_SKILL_BEGIN + 5,					//已学天赋（技能）返回
		PACKET_GC_GATHER_GOODS			= PACKET_TALENT_SKILL_BEGIN + 6,					//采集物品返回

		PACKET_zCG_ASKSTUDYTALENT		= PACKET_TALENT_SKILL_BEGIN + 121,					//学习天赋
		PACKET_zCG_ASKSTUDYSKILL		= PACKET_TALENT_SKILL_BEGIN + 122,					//学习技能
		PACKET_zCG_DETAILTALENTLIST		= PACKET_TALENT_SKILL_BEGIN + 123,					//请求已学天赋（技能）
		PACKET_CG_RESETTALENT			= PACKET_TALENT_SKILL_BEGIN + 124,					//重置天赋
		PACKET_CG_MAPBUFF				= PACKET_TALENT_SKILL_BEGIN + 125,					//请求地图buff
		PACKET_CG_GATHER_GOODS			= PACKET_TALENT_SKILL_BEGIN + 126,					//采集物品
		PACKET_CG_CANCEL_MAPBUFF		= PACKET_TALENT_SKILL_BEGIN + 127,					//取消地图buff


		//好友--------------------------------------
		PACKET_RELATION_OPT_BEGIN			= 0x1B00,	//12 + 15

		PACKET_zGC_RELATIONOPT		= PACKET_RELATION_OPT_BEGIN + 1,		//返回好友操作

		PACKET_zCG_RELATIONOPT		= PACKET_RELATION_OPT_BEGIN + 121,	//请求好友才做
		//------------------------------------------


////////////////////////////////////////////////////////////////////////
//     排行:  added by DGH
//          Controller：13 ( 0x1C00 )
///////////////////////////////////////////////////////////////////////
        PACKET_RANGE_DATA_BEGIN         = 0x1C00,// 13+15
//////////////////////////////////////////////////////////////
// Server responent
//////////////////////////////////////////////////////////////
        PACKET_GC_RANGE_DATA_RESPONENT   =  PACKET_RANGE_DATA_BEGIN + 1,		//返回排行数据
//////////////////////////////////////////////////////////////
// From client
/////////////////////////////////////////////////////////////
        PACKET_CG_RANGE_DATA_REQUEST			=  PACKET_RANGE_DATA_BEGIN + 1 + 120, //获取排行数据
		PACKET_CG_RANGE_DATA_QUERYBYNAME		=  PACKET_RANGE_DATA_BEGIN + 2 + 120, //查询指定玩家的排行


		PACKET_GW_GET_RANGELIST, // G-->W 获取玩家的排行数据
		PACKET_WG_GET_RANGELIST, // W-->G 返回玩家查询的排行数据

//-------------------------------公会操作开始---------------------------------------------------------
		//公会操作  0x1D00 / 14 ------------------- addedBy 钟雷 2010-7-2
		PACKET_GUILD_BEGIN				= 0x1D00,
		//基础操作
		//Server Side
		PACKET_zGC_GUILD			  =	 PACKET_GUILD_BEGIN + 1,  // 公会信息返回类 GCGuild
		PACKET_zGC_GUILDRETURN		  =	 PACKET_GUILD_BEGIN + 2,  // 公会操作返回类 GCGuildReturn
		PACKET_zGC_GUILDERROR		  =  PACKET_GUILD_BEGIN + 10, // 公会操作错误返回类 GCGuildError

	//Client Side
		PACKET_zCG_GUILDAPPLY		  =  PACKET_GUILD_BEGIN + 121,  // 客户端公会创建操作  GCGuildApply
		PACKET_zCG_GUILD			  =  PACKET_GUILD_BEGIN + 122,  // 客户端公会操作      CGGuild
		PACKET_zCG_GUILDJOIN		  =  PACKET_GUILD_BEGIN + 123,  // 客户端响应公会加入  CGGuildJoin
	

//------------------------------公会操作结束------------------------------------------------------------

		//舰船建造改造 0x1E00 / 15
		PACKET_SHIP_BUILD_BEGIN         = 0x1E00,
		PACKET_GC_RETBUILDSHIPINFO      = PACKET_SHIP_BUILD_BEGIN + 1,
		PACKET_GC_RETBUILDSHIP          = PACKET_SHIP_BUILD_BEGIN + 2,
		PACKET_GC_GETBUILDSHIP          = PACKET_SHIP_BUILD_BEGIN + 3,   
		PACKET_GC_RETRECASTSHIPINFO     = PACKET_SHIP_BUILD_BEGIN + 4,						 //舰船改造获取材料信息
		PACKET_GC_RETRECASTSHIP         = PACKET_SHIP_BUILD_BEGIN + 5,						 //舰船改造


		PACKET_CG_ASKBUILDSHIPINFO		= PACKET_SHIP_BUILD_BEGIN + 120 + 1,                 //获取建造舰船的信息
		PACKET_CG_ASKBUILDSHIP          = PACKET_SHIP_BUILD_BEGIN + 120 + 2,                 //建造舰船
		PACKET_CG_TAKEBUILDSHIP         = PACKET_SHIP_BUILD_BEGIN + 120 + 3,                 //领取建造的船只
		PACKET_CG_ASKRECASTSHIPINFO     = PACKET_SHIP_BUILD_BEGIN + 120 + 4,				 //舰船改造获取材料信息
		PACKET_CG_ASKRECASTSHIP         = PACKET_SHIP_BUILD_BEGIN + 120 + 5,				 //舰船改造



		PACKET_GW_SHIPBUILD ,																//游戏服务器通知世界服务器延时通知玩家
		PACKET_WG_SHIPBUILD ,

/************************************************************************/
/* 交易系统
	指令Controller 16
	指令Start     0x1F00
*/
/************************************************************************/
	    PACKET_EXCHANGE_BEGIN			= 0x1F00, //0x2000,

		//服务端发送
		PACKET_zGC_EXCHANGEAPPLY		= PACKET_EXCHANGE_BEGIN	+	1,			//其他玩家邀请玩家交易 GC_ExchangeApplyI
		PACKET_zGC_EXCHANGEESTABLISH	= PACKET_EXCHANGE_BEGIN	+	2,			//开始交易流程	GC_ExchangeEstablish
		PACKET_zGC_EXCHANGESYNC			= PACKET_EXCHANGE_BEGIN +	3,          //交易中道具,金钱改动同步 GC_ExchangeSynch
		PACKET_zGC_EXCHANGESYNCLOCK		= PACKET_EXCHANGE_BEGIN +   4,			//交易中对方按确认 GC_ExchangeSynchLock
		PACKET_zGC_EXCHANGECONFIRM		= PACKET_EXCHANGE_BEGIN +	5,			//交易中"交易"按钮的状态 GC_ExchangeSyncConfirm
		PACKET_zGC_EXCHANGESUCCESS		= PACKET_EXCHANGE_BEGIN +	10,			//交易成功		GC_ExchangeSuccess
		PACKET_zGC_EXCHANGECANCEL		= PACKET_EXCHANGE_BEGIN	+	15,			//对方取消交易 GC_ExchangeCancel
		PACKET_zGC_EXCHANGEERROR		= PACKET_EXCHANGE_BEGIN	+	20,			//交易中的错误提示


		//客户端发送
		PACKET_zCG_EXCHANGEAPPLY		= PACKET_EXCHANGE_BEGIN +   121,		//要求其他玩家交易 CGExchangeApplyI
		PACKET_zCG_EXCHANGEREPLY		= PACKET_EXCHANGE_BEGIN +	122,		//同意进行交易	 CGExchangeReply
		PACKET_zCG_EXCHANGESYNCITEM		= PACKET_EXCHANGE_BEGIN +	123,		//交易道具交替 CGExchangeSyncItemII
		PACKET_zCG_EXCHANGESYNCMONEY	= PACKET_EXCHANGE_BEGIN +	124,		//交易中金钱的变更 CGExchangeSyncMoneyII
		PACKET_zCG_EXCHANGESYNCLOCK		= PACKET_EXCHANGE_BEGIN	+	125,		//交易中点"确认"按钮 CGExchangeSynclock
		PACKET_zCG_EXCHANGEOK			= PACKET_EXCHANGE_BEGIN +	130,		//交易中点"交易"按钮 CGExchangeOkIII
		PACKET_zCG_EXCHANGECANCEL		= PACKET_EXCHANGE_BEGIN +	135,		//交易中点"取消"按钮,或者关闭交易界面 CGExchangeCancel

		//交易的超时
		PACKET_GW_EXCHANGETIMER			= PACKET_EXCHANGE_BEGIN +   200,
		PACKET_WG_EXCHANGETIMER,


/************************************************************************/
/* 交易系统结束                                                                     */
/************************************************************************/


//=======================================================================
//邮件系统：control = 17   added by DGH
//=======================================================================
 PACKET_MAIL_BEGIN = 0x2000,

 //后台回复指令
 PACKET_GC_MAIL			= PACKET_MAIL_BEGIN +1,//返回玩家邮件列表

 //PACKET_GC_READMAIL		= PACKET_MAIL_BEGIN+2,//读取未读邮件
 //PACKET_GC_DELETEMAIL	= PACKET_MAIL_BEGIN+3,//删除邮件（此指令已经存在，但对原指令进行覆盖！) 
 //PACKET_GC_MAIL			= PACKET_MAIL_BEGIN+4,//发送邮件后返回

 PACKET_GC_GETMAILGIFT	= PACKET_MAIL_BEGIN	+5, //提取邮件礼物
 PACKET_GC_NOTIFYMAIL   = PACKET_MAIL_BEGIN	+10,//通知玩家，当前新邮件可接收
 PACKET_GC_MAIL_RESULT  = PACKET_MAIL_BEGIN	+20,//邮件操作结果返回(发送，删除，设置标志)，返回错误码为0表示操作成功；

 //前台请求指令
 PACKET_CG_ASKMAIL      = PACKET_MAIL_BEGIN +1 +120,//获取邮件列表  
 PACKET_CG_SETMAILFLAG	= PACKET_MAIL_BEGIN +2 +120,//设置邮件标志(设置邮件未读标志)
 PACKET_CG_DELETEMAIL	= PACKET_MAIL_BEGIN +3 +120,//删除邮件
 PACKET_CG_MAIL			= PACKET_MAIL_BEGIN +4 +120,//发送新邮件
//提取邮件赠品
 PACKET_CG_GETMAILGIFT	= PACKET_MAIL_BEGIN +5 +120,//提取邮件礼物
//查询邮箱容量
PACKET_CG_MAILLISTSIZE	= PACKET_MAIL_BEGIN +6 +120,//获取邮箱容量(超过95封邮件时,报警)

 //world服务器与game服务器交互包
 //----------------------------------------
 //PACKET_CG_ASKMAIL 相关的包:
 PACKET_GW_ASKMAIL ,											// game server 向 world 获取邮件列表 

 PACKET_GW_READ_MAIL,                                           // G --> W :玩家读取新邮件(修改邮件在服务端的状态)

 PACKET_GW_DELETE_MAIL,											// G --> W :玩家删除邮件

 PACKET_WG_MAIL ,											    // world服务器通知game server 返回邮件列表

 PACKET_WG_NOTIFYMAIL ,                                         // world  向 game server 发送消息类邮件(登录后第一封消息邮件等) 
 //----------------------------------------
 PACKET_GW_MAIL ,                                               // game server 通知 world ,玩家发送新邮件;

 PACKET_GW_GET_PRESENT,                                         // GAME --> WORLD 提取邮件附件;

 PACKET_GW_CLEAR_MAIL_PARAM,									// game --> world 道具提取成功后，清除邮件参数;

 PACKET_WG_GET_PRESENT,											//WORLD --> GAME 实现附件提取操作

 PACKET_WG_MAIL_RESPONSE,                                       // WORLD 通知 SERVER 邮件操作结果(发送,删除,查看,提取)

 PACKET_GW_BATCHMAIL,											// 发送批量消息(给所有好友发送邮件) 

 PACKET_GW_MAILLISTSIZE	,										//向world请求当前玩家邮箱容量
 PACKET_WG_MAILLISTSIZE ,										//返回game当前玩家邮箱容量

//=======================================================================
//邮件结束	
//=======================================================================

//--商城系统-----Controller:18 -----------------------------------------------

		PACKET_MALL_BEGIN	=	0x2100,

		//服务端发送
		PACKET_zGC_MALLLIST		=	PACKET_MALL_BEGIN	+	1,	//GCMallList
		PACKET_zGC_MALLNOTICE	=	PACKET_MALL_BEGIN	+	2,	//GCMallNotice
		PACKET_zGC_MALLRESULT	=	PACKET_MALL_BEGIN	+	3,	//GCMallResult

		//客户端发送
		PACKET_zCG_MALLLIST		=	PACKET_MALL_BEGIN	+	121,	//CGMallList
		PACKET_zCG_MALLNOTICE	=	PACKET_MALL_BEGIN	+	122,	//CGMallNotice
		PACKET_zCG_MALLBUY		=	PACKET_MALL_BEGIN	+	123,	//CGMallBuy
		PACKET_zCG_MALLGIFT		=	PACKET_MALL_BEGIN	+	124,	//CGMallGift

//--商城系统结束--------------------------------------------------------


//=======================================================================
//任务相关 added by  oj 2010-8-9	
//=======================================================================
		PACKET_MISSION_BEGIN	=	0x2200,

		//服务端发送
		PACKET_zGC_ASKMISSIONLIST		=	PACKET_MISSION_BEGIN	+ 1,		//返回任务列表
		PACKET_zGC_MISSIONDESC			=	PACKET_MISSION_BEGIN	+ 2,		//任务详情		
		PACKET_zGC_MISSIONADD			=	PACKET_MISSION_BEGIN	+ 3,		//添加任务
		PACKET_zGC_MISSIONABANDON		=	PACKET_MISSION_BEGIN	+ 5,		//放弃任务
		PACKET_zGC_MISSIONMODIFY		=	PACKET_MISSION_BEGIN	+ 9,		//任务修改
		PACKET_zGC_MISSIONNOTIFYSTATE	=	PACKET_MISSION_BEGIN	+ 10,		//任务目标状态

//-----------------------------------------------------------------------

		//客户端发送
		PACKET_zCG_ASKMISSIONLIST		=	PACKET_MISSION_BEGIN	+	121,	//查询任务列表
		PACKET_zCG_MISSIONDESC			=	PACKET_MISSION_BEGIN	+	122,	//查询任务详情		
		PACKET_zCG_MISSIONACCEPT		=	PACKET_MISSION_BEGIN	+	123,	//接受任务
		PACKET_zCG_MISSIONREFUSE		=	PACKET_MISSION_BEGIN	+	124,	//拒绝任务
		PACKET_zCG_MISSIONABANDON		=	PACKET_MISSION_BEGIN	+	125,	//放弃任务
		PACKET_zCG_MISSIONCONTINUE		=	PACKET_MISSION_BEGIN	+	126,	//任务继续
		PACKET_zCG_MISSIONSUBMIT		=	PACKET_MISSION_BEGIN	+	128,	//完成任务


//=======================================================================
//任务结束		
//=======================================================================
		
//=======================================================================
//离线挂机	 Controller 20	zhonglei
//=======================================================================
	 PACKET_OFFLINE_BEGIN	=	0x2300,

	 //服务端发送
	 PACKET_zGC_RetAskOfflineExp	=		PACKET_OFFLINE_BEGIN	+	1,	//返回离线挂机的经验,时间
	 PACKET_zGC_RetWithdrawExp		=		PACKET_OFFLINE_BEGIN	+	2,	//返回提取离线挂机经验结果
//-----------------------------------------------------------------------
	// 客户端发送
	 PACKET_zCG_AskOfflineExp		=		PACKET_OFFLINE_BEGIN	+	121,	//请求离线挂机时间经验
	 PACKET_zCG_WithdrawExp			=		PACKET_OFFLINE_BEGIN	+	122,	//提取离线挂机经验

//=======================================================================
//离线挂机结束
//=======================================================================

//////////////////////////////////////////////////////////////////////////
//新手指南 Controller 21 DGH added
//  [11/19/2010 dgh]
//////////////////////////////////////////////////////////////////////////
        PACKET_GUIDE_STEP_BEGIN	= 0x2400,
		//服务器回包 
		PACKET_GC_GetGuideStep  = PACKET_GUIDE_STEP_BEGIN  +1,        //返回当前新手步骤号
		//客户端发送
		PACKET_CG_GuideStepSet  = PACKET_GUIDE_STEP_BEGIN   + 120 +1, //提交新手步骤


    



		PACKET_MAX																			//消息类型的最大值
	};
};


#endif

