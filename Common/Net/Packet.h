

#ifndef __PACKET_H__
#define __PACKET_H__

#include "BaseType.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

class Socket;
class Player;

//SHORT高低位转换
#define EXANGESHORTHL(a,b)  \
	b = a<<8;				\
	b|=((a&0xff00)>>8);	

#define GET_PACKET_INDEX(a) ((a)>>24)
#define SET_PACKET_INDEX(a,index) ((a)=(((a)&0xffffff)+((index)<<24)))
#define GET_PACKET_LEN(a) ((a)&0xffffff)
#define SET_PACKET_LEN(a,len) ((a)=((a)&0xff000000)+(len))
//消息头中包括：PacketID_t-2字节；UINT-4字节中高位一个字节为消息序列号，其余
//三个字节为消息长度
//通过GET_PACKET_INDEX和GET_PACKET_LEN宏，可以取得UINT数据里面的消息序列号和长度
//通过SET_PACKET_INDEX和SET_PACKET_LEN宏，可以设置UINT数据里面的消息序列号和长度
#define PACKET_HEADER_SIZE  sizeof(Header) //(sizeof(PacketID_t)+sizeof(UINT)+sizeof(UINT))



//Packet::Execute(...) 的返回值
enum PACKET_EXE
{
	PACKET_EXE_ERROR = 0 ,
	PACKET_EXE_BREAK ,
	PACKET_EXE_CONTINUE ,
	PACKET_EXE_NOTREMOVE ,
	PACKET_EXE_NOTREMOVE_ERROR ,
};

struct Header {
  UCHAR action;
  UCHAR control;
  UCHAR ts[4];      //时间戳
  UCHAR index;      //包序列
  UCHAR length[4];  //后续包长度 length[2]
  UCHAR flag;       //标志位

  // packageId action & control
  USHORT getPackageId() { return *(USHORT*)(&action); }
  VOID setPackageId(USHORT val) { *(USHORT*)(&action) = val; }

  // timestamp
  UINT getTimestamp() { return *(UINT*)(ts); }
  VOID setTimestamp(UINT val) { *(UINT*)(ts) = val; }

  // length
  UINT getLength() {
    // return *(USHORT *)(length);
    return *(UINT*)(length);
  }
  VOID setLength(UINT val) {
    //*(USHORT *)(length) = (USHORT)val;
    *(UINT*)(length) = (UINT)val;
  }
};

class Packet
{
public :
	BYTE			m_Index ;
	BYTE			m_Status ;
	BYTE			m_RetFlag;
	UINT            m_ProcessTime;

public :
	Packet();

	virtual ~Packet();

	virtual VOID	CleanUp( ){};

	virtual BOOL	Read( SocketInputStream& iStream ) = 0 ;
	
	virtual BOOL	Write( SocketOutputStream& oStream ) const = 0;
	
	//return value: PACKET_EXE
	//PACKET_EXE_ERROR error in handler;
	//PACKET_EXE_BREAK return but the packet is forwarded to other thread to handle.
	//PACKET_EXE_CONTINUE packet handled but it will be continuing handled in this thread
	//PACKET_EXE_NOTREMOVE packet handled but it will be continuing handled in this thread without being removed
	virtual UINT		Execute( Player* pPlayer ) = 0 ;
	
	virtual	PacketID_t	GetPacketID( ) const = 0 ;
	
	virtual	UINT		GetPacketSize( ) const = 0 ;

	virtual BOOL		CheckPacket( ){ return TRUE ; }

	BYTE				GetPacketIndex( ) const { return m_Index ; } ;
	VOID				SetPacketIndex( BYTE Index ){ m_Index = Index ; } ;

	BYTE				GetPacketStatus( ) const { return m_Status ; } ;
	VOID				SetPacketStatus( BYTE Status ){ m_Status = Status ; } ;

	BYTE				GetPacketRetFlag( ) const { return m_RetFlag ; } ;
	VOID				SetPacketRetFlag( BYTE RetFlag ){ m_RetFlag = RetFlag ; } ;

	UINT                GetProcessTime() const {return m_ProcessTime;} ;
	VOID			    SetProcessTime( UINT ProcessTime ) { m_ProcessTime = ProcessTime; };

	UINT				ExecutePacket(Player* pPlayer);
};




#endif
