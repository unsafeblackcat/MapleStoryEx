#include "DebugTest.h"
#include "Hook.h"
#include <stdio.h>


typedef int(__fastcall *pfun_sub_8D850B)(void* pthis, int dummy, int, int, int, int, int, int Unknown, char* pcVal);
pfun_sub_8D850B g_sub_8D850B;

typedef int (__fastcall *pfun_onkey)(void* pthis, int dummy, int wparam, int lparam);
pfun_onkey g_on_key;

typedef void(__stdcall* pfun_send_msg)(char**, int);
pfun_send_msg g_send_msg;

DebugTest::DebugTest()
{
    g_sub_8D850B = (pfun_sub_8D850B)0x8D850B;

    void* fun = nullptr;
    __asm {
        mov eax, DebugTest::sub_8D850B
        mov fun, eax
    }
    chook(&(PVOID&)g_sub_8D850B, fun);

    g_on_key = (pfun_onkey)0x00529968;

    fun = nullptr;
    __asm {
        mov eax, DebugTest::onkey
        mov fun, eax
    }
    chook(&(PVOID&)g_on_key, fun);

    g_send_msg = (pfun_send_msg)0x0052C315; 
    chook(&(PVOID&)g_send_msg, send_msg);
}

int 
DebugTest::sub_8D850B(
    int current_hp
    , int max_hp
    , int current_mp
    , int max_mp
    , int exp
    , int exp_max
    , char* pcVal)
{
    //printf("%d/%d, %d/%d,  %d %d %s \n", current_hp, max_hp, current_mp, max_mp, exp, exp_max, pcVal);
    return g_sub_8D850B(this, 0, current_hp, max_hp, current_mp, max_mp, exp, exp_max, pcVal);
}

#include <ZXString.h>

int 
DebugTest::onkey(
    int wparam
    , int lparam)
{ 
    if (lparam & 0x80000000)
    {
        printf("%d -- key up \n", wparam);
    }
    else
    {
        printf("%d -- key down \n", wparam);
        if (wparam == 88)
        { 
            ZXString<char> psz("mo fa shaung ji"); 
            g_send_msg((char**)&psz, 0);
        }
        if (wparam == 65)
        {
            ZXString<char> psz("mo fa dun");
            g_send_msg((char**)&psz, 0);
        }
    } 
    return g_on_key(this, 0, wparam, lparam);
}

void __stdcall send_msg(char** param1, int param2)
{ 
    printf("send msg %s  -- %d \n", *param1, param2);
    g_send_msg(param1, param2);
    return;
}