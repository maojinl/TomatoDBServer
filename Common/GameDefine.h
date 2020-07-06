#ifndef __GAMEDEFINE_H__
#define __GAMEDEFINE_H__

//世界号最大值
#define MAX_WORLD 255

#define MAX_WORLD_USER	3000

//用户角色名字可以输入的最大值
#define MAX_CHARACTER_INPUTNAME 24

//GamePlayer管理器的上限
#define MAX_PLAYER 1024

#define MAX_CHARACTER_NAME 30

//玩家称号长度
#define MAX_CHARACTER_TITLE 34

//二级密码最短长度
#define MIN_PWD 4

//二级密码的最大长度 + 1
#define MAX_PWD 17

//用户帐号的最大值
#define MAX_ACCOUNT 16

//用户密码的最大值
#define MAX_PASSWORD 32

//ID最大长度
#define MAX_ID_LENGTH  24

#define MAX_SYSTEM_MSG_SIZE 10


#define DB_BAG_POS_START			(BASE_CONTAINER_OFFSET)					// 0
#define	DB_BAG_POS_END				(MAX_BAG_SIZE-1)		// 69

#define DB_EQUIP_POS_START			(MAX_BAG_SIZE+MAX_EXTBAG_SIZE)			// 200
#define DB_EQUIP_POS_END			(DB_EQUIP_POS_START+HEQUIP_NUMBER-1)	// 208

#define DB_CARGO_POS_START			(CARGO_CONTAINER_OFFSET)				// 300
#define DB_CARGO_POS_END			(MAX_CARGO_SIZE+CARGO_CONTAINER_OFFSET-1)	// 334

#define DB_TRADE_POS_START			(TRADE_CONTAINER_OFFSET)				// 350
#define DB_TRADE_POS_END			(MAX_TRADE_SIZE+TRADE_CONTAINER_OFFSET-1)	// 334

#define DB_BANK_POS_START			(BANK_CONTAINER_OFFSET)					// 400
#define DB_BANK_POS_END				(MAX_BANK_SIZE+DB_BANK_POS_START-1)		// 

#define DB_MAX_ITEMINFO				(DB_BANK_POS_END+1)

#define DB_RECEIVE_ITEMCOUNT	(10)


#define MAX_WORKER 128
#define MAX_DATABASE_SIZE 1024

//数据库名称长度
#define		DATABASE_STR_LEN			128
//数据库用户名长度
#define		DB_USE_STR_LEN				32
//数据库密码长度
#define		DB_PASSWORD_STR_LEN			32
//DB 操作时间间隔
#define		DB_OPERATION_TIME			500
//账号保存角色个数
#define		DB_CHAR_NUMBER				5
//角色中非即时刷新属性同步到ShareMemory的时间间隔
#define		DB_2_SM_TIME				60000 //60秒

//数据库连接池默认连接个数
#define		DB_CONNECTION_COUNT			40

// 服务器能接受的客气端调整位置与服务器位的差距
#define		DEF_SERVER_ADJUST_POS_WARP_DIST	(5.f)

// 玩家为一个物品（宠物）加锁需要消耗的精力
//#define		LOCK_A_OBJ_NEED_ENERGY		10


//服务器名字的最大长度
#define    MAX_SERVER_NAME    16

//服务器IP地址的长度
#define    MAX_SERVER_IP      16


//排行榜数据相关的长度定义
#define  MAX_RANGE_DATA_ROWCOUNT   10
#define  MAX_RANGE_DATA_TOTALROW   40

//==========================================
//              邮件相关长度定义
//==========================================

//没节的邮件数
#define  MAX_MAILNODE_SIZE 102400
//最多保存多少条离线邮件
#define  MAX_MAIL 100  //20

//邮箱容量报警数
#define  MAIL_LIST_WARN_SIZE 95

//  邮件内容的最长尺寸(200个utf8汉字)
//  [7/29/2010 dgh]
//  原有长度是256，现在改为 600
//#define  MAX_MAIL_CONTEX    256  
#define  MAX_MAIL_CONTEX    600  


//邮件标题最大长度 
#define  MAX_MAIL_TITLE      36 //20
//每页显示的邮件数
#define  MAX_MAIL_PAGE_NUMBER  10

#define MAX_STRING 256


#define ABS(m) ((m)>0?(m):(m)*(-1))

#define LENGTH(x0,z0,x1,z1)  (ABS((x0)-(x1))+ABS((z0)-(z1)))

#define MAX_FILE_PATH  260

#define MAX_TALENT_KIND	 5

#define MAX_STRING_INFO_COUNT 32

enum CMD_MODE {
  CMD_MODE_CLEARALL = 1,  //清除模式
  CMD_MODE_LOADDUMP = 2,  //载入dump模式
};

enum SM_COMMANDS {
  CMD_UNKNOW,
  CMD_SAVE_ALL,
  CMD_CLEAR_ALL,

};

struct SM_COMMANDS_STATE {
  SM_COMMANDS cmdType;
  union {
    INT iParam[6];
    FLOAT fParam[6];
    CHAR cParam[24];
  };
};

#define MAX_POOL_SIZE 128

struct GLOBAL_CONFIG {
  GLOBAL_CONFIG() { Commands.cmdType = CMD_UNKNOW; }
  SM_COMMANDS_STATE Commands;
};

#endif
