#include "pch.h"
#include "COutPacket.h"

COutPacket::COutPacket()
{ 
	init();
}

COutPacket::COutPacket(
	ULONG buffer_size)
{
	init();
	  
	m_COutPacket1(this, 0, buffer_size);
}


COutPacket::~COutPacket()
{ 
}

void 
COutPacket::init()
{
	m_COutPacket0 = (pfunCOutPacket_def0)0x006EC988;
	m_COutPacket1 = (pfunCOutPacket_def1)0x006EC9CE;
	m_Encode1 = (pfunCOutPacket_Encode1)0x00406549;
	m_Encode2 = (pfunCOutPacket_Encode2)0x00427F74;
	m_Encode4 = (pfunCOutPacket_Encode4)0x004065A6;
	m_EncodeBuffer = (pfunCOutPacket_EncodeBuffer)0x0046C00C;
	m_EncodeStr = (pfunCOutPacket_EncodeStr)0x0046F3CF;

	m_max_size = 0;
	m_buffer = nullptr;
	m_unknow = 0;

	return;
}

int 
COutPacket::Encode1(
	unsigned char value)
{
	return m_Encode1(this, 0, value);
}

int 
COutPacket::Encode2(
	unsigned short value)
{
	return m_Encode2(this, 0, value);
}

int 
COutPacket::Encode4(
	unsigned int value)
{
	return m_Encode4(this, 0, value);
}

int 
COutPacket::EncodeBuffer(
	void* pbuf
	, unsigned int size)
{
	return m_EncodeBuffer(this, 0, pbuf, size);
}

int 
COutPacket::EncodeStr(
	ZXString<char>& str)
{
	return m_EncodeStr(this, 0, str);
}