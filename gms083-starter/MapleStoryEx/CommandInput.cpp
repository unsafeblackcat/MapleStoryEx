#include "CommandInput.h"
#include "Hook.h"
#include <ZXString.h>

#include "CMutex.h"

#include <list>
static std::list<pfun_command_input> m_callback;
static CMutex g_mutex;

typedef void(__stdcall* pfun_send_msg)(char**, int);
pfun_send_msg g_send_msg = nullptr;
 

CommandInput* CommandInput::m_this = nullptr;
CommandInput* CommandInput::pins()
{
    if (m_this == nullptr)
    {
        m_this = new CommandInput;
    }

    return m_this;
}

CommandInput::CommandInput()
{
    g_send_msg = (pfun_send_msg)0x0052C315;

    chook(&(PVOID&)g_send_msg, CommandInput::msg_callback);
}

CommandInput::~CommandInput()
{ 
}

void 
CommandInput::regedit(
    pfun_command_input cb)
{
    AutoMutex a(&g_mutex);
    m_callback.push_back(cb);
}
 
void 
CommandInput::msg_callback(
    char** lparam
    , int wparam)
{
    ZXString<char>* psz = *(ZXString<char> **)lparam;
    const char* psz2 = *psz;

    if (psz2[0] == '!')
    {
        AutoMutex a(&g_mutex);
        for (auto& it : m_callback)
        {
            it((char*)lparam);
        }
    }
     
    return g_send_msg(lparam, wparam);
}