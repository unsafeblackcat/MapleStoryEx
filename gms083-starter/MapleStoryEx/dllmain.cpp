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

typedef int(__fastcall* pfun_skills)(void* pthis, int dummy, int id, int param1, int param2);
extern pfun_skills g_skills;
extern int key;

#include "memory.h"

unsigned __stdcall start_work(LPVOID lpParam)
{ 
    CGlobal::pins()->init();

    {
        CPlugins p(CGlobal::pins()->get_current_dir());
        p.load();
    }
    
    CRole::pins();

    DebugTest test;
    
    const char* name = CRole::pins()->get_name();
    int i = CRole::pins()->get_leval();
    i = CRole::pins()->get_exp();
    i = CRole::pins()->get_exp_max();
    i = CRole::pins()->get_hp();
    i = CRole::pins()->get_hp_max();
    i = CRole::pins()->get_mp();
    i = CRole::pins()->get_mp_max();

    do 
    {
        Sleep(1000);


        //外部技能调用，通过键盘回调得到按键参数通过全局变量来搜索到按键ID

        int key_pos = 0x1E;

        int* value = 0;
        memory::read(0x00BED5A0, (int&)value);
        if (value != 0)
        {
            char* pos = (char*)(value + key_pos);
            pos += key_pos + 4 + 1;
            g_skills((void*)key, 0, *((int*)pos), 0, 0);
        }

        Sleep(1000);

        key_pos = 0x20;

        value = 0;
        memory::read(0x00BED5A0, (int&)value);
        if (value != 0)
        {
            char* pos = (char*)(value + key_pos);
            pos += key_pos + 4 + 1;
            g_skills((void*)key, 0, *((int*)pos), 0, 0);
        }

    } while (true);
    return 0;
}