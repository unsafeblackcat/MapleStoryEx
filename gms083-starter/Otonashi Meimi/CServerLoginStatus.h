#pragma once
#include "CProtocol.h"

class CServerLoginStatus
{
public:
	CServerLoginStatus() {};
	~CServerLoginStatus() {}; 

public:  
	int		m_head;
	short	m_login_status = SERVER_LOGIN_STATUS;		//��¼״̬Э��ͷ
	char	m_unknow;
	char	m_unknow1;
	int		m_unknow2;
	int		m_account_id;		//�˻�ID
	char	m_gender;			//�Ա�: 0Ů,1��
	char	m_is_gm_account;	//�Ƿ���GM�˻�
	char	m_gm_level;			//GM�˻��ȼ�
	char	m_country_code;		//���Ҵ��룿ŷ��������
	short	m_account_len;		//�˻�����,�˻���󳤶�ֻ����12�ֽ�
	char	m_account[13];		//��¼�˻�, ������ֽڳ��ȸ��� m_account_len�Ĳ�ͬ����ͬ���������12�ֽ�
	char	m_unknow3;
	char	m_is_ban;				//�˻��Ƿ񱻽���
	char	m_ban_time_stamp[8];		//�˻�����ʱ�� 
	char	m_creation_time_stamp[8];	//
	int		m_remove_select_world_hint;	//�Ƴ�ѡ���������
	char	m_is_pin;				//�Ƿ���pin
	char	m_pin_status;			//pin״̬, ֻ�е�pin��ֵʱ����Ч
};

