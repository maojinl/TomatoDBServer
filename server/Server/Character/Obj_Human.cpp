#include "stdafx.h"

#include "Obj_Human.h"

Obj_Human::Obj_Human()
{
	__ENTER_FUNCTION

	CleanUp();

	__LEAVE_FUNCTION
}
VOID	Obj_Human::AddLogBook(UINT LogID,UINT LogTime)
{
	//if(m_DB.AddLogBook(LogID,LogTime))
	//{
	//	_LOG_BOOK	LogBook;
	//	LogBook.m_LogID = LogID;
	//	LogBook.m_LogTime = LogTime;
	//	//��������־�ɹ�,���ظ��ͻ��˳ɹ�����Ϣ
	//	GCRetAddLogBook	Msg;
	//	Msg.SetLogBook(LogBook);
	//	this->GetPlayer()->SendPacket(&Msg);
	//}
	//else
	//{
	//	//������־ʧ��,��¼ʧ��
	//	g_pLog->FastSaveLog( LOG_FILE_1, "ObjHuman::AddLogBook Failed");
	//}
}