#include "pch.h"
#include "CClientSocket.h"

#include "memory.h"

typedef void (__fastcall* pfunSendPacket)(CClientSocket* pthis, int dummy, const COutPacket* out_pack);
static pfunSendPacket g_SendPacket;

CClientSocket* CClientSocket::m_this = nullptr;
CClientSocket* CClientSocket::pins()
{
	if (m_this == nullptr)
	{
		int socket_point = 0;
		do 
		{
			::Sleep(1000);
			memory::read(0x00BE7914, socket_point);
		} while (socket_point == 0); 

		m_this = (CClientSocket*)socket_point;
		  
		m_this->init();
	}

	return m_this;
}

CClientSocket::CClientSocket()
{

}

CClientSocket::~CClientSocket()
{

}

void 
CClientSocket::init()
{
	g_SendPacket = (pfunSendPacket)0x0049637B;
	return;
}

void 
CClientSocket::SendPacket(
	COutPacket* out_pack)
{
	g_SendPacket(this, 0, out_pack);
	return;
}