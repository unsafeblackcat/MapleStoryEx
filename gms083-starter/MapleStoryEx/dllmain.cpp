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

#include <imm.h>  
#pragma comment (lib ,"imm32.lib") 
HIMC g_hIMC = NULL;


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
 
#include "memory.h"
#include "CKeyboard.h"
#include "CommandInput.h"

unsigned __stdcall start_work(LPVOID lpParam)
{
	CGlobal::pins()->init();
	CPlugins::pins()->load();
    //CRole::pins();
    //CFunction::pins(); 
    //CKeyboard::pins();
    //CommandInput::pins();  

    char current_play_role_name[64] = { 0x0 };
    strcpy(current_play_role_name, CFunction::pins()->role_name());
     
//     CFunction::pins()->sendmsg("~~~~~~~~MapleStoryEx扩展插件启动!~~~~~~~~");
//     CFunction::pins()->sendmsg("~~~~~~~~!help 显示可用插件的帮助命令.~~~~~~~~");
//     CFunction::pins()->sendmsg("~~~~~~~~!show 显示所有当前已加载的插件介绍和命令.~~~~~~~~");
     
    do 
    {
        Sleep(1000); 
//         const char* play_role_name = CFunction::pins()->role_name();
//         if ((play_role_name != nullptr) && (strlen(play_role_name) != 0))
//         {
//             if (strcmp(current_play_role_name, play_role_name) != 0)
//             {
//                 //玩家切换了角色
//                 CPlugins::pins()->replay_role();
//                 strcpy(current_play_role_name, CFunction::pins()->role_name());
//             }
//         }
    } while (true);
    return 0;
} 