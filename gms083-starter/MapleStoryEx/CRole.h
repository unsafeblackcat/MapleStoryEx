#pragma once
#include "community.h" 
#include "CMutex.h"
#include <vector>
 

typedef int(__cdecl* pfun_CRole_decode1)(int, int);
typedef int(__cdecl* pfun_CRole_decode2)(int, int);

typedef void (__stdcall *pfun_role_hp_mp_monitor)(size_t hp, size_t hp_max, size_t mp, size_t mp_max);
 
class EXPORT CRole
{ 
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
    //人物HP,MP当前显示 sub_8D850B
    int hook_role_hp_mp(int current_hp
        , int max_hp
        , int current_mp
        , int max_mp
        , int exp
        , int exp_max
        , char* pcVal);

private:
    pfun_CRole_decode1 m_decode1;
    pfun_CRole_decode2 m_decode2;

private:
    int m_role_base;
    int m_role_base2;
    int m_offset;

private:
    std::vector<pfun_role_hp_mp_monitor> m_monitor_hp_mp;
    CMutex m_mutex;
};