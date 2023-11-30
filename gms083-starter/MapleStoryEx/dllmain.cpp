// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <Windows.h>
#include <process.h>

#include "CGlobal.h"
#include "CPlugins.h"
  
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
 
#include "memory.h"
#include "CKeyboard.h"
#include "CommandInput.h"

unsigned __stdcall start_work(LPVOID lpParam)
{
    CGlobal::pins()->init();
    CRole::pins();
    CFunction::pins(); 
    CKeyboard::pins();
    CommandInput::pins(); 
    CPlugins::pins()->load();
     
    CFunction::pins()->sendmsg("~~~~~~~~MapleStoryEx扩展插件启动!~~~~~~~~");
    CFunction::pins()->sendmsg("~~~~~~~~!help 显示可用插件的帮助命令.~~~~~~~~");
    CFunction::pins()->sendmsg("~~~~~~~~!show 显示所有当前已加载的插件介绍和命令.~~~~~~~~");

    do 
    {
        Sleep(1000); 
    } while (true);
    return 0;
}