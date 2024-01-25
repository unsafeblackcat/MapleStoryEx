// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"           
#include <Windows.h>
#include <process.h>

unsigned __stdcall start_work(LPVOID lpParam);

BOOL 
APIENTRY 
DllMain( 
    HMODULE hModule
    , DWORD  ul_reason_for_call
    , LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        _beginthreadex(nullptr, 0, start_work, nullptr, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
} 

unsigned 
__stdcall 
start_work(
    LPVOID lpParam)
{

    do 
    {
        ::Sleep(1000);
    } while (true); 
    return 0;
}