#pragma once

class CRoleHook
{
public:
    static CRoleHook* m_this;
    static CRoleHook* pins();

private:
    CRoleHook();
    virtual ~CRoleHook();

    //人物HP,MP当前显示 sub_8D850B
    int hook_role_hp_mp(int current_hp
        , int max_hp
        , int current_mp
        , int max_mp
        , int exp
        , int exp_max
        , char* pcVal);
};