// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <community.h>
#include <CFunction.h>
#include "key.h"

#include <stdio.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

CEXPORT void __cdecl init()
{ 
    CFunction::pins()->reg_commandinput_callback(Key::command_input);
    return;
}

CEXPORT void __cdecl show()
{
    CFunction::pins()->sendmsg("自动按键"); 
    CFunction::pins()->sendmsg("!key.auto.start:    开启自动按键");
    CFunction::pins()->sendmsg("!key.auto.stop:     停止自动按键");
    CFunction::pins()->sendmsg("!key.auto:          配置自动按键");
    CFunction::pins()->sendmsg("!key.auto 按键,秒数,\"可选项的消息\"");
    CFunction::pins()->sendmsg("    按键: 键盘上的某个按键.");
    CFunction::pins()->sendmsg("    秒数: 需要多少秒自动触发一次按键.");
    CFunction::pins()->sendmsg("    可选项的消息: 当自动触发按键时可以选择向世界发送一条消息.");
    CFunction::pins()->sendmsg("例子: !key.auto:a,120,魔法盾"); 
    CFunction::pins()->sendmsg("设置自动按键，每120秒触发一次按键a，并且向世界发送消息 \"魔法盾\"");
    CFunction::pins()->sendmsg("备注: 请使用英文输入法状态下的 逗号, 冒号 和 双引号"); 
    CFunction::pins()->sendmsg("直接按键: a~z,0~1");
    CFunction::pins()->sendmsg("特殊按键: F1~F12 使用数字ID(112~123)");
    CFunction::pins()->sendmsg("特殊按键: ~     使用数字ID 192");
    CFunction::pins()->sendmsg("特殊按键: ATL   使用数字ID 18");
    CFunction::pins()->sendmsg("特殊按键: CTRL  使用数字ID 17");
    CFunction::pins()->sendmsg("特殊按键: Ins   使用数字ID 45");
    CFunction::pins()->sendmsg("特殊按键: Hm    使用数字ID 36");
    CFunction::pins()->sendmsg("特殊按键: Pup   使用数字ID 33");
    CFunction::pins()->sendmsg("特殊按键: Del   使用数字ID 46");
    CFunction::pins()->sendmsg("特殊按键: End   使用数字ID 35");
    CFunction::pins()->sendmsg("特殊按键: Pdn   使用数字ID 34");
    return;
}

CEXPORT void __cdecl check()
{
    printf("key show \n");
    return;
}