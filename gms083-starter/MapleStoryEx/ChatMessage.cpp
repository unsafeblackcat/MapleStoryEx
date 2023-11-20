#include "ChatMessage.h"

#include <ZXString.h>

typedef void(__stdcall* pfun_send_msg)(char**, int);
static pfun_send_msg g_send_msg = nullptr;


void init()
{
    if (g_send_msg == nullptr)
    {
        g_send_msg = (pfun_send_msg)0x0052C315;
    } 

    return;
}

EXPORT 
void 
ChatMessage::send(
    const char* psz)
{
    init();

    ZXString<char> msg(psz);
    g_send_msg((char**)&msg, 0);
    return;
}