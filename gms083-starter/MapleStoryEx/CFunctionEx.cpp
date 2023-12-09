#include "CFunctionEx.h"
#include "memory.h"
#include "ZXString.h"


typedef void(__stdcall* pfun_send_msg)(char**, int);
extern pfun_send_msg g_send_msg;
 
CFunctionEx::CFunctionEx()
{ 
    m_skills = (pfun_skills)0x00966F7A;
}

CFunctionEx::~CFunctionEx()
{ 
}


void 
CFunctionEx::skills(
    int lparam
    , bool bskill)
{
    if (bskill)
    {
        int key_pos = lparam;
        int* value = 0;
        memory::read(0x00BED5A0, (int&)value);
        if (value != 0)
        {
            char* pos = (char*)(value + key_pos);
            pos += key_pos + 4 + 1;

            int skills_this = 0;
            memory::read(0x00BEBF98, skills_this);
            if (skills_this)
            {
                m_skills((void*)skills_this, 0, *((int*)pos), 0, 0);
            }
        }
    }
    else
    {
        int skills_this = 0;
        memory::read(0x00BEBF98, skills_this);
        if (skills_this)
        {
            m_skills((void*)skills_this, 0, lparam, 0, 0);
        }
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