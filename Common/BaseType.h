/////////////////////////////////////////////////////////////////////////////////
//文件名称：BaseType.h
//功能描述：系统底层类型基础文件，无授权人员不得修改此文件内容
//版本说明：Windows操作系统需要定义宏：__WINDOWS__
//			Linux操作系统需要定义宏：__LINUX__
//修改情况：
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef __BASETYPE_H__
#define __BASETYPE_H__



/////////////////////////////////////////////////////////////////////////////////
//网络信息预定义宏
/////////////////////////////////////////////////////////////////////////////////
#ifndef FD_SETSIZE
#define FD_SETSIZE      1024
#endif /* FD_SETSIZE */

/***************************************************/
//交互包是否加密，注释后为加密，发布版本请加密
//请勿将未加密的代码签入VSS!!!!!!!!!!!!!!!!
//#define NO_ENCRYPT
/***************************************************/





/////////////////////////////////////////////////////////////////////////////////
//当前包含的系统头文件引用
/////////////////////////////////////////////////////////////////////////////////
#if defined(__WINDOWS__)
#pragma warning ( disable : 4786 )
#pragma warning ( disable : 4996 )
	#include <Windows.h>
	//#include "crtdbg.h"
#elif defined(__LINUX__)
	#include <sys/types.h>
	#include <pthread.h>
	//#include <execinfo.h>  //Johnny 20100611 
	#include <signal.h>
	#include <exception>
	#include <setjmp.h>
	//#include <sys/epoll.h>		//Johnny 20100611 
#endif

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include <stdarg.h>

using namespace std;

///////////////////////////////////////////////////////////////////////
//标准数据类型定义
///////////////////////////////////////////////////////////////////////
#define VOID			void			//标准空
typedef unsigned char	UCHAR;			//标准无符号CHAR
typedef char			CHAR;			//标准CHAR
typedef unsigned int	UINT;			//标准无符号INT
typedef int				INT;			//标准INT
typedef unsigned short	USHORT;			//标准无符号short
typedef short			SHORT;			//标准short
typedef unsigned long	ULONG;			//标准无符号LONG(不推荐使用)
typedef long			LONG;			//标准LONG(不推荐使用)
typedef float			FLOAT;			//标准float

typedef UCHAR			uchar;
typedef USHORT			ushort;
typedef UINT			uint;
typedef ULONG			ulong;
typedef ULONG			IP_t;
typedef USHORT			PacketID_t;
typedef INT				BOOL;
typedef UCHAR			BYTE;




///////////////////////////////////////////////////////////////////////
//基本数据宏定义
///////////////////////////////////////////////////////////////////////

//IP地址的字符最大长度
#define IP_SIZE			24
#define KEY_SIZE			64
#define MAX_WORLDCOUNT			256
#define TIMELENTH			23

//↓这样在可执行文件中将是汉字显示，上线前要改成随机KEY↓KEY不得小于10个字节
#define GAMESERVER_TO_CLIENT_KEY "服务器端对客户端的封包密钥"
#define CLIENT_TO_GAMESERVER_KEY "服务器端对客户端的封包密钥"
#define LOGIN_TO_CLIENT_KEY      "服务器端对客户端的封包密钥"
#define CLIENT_TO_LOGIN_KEY      "服务器端对客户端的封包密钥"
#define OSTREAM_KEY              "底层全局封包流通用密钥"	

#define CLIENT_TO_SERVER_KEY     "sdas32SdSDF23242DFHKSADFXCD"
#define SERVER_TO_CLIENT_KEY     "MKBW322UIJdju98JDFIWBNMxmnd"

//用户账号认证KEY
#define USER_ACCOUNT_KEY         "uiGVKbu98kakjskiGGsdafNNdda"

//↑这样在可执行文件中将是汉字显示，上线前要改成随机KEY↑KEY不得小于10个字节

#define PACK_COMPART "$-$"//封包分隔符
#define PACK_COMPART_SIZE strlen(PACK_COMPART)

#define NO_ENCRYPT

#ifndef ENCRYPT

	#if defined(NO_ENCRYPT)
		#define ENCRYPT(x,xlen,KEY,BeginPlace) {;}
	#else
		#define ENCRYPT(x,xlen,KEY,BeginPlace)	if( (x)!=nullptr ) \
		{ \
		\
			CHAR* t_pBuffer = (x); \
			CHAR* pKey = {KEY}; \
			UINT KeyLen = (UINT)strlen(pKey); \
			for (UINT i = 0; i < (xlen); i++) \
			{ \
				*t_pBuffer ^= pKey[(i+BeginPlace)%KeyLen]; \
				t_pBuffer++; \
			} \
		}
	#endif

#endif

#ifndef ENCRYPT_HEAD
#define ENCRYPT_HEAD(x,KEY)	if( (x)!=nullptr ) \
		{ \
			CHAR* t_pBuffer = (x); \
			CHAR* pKey = {KEY}; \
			UINT KeyLen = (UINT)strlen(pKey); \
			for (UINT i = 0; i < PACKET_HEADER_SIZE; i++) \
			{ \
				*t_pBuffer ^= pKey[i%KeyLen]; \
				t_pBuffer++; \
			} \
		}
#endif

#define OVER_MAX_SERVER 256

//无效的句柄
#define INVALID_HANDLE	-1
//无效的ID值
#define INVALID_ID		-1
//真
#ifndef TRUE
	#define TRUE 1
#endif
//假
#ifndef FALSE
	#define FALSE 0
#endif
//文件路径的字符最大长度
#ifndef _MAX_PATH
	#define _MAX_PATH 260
#endif

///////////////////////////////////////////////////////////////////////
//调试预定义宏定义
///////////////////////////////////////////////////////////////////////
#if defined(NDEBUG)
	#define __ENTER_FUNCTION_FOXNET if(1){
	#define __LEAVE_FUNCTION_FOXNET }
#else
	#define __ENTER_FUNCTION_FOXNET if(1){
	#define __LEAVE_FUNCTION_FOXNET }
#endif


#if defined(NDEBUG)
	#define _MY_TRY try
	#define _MY_CATCH catch(...)
#else
	#define _MY_TRY try
	#define _MY_CATCH catch(...)
#endif



//根据指针值删除内存
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=nullptr ) { delete (x); (x)=nullptr; }
#endif
//根据指针值删除数组类型内存
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=nullptr ) { delete[] (x); (x)=nullptr; }
#endif
//根据指针调用free接口
#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=nullptr ) { free(x); (x)=nullptr; }
#endif
//根据指针调用Release接口
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if( (x)!=nullptr ) { (x)->Release(); (x)=nullptr; }
#endif


#endif
