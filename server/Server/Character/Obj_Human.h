//	Obj_Human.h
//
//	���ܣ������SERVER�ϵ�ʵ����
//	�޸ļ�¼��
//////////////////////////////////////////////////////

#ifndef __HUMAN_H__
#define __HUMAN_H__

class Obj_Human;
class Player;

class Obj_Human
{
//===========================================
// Obj���нӿڼ̳�
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
// ����
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


	//������־
	//************************************
	// ������:    AddLogBook
	// ����ȫ��:  Obj_Human::AddLogBook
	// ��������:  public 
	// ����:      VOID
	// ��������: 
	// ����:      UINT LogID
	// ����:      UINT LogTime
	//************************************
	VOID					AddLogBook(UINT		LogID,UINT	   LogTime);


//===========================================
// Other
//===========================================
public:
	// �Ƚ϶�������
	BOOL ComparePasswd( const CHAR* szPasswd ) {
		return (strcmp(szPasswd, __GetPassword()) == 0);
	}

	PlayerID_t GetPlayerID() { return m_pPlayer->PlayerID(); };

	Player*					GetPlayer(){ return m_pPlayer; }
	VOID					SetPlayer( Player* pPlayer ){ m_pPlayer = pPlayer; }

protected:
	BOOL						m_bIsPasswdUnlock;	// ����������

private :
	PlayerID_t			m_PlayerID;
	Player*				m_pPlayer;
public:
	//virtual const UINT			__GetCreateDate( ) const ;//����ʱ�� human
	//virtual VOID				__SetCreateDate( const UINT createdate ) ;
	//virtual BOOL				__IsPasswordSetup();
	//virtual BOOL				__IsPasswordUnlock();
	//virtual VOID				__LockPassword(); // �������������������
	//virtual VOID				__UnlockPassword(); // �������������ȷ
	virtual const CHAR* __GetPassword() { return nullptr; };  // human password
	//virtual BOOL				__SetPassword( const CHAR* password );
	//virtual VOID				__DelPassword( ); // ɾ����������

};




#endif
