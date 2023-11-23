// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <Windows.h>
#include <process.h>

#include "CGlobal.h"
#include "CPlugins.h"
 
#include "DebugTest.h"
#include "CRole.h"
#include "CKeyboard.h"
#include "CFunction.h"

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

typedef int(__fastcall* pfun_skills)(void* pthis, int dummy, int id, int param1, int param2);
extern pfun_skills g_skills;
extern int key;

#include "memory.h"

unsigned __stdcall start_work(LPVOID lpParam)
{
    CRole::pins();

    CGlobal::pins()->init();

    {
        CPlugins p(CGlobal::pins()->get_current_dir());
        p.load();
    }
     
    CKeyboard kb;
    CFunction::pins();

    DebugTest test;
     

    do 
    {
        Sleep(1000); 
    } while (true);
    return 0;
}