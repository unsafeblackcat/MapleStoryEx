#pragma once
 
struct tagChannel
{
	ZXString<char>* m_name;
	int m_ChannelCapacity;
	int m_word_id;
	int m_ChannelID;
	int m_AdultChannel;
};

struct tagOnWorldInformation
{
	int m_serverId;
	ZXString<char>* m_server_name;
	int m_flag;
	ZXString<char>* m_event_msg;
	int m_rate_modifier;
	int m_rate_modifier2;
	int m_unknow1;
	tagChannel* m_channel;
};


/**
*	À´Ô´: CClientSocket::ProcessPacket
*	[dword_BEDED4] + 8 == Clogin
**/ 
class Clogin
{
	Clogin() {}
	~Clogin() {}

	tagOnWorldInformation* m_offset_18C; // 1. CLogin::OnWorldInformation
};

