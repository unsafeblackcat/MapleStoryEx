#include "CKeyboard.h"
#include <Hook.h> 
#include "CMutex.h"

typedef int(__fastcall* pfun_onkey)(void* pthis, int dummy, int wparam, int lparam);
static pfun_onkey g_on_key = nullptr;
static CMutex g_mutex;

static std::list<pfun_keyboard_callback> m_callback;

CKeyboard::CKeyboard()
{
    void* fun = nullptr;
    __asm {
        mov eax, CKeyboard::onkey
        mov fun, eax
    }

    g_on_key = (pfun_onkey)0x00529968;
    chook(&(PVOID&)g_on_key, fun);

    m_callback.clear();
}

CKeyboard::~CKeyboard()
{ 
}

void 
CKeyboard::regedit(
    pfun_keyboard_callback cb)
{
    AutoMutex a(&g_mutex);
    m_callback.push_back(cb);
    return;
}

int 
CKeyboard::onkey(
    int wparam
    , int lparam)
{
    {
        AutoMutex a(&g_mutex);
        for (auto& it : m_callback)
        {
            it(wparam, lparam);
        }
    }

    return g_on_key(this, 0, wparam, lparam);
}