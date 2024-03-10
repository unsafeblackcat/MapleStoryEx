#pragma once
#include <ZXString.h>
class CServerLoginServerList
{
public:
	CServerLoginServerList() {};
	~CServerLoginServerList() {};

public:
	int		m_head;
	short	m_server_list = SERVER_LOGIN_SERVERLIST;
	short	m_server_id;
	ZXString<char> m_server_name;
	short	m_flag;
	ZXString<char> m_server_msg;
	unsigned char	m_unknow1;
	unsigned char	m_unknow2;
	unsigned char	m_unknow3;
	unsigned char	m_unknow4; 
	unsigned char	m_unknow5[]; //Î´Öª³¤¶Èbuffer

};

