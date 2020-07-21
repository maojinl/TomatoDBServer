#ifndef _SHARE_MEM_ACCESS_OBJECT_H_
#define _SHARE_MEM_ACCESS_OBJECT_H_

#include "Type.h"


#define		SHMEM_LOG_PATH	"./Log/ShareMemory.log"
/*
 *		�����ڴ���ʶ���
 *		ShareMemory	Access	Object
 */

struct SMHead {
  SM_KEY m_Key;
  unsigned long m_Size;
  UINT m_HeadVer;  //�����̰汾
  SMHead() {
    m_Key = 0;
    m_Size = 0;
    m_HeadVer = 0;
  }
};

class ShareMemAO
{

	
public:
	ShareMemAO()
	{
		m_pDataPtr	=	0;
		m_hold		=	0;
		m_Size		=	0;
		m_pHeader	=	0;	
	}
	~ShareMemAO(){};
	/*
	 *	����ShareMem ���ʶ���(�´���)
	 *
	 *  SM_KEY	key		���ʼ�ֵ
	 *
	 *	UINT		Size	�����������ֽڸ���
	 *
	 */
	BOOL	Create(SM_KEY key,UINT	Size);
	/*
	 *	���ٶ���
	 */
	VOID	Destory();

	/*
	 *		����ShareMem ���ʶ���(�����´���)
	 *		SM_KEY	key		���ʼ�ֵ
	 *
	 *		UINT		Size	�����������ֽڸ���
	 *		
	 */
	BOOL	Attach(SM_KEY,UINT Size);
	/*
	 *		ȡ������(������)
	 */
	BOOL	Detach();

	/*
	 *	 ���������ָ��
	 */
	CHAR*	GetDataPtr()
	{
		return m_pDataPtr;
	}

	/*
	 *	��� ��СΪtSize �ĵ�tIndex ��smu������
	 */
	CHAR*	GetTypePtr(UINT tSize,UINT tIndex)
	{
		Assert(tSize>0);
		Assert(tSize*tIndex<m_Size);
		if( tSize<=0 || tIndex>=m_Size )
			return nullptr ;
		return m_pDataPtr+tSize*tIndex;
	}
	/*
	 *	����������ܴ�С
	 */
	UINT	GetSize()
	{
		return m_Size;
	}

	BOOL	DumpToFile(CHAR* FilePath);
	BOOL	MergeFromFile(CHAR* FilePath);

	UINT	GetHeadVer();
	VOID	SetHeadVer(UINT ver);
	
	//����
	INT					m_CmdArg;
private:
	
	//ShareMemory	�ڴ��С
	UINT				m_Size;
	// ShareMemory  ����ָ��
	CHAR*				m_pDataPtr;
	// ShareMemory	�ڴ�ͷָ��
	CHAR*				m_pHeader;
	// ShareMemory	���	
	SMHandle			m_hold;
	
};	





#endif