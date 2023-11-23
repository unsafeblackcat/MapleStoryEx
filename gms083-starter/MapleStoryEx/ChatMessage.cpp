#include "ChatMessage.h"
#include "Hook.h"
#include <ZXString.h>

#include <list>
static std::list<pfunsend_msg_callback> m_callback;

typedef void(__stdcall* pfun_send_msg)(char**, int);
static pfun_send_msg g_send_msg = nullptr;
 
ChatMessage* ChatMessage::m_this = nullptr;
ChatMessage* ChatMessage::pins()
{
    if (m_this == nullptr)
    {
        m_this = new ChatMessage;
    }

    return m_this;
}

ChatMessage::ChatMessage()
{
    g_send_msg = (pfun_send_msg)0x0052C315;

    chook(&(PVOID&)g_send_msg, ChatMessage::send_msg_callback);
}

ChatMessage::~ChatMessage()
{ 
}

void 
ChatMessage::regedit(
    pfunsend_msg_callback cb)
{
    m_callback.push_back(cb);
}
   
void 
ChatMessage::send(
    const char* psz)
{ 
    ZXString<char> msg(psz);
    g_send_msg((char**)&msg, 0);
    return;
}


void 
ChatMessage::send_msg_callback(
    char** lparam
    , int wparam)
{  
    for (auto& it : m_callback)
    {
        it((char*)lparam);
    }
    return g_send_msg(lparam, wparam);
}