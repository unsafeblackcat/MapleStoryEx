#pragma once
class CSystemInfo
{
public:
	CSystemInfo();
	virtual ~CSystemInfo();

	unsigned char* Init();
	unsigned char* GetMachineId();
	int GetGameRoomClient(); 

private:
	char m_unknow[36];
};