#ifndef __SERVERTHREAD_H__
#define __SERVERTHREAD_H__

#include "Type.h"
#include "Thread.h"

class ServerThread : public Thread
{
public :
	ServerThread( ) ;
	~ServerThread( ) ;

	//主循环
	virtual VOID	run( ) ;

	//停止线程执行
	virtual VOID	stop( ) { m_Active = FALSE ; } ;

	//判断当前线程是否激活
	BOOL			IsActive( ){ return m_Active ; } ;



private :
	BOOL		m_Active ;
};





#endif
