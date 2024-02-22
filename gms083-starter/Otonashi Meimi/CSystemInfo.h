#pragma once
class CSystemInfo
{
public:
	CSystemInfo(); 

	unsigned char* Init();
	unsigned char* GetMachineId();
	int GetGameRoomClient(); 

private: 
	unsigned char m_unknow[36];
};