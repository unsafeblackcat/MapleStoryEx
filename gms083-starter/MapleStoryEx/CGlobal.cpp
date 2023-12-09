#include "pch.h"
#include "CGlobal.h"

#include <stdio.h>

CGlobal* CGlobal::m_this = nullptr;

CGlobal* 
CGlobal::pins()
{
    if (m_this == nullptr)
    {
        m_this = new CGlobal;
    }

    return m_this;
}

CGlobal::CGlobal()
{ 
}

CGlobal::~CGlobal()
{ 
}

void 
CGlobal::init()
{
    //init_console();
    init_path(); 
}

void 
CGlobal::init_path()
{ 
    m_MapleStory_moduel = GetModuleHandle(nullptr);

    wchar_t file_name[MAX_PATH];
    GetModuleFileName(m_MapleStory_moduel, file_name, MAX_PATH);

    std::wstring str_path(file_name);
    size_t pos = str_path.rfind(L"\\");
    if (pos != -1)
    {
        m_current_dir = str_path.substr(0, pos + 1);
    }

    return;
}

void 
CGlobal::init_console()
{ 
    AllocConsole();
    AttachConsole(GetCurrentProcessId());

    freopen("CON", "w", stdout);

    char cc[128];
    sprintf_s(cc, "Client: %i", GetCurrentProcessId());
    SetConsoleTitleA(cc);
    return;
}