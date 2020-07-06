#ifndef __GAMEDEFINE_H__
#define __GAMEDEFINE_H__

//��������ֵ
#define MAX_WORLD 255

#define MAX_WORLD_USER	3000

//�û���ɫ���ֿ�����������ֵ
#define MAX_CHARACTER_INPUTNAME 24

//GamePlayer������������
#define MAX_PLAYER 1024

#define MAX_CHARACTER_NAME 30

//��ҳƺų���
#define MAX_CHARACTER_TITLE 34

//����������̳���
#define MIN_PWD 4

//�����������󳤶� + 1
#define MAX_PWD 17

//�û��ʺŵ����ֵ
#define MAX_ACCOUNT 16

//�û���������ֵ
#define MAX_PASSWORD 32

//ID��󳤶�
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

//���ݿ����Ƴ���
#define		DATABASE_STR_LEN			128
//���ݿ��û�������
#define		DB_USE_STR_LEN				32
//���ݿ����볤��
#define		DB_PASSWORD_STR_LEN			32
//DB ����ʱ����
#define		DB_OPERATION_TIME			500
//�˺ű����ɫ����
#define		DB_CHAR_NUMBER				5
//��ɫ�зǼ�ʱˢ������ͬ����ShareMemory��ʱ����
#define		DB_2_SM_TIME				60000 //60��

//���ݿ����ӳ�Ĭ�����Ӹ���
#define		DB_CONNECTION_COUNT			40

// �������ܽ��ܵĿ����˵���λ���������λ�Ĳ��
#define		DEF_SERVER_ADJUST_POS_WARP_DIST	(5.f)

// ���Ϊһ����Ʒ�����������Ҫ���ĵľ���
//#define		LOCK_A_OBJ_NEED_ENERGY		10


//���������ֵ���󳤶�
#define    MAX_SERVER_NAME    16

//������IP��ַ�ĳ���
#define    MAX_SERVER_IP      16


//���а�������صĳ��ȶ���
#define  MAX_RANGE_DATA_ROWCOUNT   10
#define  MAX_RANGE_DATA_TOTALROW   40

//==========================================
//              �ʼ���س��ȶ���
//==========================================

//û�ڵ��ʼ���
#define  MAX_MAILNODE_SIZE 102400
//��ౣ������������ʼ�
#define  MAX_MAIL 100  //20

//��������������
#define  MAIL_LIST_WARN_SIZE 95

//  �ʼ����ݵ���ߴ�(200��utf8����)
//  [7/29/2010 dgh]
//  ԭ�г�����256�����ڸ�Ϊ 600
//#define  MAX_MAIL_CONTEX    256  
#define  MAX_MAIL_CONTEX    600  


//�ʼ�������󳤶� 
#define  MAX_MAIL_TITLE      36 //20
//ÿҳ��ʾ���ʼ���
#define  MAX_MAIL_PAGE_NUMBER  10

#define MAX_STRING 256


#define ABS(m) ((m)>0?(m):(m)*(-1))

#define LENGTH(x0,z0,x1,z1)  (ABS((x0)-(x1))+ABS((z0)-(z1)))

#define MAX_FILE_PATH  260

#define MAX_TALENT_KIND	 5

#define MAX_STRING_INFO_COUNT 32

enum CMD_MODE {
  CMD_MODE_CLEARALL = 1,  //���ģʽ
  CMD_MODE_LOADDUMP = 2,  //����dumpģʽ
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
