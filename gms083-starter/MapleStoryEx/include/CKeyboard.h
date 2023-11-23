#pragma once

#include "community.h"

#include <list>

typedef int(__stdcall* pfun_keyboard_callback)(int wparam, int lparam);

class EXPORT CKeyboard
{
public:
    CKeyboard();
    virtual ~CKeyboard();

    void regedit(pfun_keyboard_callback cb);

private:
    int onkey(int wparam, int lparam);
};

