#pragma once
#include <list>

typedef int(__stdcall* pfun_keyboard_callback)(int wparam, int lparam);

class CKeyboard
{
public:
    static CKeyboard* m_this;
    static CKeyboard* pins();

private:
    CKeyboard();
    virtual ~CKeyboard();

public:
    void regedit(pfun_keyboard_callback cb);

    void block_input(bool status) { m_block_input = status; }

private:
    int onkey(int wparam, int lparam);

private:
    volatile bool m_block_input = false;
};

