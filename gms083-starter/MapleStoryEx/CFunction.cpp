#include "CFunction.h" 
#include "CFunctionEx.h" 
#include "CRole.h"
#include "CKeyboard.h"
#include "CommandInput.h" 

CFunctionEx* m_fex = nullptr;

CFunction* CFunction::m_this = nullptr;
CFunction* CFunction::pins()
{
    if (m_this == nullptr)
    {
        m_this = new CFunction;
    }

    return m_this;
}

CFunction::CFunction()
{
    m_fex = new CFunctionEx;
}

CFunction::~CFunction()
{ 
}

void 
CFunction::skills(
    int id
    , bool bkey)
{ 
    return m_fex->skills(id, bkey);
}

void 
CFunction::sendmsg(
    const char* psz)
{
    m_fex->send_msg(psz);
}

const char* 
CFunction::role_name()
{
    return CRole::pins()->get_name();
}

int 
CFunction::role_get_hp()
{
    return CRole::pins()->get_hp();
}

int 
CFunction::role_get_hp_max()
{
    return CRole::pins()->get_hp_max();
}

int 
CFunction::role_get_mp()
{
    return CRole::pins()->get_mp();
}

int 
CFunction::role_get_mp_max()
{
    return CRole::pins()->get_mp_max(); 
}

int 
CFunction::role_get_exp()
{
    return CRole::pins()->get_exp();
}

int 
CFunction::role_get_exp_max()
{
    return CRole::pins()->get_exp_max();
}

void 
CFunction::reg_hp_mp_monitor(
    pfun_role_hp_mp_monitor cb)
{
    CRole::pins()->reg_hp_mp_monitor(cb);
    return;
}

void 
CFunction::reg_keyboard_callback(
    pfun_keyboard_callback cb)
{
    CKeyboard::pins()->regedit(cb);
}

void 
CFunction::reg_commandinput_callback(
    pfun_command_input cb)
{
    CommandInput::pins()->regedit(cb);
    return;
}