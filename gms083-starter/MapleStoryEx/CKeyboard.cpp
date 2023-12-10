#include "CKeyboard.h"
#include <Hook.h> 
#include "CMutex.h"

typedef int(__fastcall* pfun_onkey)(void* pthis, int dummy, int wparam, int lparam);
static pfun_onkey g_on_key = nullptr;
static CMutex g_mutex;

static std::list<pfun_keyboard_callback> m_callback;

CKeyboard* CKeyboard::m_this = nullptr;
CKeyboard* CKeyboard::pins()
{
    if (m_this == nullptr)
    {
        m_this = new CKeyboard;
    }

    return m_this;
}

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
    printf("%d -- %08X \n", wparam, lparam);

    {
        AutoMutex a(&g_mutex);
        for (auto& it : m_callback)
        {
            it(wparam, lparam);
        }
    }

    if (CKeyboard::pins()->m_block_input)
    {
        return 0;
    }

    int iret = g_on_key(this, 0, wparam, lparam);
    return iret;
}