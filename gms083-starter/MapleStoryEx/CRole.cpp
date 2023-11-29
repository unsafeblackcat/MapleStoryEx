#include "CRole.h"
#include <memory.h>

#include "CMutex.h"
#include "Hook.h"

typedef int(__fastcall* pfun_role_hp_mp)(void* pthis, int dummy, int, int, int, int, int, int Unknown, char* pcVal);
pfun_role_hp_mp g_role_hp_mp = (pfun_role_hp_mp)0x8D850B;
 
CRole* CRole::m_this = nullptr;
CRole* CRole::pins()
{
    if (m_this == nullptr)
    {
        m_this = new CRole;
    }

    return m_this;
}

CRole::CRole()
{
    m_role_base = 0;
    do 
    {
        Sleep(1000);
        memory::read(0xBE7918, m_role_base);
    } while (m_role_base == 0);  

    m_offset = 0x20B8;

    do 
    {
        Sleep(1000);
        memory::read(m_role_base + m_offset, m_role_base2);
    } while (m_role_base2 == 0);

    m_decode1 = (pfun_CRole_decode1)0x00416563;
    m_decode2 = (pfun_CRole_decode2)0x004746DD; 


    void* fun = nullptr;
    __asm {
        mov eax, CRole::hook_role_hp_mp
        mov fun, eax
    } 
    chook(&(PVOID&)g_role_hp_mp, fun);
}

CRole::~CRole()
{
}

const char* 
CRole::get_name()
{
    return (const char*)(m_role_base2 + 0x4);
}

int 
CRole::get_leval()
{
    //还拿不到
    return 0;
}

short
CRole::get_hp()
{
    int param1 = m_role_base2 + 0x61;
    int param2 = 0;
    memory::read(m_role_base2 + 0x65, param2);
     
    return m_decode2(param1, param2);
}

int 
CRole::get_hp_max()
{
    int param1 = m_role_base + 0x211C;
    int param2 = 0;
    memory::read(m_role_base + 0x2124, param2);
     
    return m_decode1(param1, param2);
}
 
short
CRole::get_mp()
{
    int param1 = m_role_base2 + 0x71;
    int param2 = 0;
    memory::read(m_role_base2 + 0x75, param2);
     
    return m_decode2(param1, param2);
}

int 
CRole::get_mp_max()
{
    int param1 = m_role_base + 0x2128;
    int param2 = 0;
    memory::read(m_role_base + 0x2130, param2);
     
    return m_decode1(param1, param2);
}
 
int 
CRole::get_exp()
{
    int param1 = m_role_base2 + 0x91;
    int param2 = 0;
    memory::read(m_role_base2 + 0x99, param2); 
    return m_decode1(param1, param2);
}

int 
CRole::get_exp_max()
{  
    unsigned char ch = 0; 
     
    memory::read(m_role_base2 + 0x33, ch);
    int t33 = ch; 

    memory::read(m_role_base2 + 0x34, ch);
    int t34 = ch;
     
    return ((DWORD*)(0xBEF230))[t33 ^ t34];
}

void 
CRole::reg_hp_mp_monitor(
    pfun_role_hp_mp_monitor callback)
{  
    AutoMutex a(&m_mutex);
    m_monitor_hp_mp.push_back(callback);
    return;
} 

int
CRole::hook_role_hp_mp(
    int current_hp
    , int max_hp
    , int current_mp
    , int max_mp
    , int exp
    , int exp_max
    , char* pcVal)
{
    int iret = g_role_hp_mp(this, 0, current_hp, max_hp, current_mp, max_mp, exp, exp_max, pcVal);

    AutoMutex a(&CRole::pins()->m_mutex);
    for (auto& it : CRole::pins()->m_monitor_hp_mp)
    {
        it(current_hp, max_hp, current_mp, max_mp);
    }
    return iret;
}