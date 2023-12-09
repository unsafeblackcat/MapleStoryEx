// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <community.h>
#include <CFunction.h>
#include "Skills.h"

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

CEXPORT void __cdecl init(const char* current_dir, const char* play_role_name)
{
    Skills::pins()->set_dir(current_dir);
    Skills::pins()->set_play_role_name(play_role_name);
    Skills::pins()->read_ini();
    CFunction::pins()->reg_commandinput_callback(Skills::command_input);
    return;
}

CEXPORT void __cdecl show()
{
    CFunction::pins()->sendmsg("定时技能释放"); 
    CFunction::pins()->sendmsg("!skills.auto.start:            开启定时自动技能释放");
    CFunction::pins()->sendmsg("!skills.auto.stop:             停止定时自动技能释放");
    CFunction::pins()->sendmsg("!skills.auto:                  配置自动技能释放");
    CFunction::pins()->sendmsg("!skills.auto.show:             显示自动技能配置");
    CFunction::pins()->sendmsg("!skills.auto.delete:[index]:   删除指定索引配置");
    CFunction::pins()->sendmsg(" ");
    CFunction::pins()->sendmsg("!skills.auto:按键,秒数,\"可选项的消息\"");
    CFunction::pins()->sendmsg("    按键: 需要自动释放技能的键盘按键.");
    CFunction::pins()->sendmsg("    秒数: 需要多少秒自动触发一次技能释放.");
    CFunction::pins()->sendmsg("    可选项的消息: 当自动触发技能时可以选择向世界发送一条消息.");
    CFunction::pins()->sendmsg("例子: !skills.auto:a,120,魔法盾"); 
    CFunction::pins()->sendmsg("设置自动释放技能，每120秒触发一次按键a上面的技能，并且向世界发送消息 \"魔法盾\"");
    CFunction::pins()->sendmsg("备注: 请使用英文输入法状态下的 逗号, 冒号");
    CFunction::pins()->sendmsg("特殊按键以对应的数字ID替换字符");
    CFunction::pins()->sendmsg("特殊按键: F1~F12 使用数字ID(112~123)");
    CFunction::pins()->sendmsg("特殊按键: ~      使用数字ID 192");
    CFunction::pins()->sendmsg("特殊按键: ATL    使用数字ID 18");
    CFunction::pins()->sendmsg("特殊按键: CTRL   使用数字ID 17");
    CFunction::pins()->sendmsg("特殊按键: Ins    使用数字ID 45");
    CFunction::pins()->sendmsg("特殊按键: Hm     使用数字ID 36");
    CFunction::pins()->sendmsg("特殊按键: Pup    使用数字ID 33");
    CFunction::pins()->sendmsg("特殊按键: Del    使用数字ID 46");
    CFunction::pins()->sendmsg("特殊按键: End    使用数字ID 35");
    CFunction::pins()->sendmsg("特殊按键: Pdn    使用数字ID 34");
    return;
}

CEXPORT void __cdecl check()
{
    printf("key show \n");
    return;
}

CEXPORT void __cdecl reload_play_name(
    const char* play_role_name)
{
    Skills::pins()->set_play_role_name(play_role_name);
    Skills::pins()->read_ini();
    return;
}