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
}