#pragma once
class CClientLoginPassord
{
public:
	CClientLoginPassord() {};
	virtual ~CClientLoginPassord() {};

public:
	int				m_protocol = CLIENT_LOGIN_PASSWORD;
	short			m_login_user_lenth;
	unsigned char	m_login_user[1];		//ʵ�ʳ�����m_login_user_lenth����
	short			m_login_password_length;
	unsigned char	m_login_password[1];	//ʵ�ʳ�����m_login_password_length����
	unsigned char	m_machine_id[0x10];	//����ID�̶�����
	int				m_game_room_client = 0;			//�̶�ֵ
	unsigned char	m_unknow = 2;			//�̶�ֵ��
	unsigned char	m_unknow1 = 0;		//�̶�ֵ
	unsigned char	m_unknow2 = 0;		//�̶�ֵ
	int				m_partner_code = 0;				//������飬�̶�ֵ
};

