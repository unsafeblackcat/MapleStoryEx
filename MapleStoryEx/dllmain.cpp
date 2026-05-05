// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <Windows.h>
#include <process.h>
#include "CClientSocket.h"

unsigned __stdcall start_work(LPVOID lpParam);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: 
	{  
		_beginthreadex(nullptr, 0, start_work, nullptr, 0, nullptr);
		Sleep(3000);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


unsigned __stdcall start_work(LPVOID lpParam)
{
    CClientSocket::pins();
    return 0;
} 