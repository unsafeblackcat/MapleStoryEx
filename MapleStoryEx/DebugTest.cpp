#include "DebugTest.h"
#include "Hook.h"
#include <stdio.h>


typedef int(__fastcall *pfun_sub_8D850B)(void* pthis, int dummy, int, int, int, int, int, int Unknown, char* pcVal);
pfun_sub_8D850B g_sub_8D850B;

DebugTest::DebugTest()
{
    g_sub_8D850B = (pfun_sub_8D850B)0x8D850B;

    void* fun = nullptr;
    __asm {
        mov eax, DebugTest::sub_8D850B
        mov fun, eax
    }
    chook(&(PVOID&)g_sub_8D850B, fun);
}

int 
DebugTest::sub_8D850B(
    int current_hp
    , int max_hp
    , int current_mp
    , int max_mp
    , int p5
    , int Unknown
    , char* pcVal)
{
    printf("%d/%d, %d/%d,  %d %d %s \n", current_hp, max_hp, current_mp, max_mp, p5, Unknown, pcVal);
    return g_sub_8D850B(this, 0, current_hp, max_hp, current_mp, max_mp, p5, Unknown, pcVal);
}