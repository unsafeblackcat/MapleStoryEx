#include "DebugTest.h"
#include "Hook.h"
#include <stdio.h>


typedef int(__fastcall *pfun_sub_8D850B)(void* pthis, int dummy, int, int, int, int, int, int Unknown, char* pcVal);
pfun_sub_8D850B g_sub_8D850B;

typedef int (__fastcall *pfun_onkey)(void* pthis, int dummy, int wparam, int lparam);
pfun_onkey g_on_key;

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
    printf("%d/%d, %d/%d,  %d %d %s \n", current_hp, max_hp, current_mp, max_mp, exp, exp_max, pcVal);
    return g_sub_8D850B(this, 0, current_hp, max_hp, current_mp, max_mp, exp, exp_max, pcVal);
}

int 
DebugTest::onkey(
    int wparam
    , int lparam)
{
    printf("%c -- %c \n", wparam, lparam);
    return g_on_key(this, 0, wparam, lparam);
}