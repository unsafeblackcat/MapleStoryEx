#pragma once
#include <ZXString.h>


class COutPacket
{
public: 
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
};