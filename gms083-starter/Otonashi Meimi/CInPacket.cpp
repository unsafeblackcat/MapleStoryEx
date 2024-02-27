#define WIN32_LEAN_AND_MEAN
#include "CInPacket.h"
#include "ZAllocEx2.h"

typedef void (__fastcall *pfunCInPacket_CInPacket)(void* pthis, int dummy, CInPacket& obj);
typedef CInPacket* (__fastcall *pfunCInPacket_get)(void* pthis, int dummy, const CInPacket& obj);
typedef char (__fastcall *pfunCInPacket_Decode1)(void* pthis, int dummy);
typedef short (__fastcall *pfunCInPacket_Decode2)(void* pthis, int dummy);
typedef unsigned long (__fastcall* pfunCInPacket_Decode4)(void* pthis, int dummy);
typedef int (__fastcall* pfunCInPacket_DecodeBuffer)(void* pthis, int dummy, unsigned char* out, int len);
typedef unsigned char* (__fastcall* pfunCInPacket_DecodeStr)(void* pthis, int dummy, ZXString<char>* pstr);
typedef int (__fastcall* pfunCInPacket_DecryptData)(void* pthis, int dummy, int unknow);

static pfunCInPacket_CInPacket g_CInPacket_CInPacket = nullptr;
static pfunCInPacket_get g_CInPacket_get = nullptr;
static pfunCInPacket_Decode1 g_CInPacket_Decode1 = nullptr;
static pfunCInPacket_Decode2 g_CInPacket_Decode2 = nullptr;
static pfunCInPacket_Decode4 g_CInPacket_Decode4 = nullptr;
static pfunCInPacket_DecodeBuffer g_CInPacket_DecodeBuffer = nullptr;
static pfunCInPacket_DecodeStr g_CInPacket_DecodeStr = nullptr;
static pfunCInPacket_DecryptData g_CInPacket_DecryptData = nullptr;

CInPacket::CInPacket()
{ 
}

CInPacket::~CInPacket()
{
	if (m_membuffer)
	{
		ZAllocEx2::Free(m_membuffer);
	}
}
  
CInPacket::CInPacket(
	CInPacket& in)
{
	if (g_CInPacket_CInPacket == nullptr)
	{
		g_CInPacket_CInPacket = (pfunCInPacket_CInPacket)0x006EC39F;
	}

	g_CInPacket_CInPacket(this, 0, in);
	return;
}

CInPacket*
CInPacket::operator= (
	const CInPacket& obj)
{
	if (g_CInPacket_get == nullptr)
	{
		g_CInPacket_get = (pfunCInPacket_get)0x0066C3E1;
	}
	 
	return g_CInPacket_get(this, 0, obj);
}

char 
CInPacket::Decode1()
{
	if (g_CInPacket_Decode1 == nullptr)
	{
		g_CInPacket_Decode1 = (pfunCInPacket_Decode1)0x004065F3;
	}

	return g_CInPacket_Decode1(this, 0);
}

short 
CInPacket::Decode2()
{
	if (g_CInPacket_Decode2 == nullptr)
	{
		g_CInPacket_Decode2 = (pfunCInPacket_Decode2)0x0042470C;
	}

	return g_CInPacket_Decode2(this, 0);
}


unsigned long 
CInPacket::Decode4()
{
	if (g_CInPacket_Decode4 == nullptr)
	{
		g_CInPacket_Decode4 = (pfunCInPacket_Decode4)0x00406629;
	}

	return g_CInPacket_Decode4(this, 0);
}


int 
CInPacket::DecodeBuffer(
	unsigned char* out
	, int len)
{
	if (g_CInPacket_DecodeBuffer == nullptr)
	{
		g_CInPacket_DecodeBuffer = (pfunCInPacket_DecodeBuffer)0x00432257;
	}

	return g_CInPacket_DecodeBuffer(this, 0, out, len);
}
 
unsigned char* 
CInPacket::DecodeStr(
	ZXString<char>* pstr)
{
	if (g_CInPacket_DecodeStr == nullptr)
	{
		g_CInPacket_DecodeStr = (pfunCInPacket_DecodeStr)0x0046F30C;
	}

	return g_CInPacket_DecodeStr(this, 0, pstr);
}
	
int 
CInPacket::DecryptData(
	int unknow)
{
	if (g_CInPacket_DecryptData == nullptr)
	{
		g_CInPacket_DecryptData = (pfunCInPacket_DecryptData)0x006EC58B;
	}

	return g_CInPacket_DecryptData(this, 0, unknow);
}