#include <process.h>

#include "CommandInput.h"
#include "Hook.h"
#include <ZXString.h>

#include "CMutex.h"
#include "CFunction.h"
#include "CPlugins.h"

#include <list>
static std::list<pfun_command_input> m_callback;
static CMutex g_mutex_call_back;

static std::list<std::string> g_msg;
static CMutex g_mutex_msg;

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


    _beginthreadex(nullptr, 0, CommandInput::dispath_thread, nullptr, 0, nullptr);
}

CommandInput::~CommandInput()
{ 
}

void 
CommandInput::regedit(
    pfun_command_input cb)
{
    AutoMutex a(&g_mutex_call_back);
    m_callback.push_back(cb);
}
 
void 
CommandInput::msg_callback(
    char** lparam
    , int wparam)
{
    ZXString<char>* psz = *(ZXString<char> **)lparam;
    const char* psz2 = (const char*)psz;
      
    if (psz2[0] == '!')
    {
        std::string str(psz2);
        AutoMutex a(&g_mutex_msg); 
        g_msg.push_back(str);
    }
     
    return g_send_msg(lparam, wparam);
}

unsigned 
__stdcall 
CommandInput::dispath_thread(
    LPVOID lpParam)
{
    do 
    {
        Sleep(1000);

        std::list<std::string> command;

        {
            AutoMutex a(&g_mutex_msg);
            if (g_msg.size())
            {
                command.swap(g_msg);
            }
        }

        if (command.empty())
        {
            continue;
        }

        for (auto& it : command)
        {
            if (it.compare("!help") == 0)
            { 
                CFunction::pins()->sendmsg("!help 显示插件内置命令."); 
                CFunction::pins()->sendmsg("!show 显示所有插件介绍."); 
                CFunction::pins()->sendmsg("!check 显示所有插件状态(是否正在开启).");
            }
            else if (it.compare("!show") == 0)
            {
                CPlugins::pins()->show();
            }
            else
            {
                AutoMutex a(&g_mutex_call_back);
                for (auto& cb : m_callback)
                {
                    if (cb(it.c_str()))
                    {
                        break;
                   }
                }
            }
        }
         
    } while (true);

    return 0;
}