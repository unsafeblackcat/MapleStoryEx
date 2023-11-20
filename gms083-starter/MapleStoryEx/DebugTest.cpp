#include "DebugTest.h"
#include "Hook.h"
#include <stdio.h>

#include "ChatMessage.h"
 

typedef int (__fastcall *pfun_onkey)(void* pthis, int dummy, int wparam, int lparam);
pfun_onkey g_on_key;
 
DebugTest::DebugTest()
{  
    g_on_key = (pfun_onkey)0x00529968; 
    //CPP_HOOK(g_on_key, DebugTest::onkey);

    void* fun = nullptr;
    __asm {
        mov eax, DebugTest::onkey
        mov fun, eax
    }
    chook(&(PVOID&)g_on_key, fun);
}
  

int 
DebugTest::onkey(
    int wparam
    , int lparam)
{ 
    if (lparam & 0x80000000)
    {
        printf("%d -- %08X  key up \n", wparam, lparam);
    }
    else
    {
        printf("%d -- %08X key down \n", wparam, lparam);
        if (wparam == 88)
        {  
            ChatMessage::send("mo fa shaung ji");
        }
        if (wparam == 65)
        { 
            ChatMessage::send("mo fa dun");
        }
    } 
    return g_on_key(this, 0, wparam, lparam);
}
 