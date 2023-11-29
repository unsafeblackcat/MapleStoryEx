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

private:
    int onkey(int wparam, int lparam);
};

