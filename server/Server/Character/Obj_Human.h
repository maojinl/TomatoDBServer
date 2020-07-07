//	Obj_Human.h
//
//	功能：玩家在SERVER上的实现类
//	修改记录：
//////////////////////////////////////////////////////

#ifndef __HUMAN_H__
#define __HUMAN_H__

class Obj_Human;
class Player;

class User
{
private:
	UINT					m_uLastTime;
	UINT					m_uNowTime;
	UINT					m_uCreateTime;
	Worker*					m_pWorker;
public:
	User() {};
	virtual ~User() {};
	VOID OnEnterWorker(Worker* pWorker)
	{
		__ENTER_FUNCTION

		m_uLastTime = 0;
		m_uNowTime = 0;
		m_uCreateTime = 0;
		m_pWorker = pWorker;
		__LEAVE_FUNCTION
	}

	VOID OnLeaveWorker(VOID)
	{
		__ENTER_FUNCTION

		m_uLastTime = 0;
		m_uNowTime = 0;
		m_uCreateTime = 0;
		m_pWorker = nullptr;

		__LEAVE_FUNCTION
	}

	Worker* GetWorker()
	{
		return m_pWorker;
	}
};

class Obj_Human : public User
{
//===========================================
// Obj公有接口继承
//===========================================
public:
	Obj_Human();
	virtual ~Obj_Human();
	virtual VOID CleanUp(VOID);

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
	BOOL						m_bIsPasswdUnlock;	//

private :
	PlayerID_t			m_PlayerID;
	Player*				m_pPlayer;
public:
	//virtual const UINT			__GetCreateDate() const;
	//virtual VOID				__SetCreateDate(const UINT createdate);
	//virtual BOOL				__IsPasswordSetup();
	//virtual BOOL				__IsPasswordUnlock();
	//virtual VOID				__LockPassword();
	//virtual VOID				__UnlockPassword();
	virtual const CHAR* __GetPassword() { return nullptr; };  // human password
	//virtual BOOL				__SetPassword(const CHAR* password);
	//virtual VOID				__DelPassword();
};

#endif
