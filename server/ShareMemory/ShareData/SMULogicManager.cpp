#include "stdafx.h"
#include "SMULogicManager.h"
#include "TimeManager.h"
#include "Log.h"
#include "ShareDBManager.h"
#include "Config.h"

extern BOOL g_LockTimeOutEnable;

GLOBAL_CONFIG g_SMConfig;

template<>
BOOL	SMULogicManager<string>::DoSaveAll()
{
	__ENTER_FUNCTION
		if(!m_PoolSharePtr)
		{
			Assert(m_PoolSharePtr);
			return FALSE;
		}

		INT MaxPoolSize = m_PoolSharePtr->GetPoolMaxSize();
		//做预先统计
		INT		iHoldDataCount	=	0;		//已经占据位置的SMU个数
		INT		iCanSaveCount	=	0;		//服务器通知下线等待存盘档案数量
		INT		iHaveSaveCount	=	0;		//已经存盘等待服务器回收个数
		return TRUE;
	__LEAVE_FUNCTION
		return FALSE;

}


template<>
BOOL SMULogicManager<string>::DoNormalSave()
{
	__ENTER_FUNCTION

		if(!m_PoolSharePtr)
		{
			Assert(m_PoolSharePtr);
			return FALSE;
		}

		INT MaxPoolSize = m_PoolSharePtr->GetPoolMaxSize();
		//做预先统计
		INT		iHoldDataCount	=	0;		//已经占据位置的SMU个数
		INT		iCanSaveCount	=	0;		//服务器通知下线等待存盘档案数量
		INT		iHaveSaveCount	=	0;		//已经存盘等待服务器回收个数

		for(INT iIndex = 0;iIndex<MaxPoolSize;iIndex++)
		{
			string*	pSMU = m_PoolSharePtr->GetPoolObj(iIndex);
			if(!pSMU)
			{
				Assert(pSMU);
				return FALSE;
			}
			
			UINT    uTime		=	g_pTimeManager->RunTime();			//取当前时间

		}
		
	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

template<>
BOOL SMULogicManager<string>::DoClear()
{
	__ENTER_FUNCTION
	
	INT MaxPoolSize = m_PoolSharePtr->GetPoolMaxSize();
	for(INT iIndex = 0;iIndex<MaxPoolSize;iIndex++)
	{
		string*	pSMU = m_PoolSharePtr->GetPoolObj(iIndex);
		if(!pSMU)
		{
			Assert(pSMU);
			return FALSE;
		}
	
		pSMU->clear();
	}
	return TRUE;
	

	__LEAVE_FUNCTION

	return FALSE;
}

template<>
BOOL SMULogicManager<string>::DoPostInit()
{
	__ENTER_FUNCTION

		if(!m_PoolSharePtr)
		{
			Assert(m_PoolSharePtr);
			return FALSE;
		}

		INT MaxPoolSize = m_PoolSharePtr->GetPoolMaxSize();

		for(INT iIndex = 0;iIndex<MaxPoolSize;iIndex++)
		{
			string*	pSMU = m_PoolSharePtr->GetPoolObj(iIndex);
			if(!pSMU)
			{
				Assert(pSMU);
				return FALSE;
			}
                        pSMU->append("sss");
		}

		return TRUE;

	__LEAVE_FUNCTION

		return FALSE;
}