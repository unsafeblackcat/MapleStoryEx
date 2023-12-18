#include "MapleSocket.h"


#pragma comment(lib, "ws2_32.lib")

MapleSocket::MapleSocket()
{
    m_iSock_Client = -1;
	m_iAddr_len = sizeof(sockaddr_in);
	memset(m_cMsg, 0, sizeof(char) * 1024);
}
MapleSocket::~MapleSocket()
{

}


bool MapleSocket::GetIpAddress(char* pIpaddress)
{
	return true;
}
bool MapleSocket::InitWinsock()
{

}

bool MapleSocket::ConnectServer(int iPort, std::string strIp)
{


	return true;
}
