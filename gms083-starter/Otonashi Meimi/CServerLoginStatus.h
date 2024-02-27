#pragma once
#include "CProtocol.h"

class CServerLoginStatus
{
public:
	CServerLoginStatus() {};
	~CServerLoginStatus() {}; 

public:  
	int		m_head;
	short	m_login_status = SERVER_LOGIN_STATUS;		//登录状态协议头
	char	m_unknow;
	char	m_unknow1;
	int		m_unknow2;
	int		m_account_id;		//账户ID
	char	m_gender;			//性别: 0女,1男
	char	m_is_gm_account;	//是否是GM账户
	char	m_gm_level;			//GM账户等级
	char	m_country_code;		//国家代码？欧服美服？
	short	m_account_len;		//账户长度,账户最大长度只能是12字节
	char	m_account[13];		//登录账户, 这里的字节长度根据 m_account_len的不同而不同，最长不超过12字节
	char	m_unknow3;
	char	m_is_ban;				//账户是否被禁用
	char	m_ban_time_stamp[8];		//账户禁用时间 
	char	m_creation_time_stamp[8];	//
	int		m_remove_select_world_hint;	//移除选择世界界面
	char	m_is_pin;				//是否开启pin
	char	m_pin_status;			//pin状态, 只有当pin有值时才生效
};

