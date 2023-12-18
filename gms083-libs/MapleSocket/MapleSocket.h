#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>

#define PORT 8484


class MapleSocket
{
public:
	MapleSocket();
	virtual ~MapleSocket();

private:
	int m_iSock_Client;
	sockaddr_in m_stServer_Addr;
	int m_iAddr_len;
	char m_cMsg[1024];
	bool GetIpAddress(char* pIpaddress);
	bool InitWinsock();
public:
	bool ConnectServer(int iPort, std::string strIp);
};