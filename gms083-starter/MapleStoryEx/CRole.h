#pragma once
#include "community.h"

typedef int(__cdecl* pfun_CRole_decode1)(int, int);
typedef int(__cdecl* pfun_CRole_decode2)(int, int);
 
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

private:
    pfun_CRole_decode1 m_decode1;
    pfun_CRole_decode2 m_decode2;

private:
    int m_role_base;
    int m_role_base2;
    int m_offset;
};

