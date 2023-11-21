#include "DebugTest.h"
#include "Hook.h"
#include "memory.h"
#include <stdio.h>

#include "ChatMessage.h" 

typedef int (__fastcall *pfun_onkey)(void* pthis, int dummy, int wparam, int lparam);
pfun_onkey g_on_key = (pfun_onkey)0x00529968;


int key = 0;
typedef int (__fastcall *pfun_skills)(void* pthis, int dummy, int id, int param1, int param2);
pfun_skills g_skills = (pfun_skills)0x00966F7A;
 
DebugTest::DebugTest()
{    
    void* fun = nullptr;
    __asm {
        mov eax, DebugTest::onkey
        mov fun, eax
    }
    chook(&(PVOID&)g_on_key, fun);
     
    //主动释放技能
    memory::read(0x00BEBF98, key); 
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
        if (wparam == 48)
        { 
            int key_pos = lparam >> 16;
            key_pos = 0x1E;

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
        }
    } 
    return g_on_key(this, 0, wparam, lparam);
}
 