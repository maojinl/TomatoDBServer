#ifndef _SHARE_DB_MANAGER_H_
#define _SHARE_DB_MANAGER_H_


class ShareDBManager
{

public:
	virtual  BOOL	Init();
	virtual  VOID	run();

};


extern ShareDBManager* g_pDBManager;

#endif


