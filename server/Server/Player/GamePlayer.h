#ifndef __GAMEPLAYER_H__
#define __GAMEPLAYER_H__

#include "Type.h"
#include "Player.h"

class Obj_Human;
class RecyclePlayerManager;

class GamePlayer : public Player
{
public :
	GamePlayer( ) ;
	~GamePlayer( ) ;

	//消息执行接口
	virtual BOOL		ProcessCommand( BOOL Option = TRUE ) ;
	//数据接收接口
	virtual BOOL		ProcessInput( ) ;
	//数据发送接口
	virtual BOOL		ProcessOutput( ) ;

//心跳接口，处理所有逻辑
	virtual BOOL		HeartBeat( UINT uTime=0, INT nFlag=0 ) ;

	//清除数据
	virtual VOID		CleanUp( ) ;


public :
	//应用接口

	virtual BOOL		IsGamePlayer( ){ return TRUE ; } ;
	virtual BOOL		IsServerPlayer( ){ return FALSE ; } ;

	//连接成功后初始化基本数据
	VOID				Init( ) ;

	//向此Player发送一个消息包
	//此接口只能在本执行线程内处理（无数据同步能力）
	virtual BOOL		SendPacket( Packet* pPacket ) ;

	virtual VOID		Encrypt_SC(CHAR* header, UINT uLen, UINT uBeginPlace){ENCRYPT(header, uLen, SERVER_TO_CLIENT_KEY, uBeginPlace)}

	virtual VOID DecryptHead_CS(CHAR* header){} //{
        /*  ENCRYPT_HEAD(header, CLIENT_TO_GAMESERVER_KEY)
        }*/

	virtual VOID		Decrypt_CS(CHAR* header, UINT uLen, UINT uBeginPlace){ENCRYPT(header, uLen, CLIENT_TO_SERVER_KEY, uBeginPlace)}
	//玩家状态设置、读取接口
	VOID				SetPlayerStatus( UINT status ){ m_Status = status ; } ;
	UINT				GetPlayerStatus( ) { return m_Status ; } ;

    //断开网络连接，并且回收Player数据
    //当数据被回收后可能马上会被PlayerPool分配出去使用
    BOOL FreeOwn();

	virtual VOID		ResetKick( ) ;
	virtual VOID		Disconnect( ) ;

	VOID SetHuman(Obj_Human* pHuman) { m_pHuman = pHuman; };
    Obj_Human* GetHuman() { return m_pHuman; };

public :
	//通用游戏接口

	//验证用户接入的合法性
	BOOL		CheckKey( UINT key ) ;


	BOOL		IsDirty( ){ return m_Dirty ; } ;
	VOID		SetDirty( BOOL bValue ){ m_Dirty = bValue ; } ;
private :
	UINT					m_Status ;

public :

	Obj_Human* m_pHuman;

	GUID_t m_HumanGUID;

	UINT					m_KickTime ;		//判断是否需要踢掉玩家的计时器
	UINT					m_LastSendTime ;	//上次发送数据的时间
	UINT					m_CurrentTime ;		//当前逻辑时间
	INT						m_LeftTimeToQuit ;	//剩余被清除退出的时间
	BOOL					m_Dirty ;			//此标志表示当前连接已经无效，
												//不需要发送任何状态消息给世界数据服务器
	INT						m_SaveTime ;
};


#endif
