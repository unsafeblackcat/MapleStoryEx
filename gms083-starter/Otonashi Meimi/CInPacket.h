#pragma once
#include <ZXString.h>

class CInPacketEx;

class CInPacket
{
	friend CInPacketEx;
public:
	CInPacket();
	CInPacket(CInPacket& in);
	CInPacket* operator= (const CInPacket& obj);  
	~CInPacket();

public:
	char Decode1();
	short Decode2();
	unsigned long Decode4();
	int DecodeBuffer(unsigned char* out, int len);
	unsigned char* DecodeStr(ZXString<char>* p);
	int DecryptData(int unknow);

//private: 
public:
	int m_nuknow0 = 0;
	int m_nuknow4 = 0;
	unsigned char* m_membuffer = 0;
	unsigned char m_buffer_len = 0;
	unsigned char m_nuknowD = 0;
	unsigned char m_nuknowE = 0;
	unsigned char m_nuknowF = 0;
	int m_nuknow10 = 0;
	int m_current_buffer_pos = 0; 
};