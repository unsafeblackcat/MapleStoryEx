#pragma once
#include "community.h"
#include "CRoleHook.h"

#include <vector>
 

typedef int(__cdecl* pfun_CRole_decode1)(int, int);
typedef int(__cdecl* pfun_CRole_decode2)(int, int);

typedef void (__stdcall *pfun_role_hp_mp_monitor)(size_t hp, size_t hp_max, size_t mp, size_t mp_max);
 
class EXPORT CRole
{
    friend CRoleHook;

public:
    static CRole* m_this;
    static CRole* pins();

private:
    CRole();
    virtual ~CRole();

public:
    const char* get_name();
    int get_leval();

    short get_hp();
    int get_hp_max();

    short get_mp();
    int get_mp_max();

    int get_exp();
    int get_exp_max();

public:
    void reg_hp_mp_monitor(pfun_role_hp_mp_monitor callback); 
 
private:
    pfun_CRole_decode1 m_decode1;
    pfun_CRole_decode2 m_decode2;

private:
    int m_role_base;
    int m_role_base2;
    int m_offset;

private:
    std::vector<pfun_role_hp_mp_monitor> m_monitor_hp_mp; 
    CRoleHook m_role_hook;
};