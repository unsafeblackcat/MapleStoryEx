#include "pch.h"
#include "CClientSocket.h"
#include "memory.h"
#include "Hook.h"

typedef void (__fastcall* pfunSendPacket)(CClientSocket* pthis, int dummy, const COutPacket* out_pack);
static pfunSendPacket g_SendPacket = nullptr;

typedef int (__fastcall *pfunCClientSocket_ProcessPacket)(void* pthis, int dummy, CInPacket* in_pack);
pfunCClientSocket_ProcessPacket g_CClientSocket_ProcessPacket = nullptr;

CClientSocket* CClientSocket::m_this = nullptr;
CClientSocket* CClientSocket::pins()
{
	if (m_this == nullptr)
	{
		int socket_point = 0;
		do 
		{ 
			memory::read(0x00BE7914, socket_point);
			if (socket_point == 0)
			{
				::Sleep(1000);
			}
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
CClientSocket::SendPacket(
	COutPacket* out_pack)
{
	g_SendPacket(this, 0, out_pack);
	return;
}

void 
CClientSocket::init()
{
	g_SendPacket = (pfunSendPacket)0x0049637B;
	hook_recv();
	return;
}

void 
CClientSocket::hook_recv()
{
	void* fun = nullptr;
	__asm {
		mov eax, CClientSocket::ProcessPacket
		mov fun, eax
	}

	g_CClientSocket_ProcessPacket = (pfunCClientSocket_ProcessPacket)0x004965F1;
	chook(&(PVOID&)g_CClientSocket_ProcessPacket, fun);
	return;
}
 

int  
CClientSocket::ProcessPacket(
	CInPacket* in_pack)
{
	CInPacket in1;
	in1 = *in_pack;
	 
	int iret = g_CClientSocket_ProcessPacket(this, 0, in_pack);
	
	return iret;
}