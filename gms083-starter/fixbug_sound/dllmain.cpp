// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <memory.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: 
        {
            HMODULE module = ::GetModuleHandle(NULL);
            DWORD address = (DWORD)module + 0x3FD55;
            DWORD offset = 0x016C;

			memory::write(address, (unsigned char)0xe9);
			memory::write(address + 1, (unsigned int)offset);

            break;
        } 
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

