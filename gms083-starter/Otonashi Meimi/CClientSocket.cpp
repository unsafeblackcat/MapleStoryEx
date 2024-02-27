#include "pch.h"
#include "CClientSocket.h"
#include "memory.h"
#include "Hook.h"
#include "CProtocol.h"

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
	CInPacket in; 
	in = *in_pack;
	if (in.Decode2() == LOGIN_STATUS)
	{
		int m_login_status = in.Decode2();
		char m_unknow = in.Decode1();
		char m_unknow1 = in.Decode1();
		int m_unknow2 = in.Decode4();
		int m_account_id = in.Decode4();
		char m_gender = in.Decode1();
		char m_is_gm_account = in.Decode1();
		char m_gm_level = in.Decode1();
		char m_country_code = in.Decode1();

		ZXString<char> str;
		in.DecodeStr(&str);

		char m_unknow3 = in.Decode1();
		char m_is_ban = in.Decode1();

		unsigned char	m_ban_time_stamp[8];
		in.DecodeBuffer(m_ban_time_stamp, 8);

		unsigned char	m_creation_time_stamp[8];
		in.DecodeBuffer(m_creation_time_stamp, 8);

		int m_remove_select_world_hint = in.Decode4();
		char m_is_pin = in.Decode1();
		char m_pin_status = in.Decode1();

		int i = 0; 
	}
	

	int iret = g_CClientSocket_ProcessPacket(this, 0, in_pack);
	return iret;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        