#pragma once
class CClientLoginPassord
{
public:
	CClientLoginPassord() {};
	virtual ~CClientLoginPassord() {};

public:
	int				m_protocol = CLIENT_LOGIN_PASSWORD;
	short			m_login_user_lenth;
	unsigned char	m_login_user[1];		//实际长度由m_login_user_lenth决定
	short			m_login_password_length;
	unsigned char	m_login_password[1];	//实际长度由m_login_password_length决定
	unsigned char	m_machine_id[0x10];	//机器ID固定长度
	int				m_game_room_client = 0;			//固定值
	unsigned char	m_unknow = 2;			//固定值？
	unsigned char	m_unknow1 = 0;		//固定值
	unsigned char	m_unknow2 = 0;		//固定值
	int				m_partner_code = 0;				//合作伙伴，固定值
};

