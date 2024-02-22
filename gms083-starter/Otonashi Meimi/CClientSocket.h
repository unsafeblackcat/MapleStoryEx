#pragma once
#include "COutPacket.h"
#include "CInPacket.h"

class CClientSocket
{
public:
	static CClientSocket* m_this;
	static CClientSocket* pins();

private:
	CClientSocket();
	virtual ~CClientSocket();
	  
public:
	void SendPacket(COutPacket* out_pack);

private: 
	void init();

	void hook_recv();

	int ProcessPacket(CInPacket* in_pack);
};