#include "stdafx.h"

#include "Obj_Human.h"

VOID	Obj_Human::AddLogBook(UINT LogID,UINT LogTime)
{
	//if(m_DB.AddLogBook(LogID,LogTime))
	//{
	//	_LOG_BOOK	LogBook;
	//	LogBook.m_LogID = LogID;
	//	LogBook.m_LogTime = LogTime;
	//	//加入新日志成功,返回给客户端成功的消息
	//	GCRetAddLogBook	Msg;
	//	Msg.SetLogBook(LogBook);
	//	this->GetPlayer()->SendPacket(&Msg);
	//}
	//else
	//{
	//	//加入日志失败,记录失败
	//	g_pLog->FastSaveLog( LOG_FILE_1, "ObjHuman::AddLogBook Failed");
	//}
}