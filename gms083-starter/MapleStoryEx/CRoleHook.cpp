#include "CRoleHook.h"
#include "CRole.h"
#include <Hook.h>
#include "CMutex.h"

typedef int(__fastcall *pfun_role_hp_mp)(void* pthis, int dummy, int, int, int, int, int, int Unknown, char* pcVal);
pfun_role_hp_mp g_role_hp_mp = (pfun_role_hp_mp)0x8D850B;

CRoleHook* CRoleHook::m_this = nullptr;
CRoleHook* CRoleHook::pins()
{
    if (m_this == nullptr)
    {
        m_this = new CRoleHook;
    }

    return m_this;
}

CRoleHook::CRoleHook()
{  
    void* fun = nullptr;  
    __asm {
        mov eax, CRoleHook::hook_role_hp_mp
        mov fun, eax
    }
     
    chook(&(PVOID&)g_role_hp_mp, fun);
}

CRoleHook::~CRoleHook()
{

}

int
CRoleHook::hook_role_hp_mp(
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