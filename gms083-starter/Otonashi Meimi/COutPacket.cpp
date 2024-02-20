#include "pch.h"
#include "COutPacket.h"

typedef int(__fastcall* pfunCOutPacket_def0)(void* pthis, int);
typedef int(__fastcall* pfunCOutPacket_def1)(void* pthis, int, ULONG buffer_size);
typedef int(__fastcall* pfunCOutPacket_Encode1)(void* pthis, int, unsigned char value);
typedef int(__fastcall* pfunCOutPacket_Encode2)(void* pthis, int, unsigned short value);
typedef int(__fastcall* pfunCOutPacket_Encode4)(void* pthis, int, unsigned int value);
typedef int(__fastcall* pfunCOutPacket_EncodeBuffer)(void* pthis, int, void* pbuf, unsigned int size);
typedef int(__fastcall* pfunCOutPacket_EncodeStr)(void* pthis, int, ZXString<char>&);
 
static pfunCOutPacket_def0 g_COutPacket0;
static pfunCOutPacket_def1 g_COutPacket1;
static pfunCOutPacket_Encode1 g_Encode1;
static pfunCOutPacket_Encode2 g_Encode2;
static pfunCOutPacket_Encode4 g_Encode4;
static pfunCOutPacket_EncodeBuffer g_EncodeBuffer;
static pfunCOutPacket_EncodeStr g_EncodeStr;
 
COutPacket::COutPacket(
	ULONG buffer_size)
{
	init();
	g_COutPacket1(this, 0, buffer_size);
}


COutPacket::~COutPacket()
{ 
}

void 
COutPacket::init()
{ 
	if (g_COutPacket0 == nullptr)
	{
		g_COutPacket0 = (pfunCOutPacket_def0)0x006EC988;
	} 

	if (g_COutPacket1 == nullptr)
	{
		g_COutPacket1 = (pfunCOutPacket_def1)0x006EC9CE;
	}

	if (g_Encode1 == nullptr)
	{
		g_Encode1 = (pfunCOutPacket_Encode1)0x00406549;
	}

	if (g_Encode2 == nullptr)
	{
		g_Encode2 = (pfunCOutPacket_Encode2)0x00427F74;
	}

	if (g_Encode4 == nullptr)
	{
		g_Encode4 = (pfunCOutPacket_Encode4)0x004065A6;
	}

	if (g_EncodeBuffer == nullptr)
	{
		g_EncodeBuffer = (pfunCOutPacket_EncodeBuffer)0x0046C00C;
	}

	if (g_EncodeStr == nullptr)
	{
		g_EncodeStr = (pfunCOutPacket_EncodeStr)0x0046F3CF;
	}
	       
	m_max_size = 0;
	m_buffer = nullptr;
	m_unknow = 0;
	m_unknow2 = 0;

	return;
}

int 
COutPacket::Encode1(
	unsigned char value)
{
	return g_Encode1(this, 0, value);
}

int 
COutPacket::Encode2(
	unsigned short value)
{
	return g_Encode2(this, 0, value);
}

int 
COutPacket::Encode4(
	unsigned int value)
{
	return g_Encode4(this, 0, value);
}

int 
COutPacket::EncodeBuffer(
	void* pbuf
	, unsigned int size)
{
	return g_EncodeBuffer(this, 0, pbuf, size);
}

int 
COutPacket::EncodeStr(
	ZXString<char>& str)
{
	return g_EncodeStr(this, 0, str);
}