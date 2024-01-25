#pragma once
#include <ZXString.h>

typedef int(__fastcall* pfunCOutPacket_def0)(void* pthis, int);
typedef int (__fastcall* pfunCOutPacket_def1)(void* pthis, int, ULONG buffer_size); 
typedef int(__fastcall* pfunCOutPacket_Encode1)(void* pthis, int, unsigned char value);
typedef int(__fastcall* pfunCOutPacket_Encode2)(void* pthis, int, unsigned short value);
typedef int(__fastcall* pfunCOutPacket_Encode4)(void* pthis, int, unsigned int value);
typedef int(__fastcall* pfunCOutPacket_EncodeBuffer)(void* pthis, int, void* pbuf, unsigned int size);
typedef int(__fastcall* pfunCOutPacket_EncodeStr)(void* pthis, int, ZXString<char>&);

class COutPacket
{
public:
	COutPacket();
	COutPacket(ULONG buffer_size);
	virtual ~COutPacket();

private:
	void init();

public:
	int Encode1(unsigned char ch);
	int Encode2(unsigned short value);
	int Encode4(unsigned int value);
	int EncodeBuffer(void* pbuf, unsigned int size);
	int EncodeStr(ZXString<char>& str);

private:
	int m_max_size;
	char* m_buffer;
	int m_unknow;
	int m_unknow2;

private:
	pfunCOutPacket_def0 m_COutPacket0;
	pfunCOutPacket_def1 m_COutPacket1;
	pfunCOutPacket_Encode1 m_Encode1;
	pfunCOutPacket_Encode2 m_Encode2;
	pfunCOutPacket_Encode4 m_Encode4;
	pfunCOutPacket_EncodeBuffer m_EncodeBuffer;
	pfunCOutPacket_EncodeStr m_EncodeStr;
};