#define WIN32_LEAN_AND_MEAN
#include "CSystemInfo.h"

typedef void (__fastcall* pfunCSystemInfo)(void* pthis, int dummy);
typedef void (__fastcall* pfunUnCSystemInfo)(void* pthis, int dummy);
typedef unsigned char* (__fastcall* pfunCSystemInfo_Init)(void* pthis, int dummy);
typedef unsigned char* (__fastcall* pfunCSystemInfo_GetMachineId)(void* pthis, int dummy);
typedef int (__fastcall* pfunCSystemInfo_GetGameRoomClient)(void* pthis, int dummy);

static pfunCSystemInfo g_CSystemInfo = nullptr;
static pfunUnCSystemInfo g_UnCSystemInfo = nullptr;
static pfunCSystemInfo_Init g_CSystemInfo_Init = nullptr;
static pfunCSystemInfo_GetMachineId g_CSystemInfo_GetMachineId = nullptr;
static pfunCSystemInfo_GetGameRoomClient g_CSystemInfo_GetGameRoomClient = nullptr;


CSystemInfo::CSystemInfo()
{
	if (g_CSystemInfo == nullptr)
	{ 
		g_CSystemInfo = (pfunCSystemInfo)0x00A54B90;
	}

	if (g_UnCSystemInfo == nullptr)
	{
		g_UnCSystemInfo = (pfunUnCSystemInfo)0x00A54BA0;
	}

	if (g_CSystemInfo_Init == nullptr)
	{
		g_CSystemInfo_Init = (pfunCSystemInfo_Init)0x00A54BD0;
	}

	if (g_CSystemInfo_GetMachineId == nullptr)
	{
		g_CSystemInfo_GetMachineId = (pfunCSystemInfo_GetMachineId)0x00A54EB0;
	}

	if (g_CSystemInfo_GetGameRoomClient == nullptr)
	{
		g_CSystemInfo_GetGameRoomClient = (pfunCSystemInfo_GetGameRoomClient)0x00A54FB0;
	}

	g_CSystemInfo(this, 0);
	return ;
}


unsigned char* 
CSystemInfo::Init()
{
	return g_CSystemInfo_Init(this, 0);
}

unsigned char* 
CSystemInfo::GetMachineId()
{
	return g_CSystemInfo_GetMachineId(this, 0);
}

int 
CSystemInfo::GetGameRoomClient()
{
	return g_CSystemInfo_GetGameRoomClient(this, 0);
}