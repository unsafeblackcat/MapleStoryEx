#pragma once
#include "COutPacket.h"

class CClientSocket
{
public:
	static CClientSocket* m_this;
	static CClientSocket* pins();

private:
	CClientSocket();
	virtual ~CClientSocket();

	void init();

public:
	void SendPacket(COutPacket* out_pack);
};