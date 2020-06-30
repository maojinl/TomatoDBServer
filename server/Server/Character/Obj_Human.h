//	Obj_Human.h
//
//	功能：玩家在SERVER上的实现类
//	修改记录：
//////////////////////////////////////////////////////

#ifndef __HUMAN_H__
#define __HUMAN_H__

class Obj_Human;
class Player;

class Obj_Human
{
//===========================================
// Obj公有接口继承
//===========================================
public:
	Obj_Human( );
	virtual ~Obj_Human( );
	virtual VOID CleanUp( VOID );

protected:
    char m_Name[MAX_CHARACTER_NAME] = "human";
    char m_Title[MAX_CHARACTER_TITLE] = "title";
    INT m_Level = 0;

//===========================================
// 属性
//===========================================
public:  
	virtual GUID_t			GetGUID( VOID )const;

	virtual VOID SetName(const CHAR* pszName) {};
    virtual const CHAR* GetName(VOID) const { return m_Name; };

	virtual VOID SetTitle(const CHAR* pszTitle) {
        memset(m_Title, 0, MAX_CHARACTER_TITLE);
        size_t nSize = (BYTE)strlen(pszTitle);
        nSize = nSize > MAX_CHARACTER_TITLE ? MAX_CHARACTER_TITLE : nSize;
		memcpy(m_Title, pszTitle, nSize);
    }
    
	virtual const CHAR* GetTitle(VOID) const { return m_Title; }

	virtual VOID SetLevel(INT nLevel) { m_Level = nLevel; };
    virtual INT GetLevel(VOID) const { return m_Level; };


	//增加日志
	//************************************
	// 函数名:    AddLogBook
	// 函数全名:  Obj_Human::AddLogBook
	// 访问限制:  public 
	// 返回:      VOID
	// 函数修饰: 
	// 参数:      UINT LogID
	// 参数:      UINT LogTime
	//************************************
	VOID					AddLogBook(UINT		LogID,UINT	   LogTime);


//===========================================
// Other
//===========================================
public:
	// 比较二级密码
	BOOL ComparePasswd( const CHAR* szPasswd ) {
		return (strcmp(szPasswd, __GetPassword()) == 0);
	}

	PlayerID_t GetPlayerID() { return m_pPlayer->PlayerID(); };

	Player*					GetPlayer(){ return m_pPlayer; }
	VOID					SetPlayer( Player* pPlayer ){ m_pPlayer = pPlayer; }

protected:
	BOOL						m_bIsPasswdUnlock;	// 密码解锁标记

private :
	PlayerID_t			m_PlayerID;
	Player*				m_pPlayer;
public:
	//virtual const UINT			__GetCreateDate( ) const ;//创建时间 human
	//virtual VOID				__SetCreateDate( const UINT createdate ) ;
	//virtual BOOL				__IsPasswordSetup();
	//virtual BOOL				__IsPasswordUnlock();
	//virtual VOID				__LockPassword(); // 输入二级密码错误，则调用
	//virtual VOID				__UnlockPassword(); // 输入二级密码正确
	virtual const CHAR* __GetPassword() { return nullptr; };  // human password
	//virtual BOOL				__SetPassword( const CHAR* password );
	//virtual VOID				__DelPassword( ); // 删除二级密码

};




#endif
