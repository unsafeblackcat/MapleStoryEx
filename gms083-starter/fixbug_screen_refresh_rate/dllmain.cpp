// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <Hook.h>
#include <memory.h>

typedef void (_cdecl* pfunPcCreateObject_IWzPackage)(int param1, DWORD param2, DWORD param3);
pfunPcCreateObject_IWzPackage g_PcCreateObject_IWzPackage = nullptr;

void 
_cdecl 
HookPcCreateObject_IWzPackage(
    int param1
	, DWORD param2
	, DWORD param3)
{
    g_PcCreateObject_IWzPackage(param1, param2, param3);

    int screen_refresh_rate = 0;
    memory::read(0x00BF14EC, screen_refresh_rate);
    if (screen_refresh_rate != 0)
	{
		unsigned char* p = (unsigned char*)screen_refresh_rate;
		p[0x84] = 0x3C;
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_PcCreateObject_IWzPackage = (pfunPcCreateObject_IWzPackage)0x009FB0E9;
        chook((LPVOID*)&g_PcCreateObject_IWzPackage, HookPcCreateObject_IWzPackage);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

