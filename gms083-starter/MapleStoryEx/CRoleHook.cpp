#include "CRoleHook.h"
#include "CRole.h"
#include <Hook.h>

typedef int(__fastcall* pfun_role_hp_mp)(void* pthis, int dummy, int, int, int, int, int, int Unknown, char* pcVal);
pfun_role_hp_mp g_role_hp_mp;

CRoleHook::CRoleHook()
{
    g_role_hp_mp = (pfun_role_hp_mp)0x8D850B;
    //CPP_HOOK(g_role_hp_mp, CRoleHook::hook_role_hp_mp);

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

    for (auto& it : CRole::pins()->m_monitor_hp_mp)
    {
        it(current_hp, max_hp, current_mp, max_mp);
    }
    return iret;
}