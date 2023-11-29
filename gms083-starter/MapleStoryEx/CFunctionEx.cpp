#include "CFunctionEx.h"
#include "memory.h"
#include "ZXString.h"


typedef void(__stdcall* pfun_send_msg)(char**, int);
extern pfun_send_msg g_send_msg;
 
CFunctionEx::CFunctionEx()
{
    memory::read(0x00BEBF98, m_skills_this);
}

CFunctionEx::~CFunctionEx()
{ 
}


void 
CFunctionEx::skills(
    int lparam
    , bool bkey)
{
    if (bkey)
    {
        int key_pos = lparam >> 16;
        int* value = 0;
        memory::read(0x00BED5A0, (int&)value);
        if (value != 0)
        {
            char* pos = (char*)(value + key_pos);
            pos += key_pos + 4 + 1; 
            m_skills((void*)m_skills_this, 0, *((int*)pos), 0, 0);
        }
    }
    else
    {
        m_skills((void*)m_skills_this, 0, lparam, 0, 0);
    } 
    return;
}

void 
CFunctionEx::send_msg(
    const char* psz)
{
    ZXString<char> msg(psz);
    g_send_msg((char**)&msg, 0);
    return;
}