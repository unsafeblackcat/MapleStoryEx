// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <Windows.h>
#include <process.h>

#include "CGlobal.h"
#include "CPlugins.h"
 
#include "DebugTest.h"
#include "CRole.h"

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
    CGlobal::pins()->init();

    {
        CPlugins p(CGlobal::pins()->get_current_dir());
        p.load();
    }
  
    DebugTest test; 
     
    CRole::pins();
     
    int i = CRole::pins()->get_exp();
    i = CRole::pins()->get_exp_max();
    i = CRole::pins()->get_hp();
    i = CRole::pins()->get_hp_max();
    i = CRole::pins()->get_mp();
    i = CRole::pins()->get_mp_max();

    do 
    {
        Sleep(1000);
    } while (true);
    return 0;
}