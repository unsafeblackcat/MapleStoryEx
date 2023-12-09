#include "pch.h"
#include "CPlugins.h"
#include "CGlobal.h"
#include "CFunction.h"

#include <codecvt>

CPlugins* CPlugins::m_this = nullptr;
CPlugins* CPlugins::pins()
{
    if (m_this == nullptr)
    {
        m_this = new CPlugins(CGlobal::pins()->get_current_dir());
    }

    return m_this;
}

CPlugins::CPlugins(
    const std::wstring& current_dir)
{
    m_plugins_dir = current_dir + L"plugins\\";
}

CPlugins::~CPlugins()
{
}

void 
CPlugins::load()
{
    enum_plugins();
    load_ex();
    return;
}

void 
CPlugins::enum_plugins()
{
    if (m_plugins_dir.empty())
    {
        return;
    }

    std::wstring plugins_dir;
    plugins_dir = m_plugins_dir + L"*";
    
    WIN32_FIND_DATAW fd = {0x0};
    HANDLE handle = ::FindFirstFileW(plugins_dir.c_str(), &fd);
    if (handle)
    {
        BOOL bret = FALSE;
        do 
        {
            std::wstring file(fd.cFileName);
            if ((file.compare(L".") == 0)
                || (file.compare(L"..") == 0))
            {
            }
            else
            { 
                if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                {
                    size_t pos = file.rfind(L".");
                    if (pos != -1)
                    {
                        std::wstring suffix = file.substr(pos + 1);
                        if (wcsncmp(suffix.c_str(), L"dll", 3) == 0)
                        {
                            std::wstring dll;
                            dll = m_plugins_dir + file;
                            m_plugins.push_back(dll);
                        }
                    }
                }
            }

            memset(&fd, 0x0, sizeof(WIN32_FIND_DATAW));
            bret = ::FindNextFileW(handle, &fd);
        } while (bret);

        ::FindClose(handle);
    }
    else
    {

    }
     
    return;
}

void 
CPlugins::load_ex()
{
    std::string current_dir;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    current_dir = converter.to_bytes(m_plugins_dir);

    for (auto& it : m_plugins)
    {
        HMODULE pit = ::LoadLibraryW(it.c_str());
        if (pit)
        {
            pfun_init pfun = (pfun_init)::GetProcAddress(pit, "init");
            if (pfun)
            {
                pfun(current_dir.c_str(), CFunction::pins()->role_name());
            }
        }
    }

    return;
}

void 
CPlugins::show()
{
    for (auto& it : m_plugins)
    {
        HMODULE pit = ::GetModuleHandle(it.c_str());
        if (pit)
        {
            pfun_show pfun = (pfun_show)::GetProcAddress(pit, "show");
            if (pfun)
            {
                pfun();
            }
        }
    }
}

void 
CPlugins::replay_role()
{
    for (auto& it : m_plugins)
    {
        HMODULE pit = ::GetModuleHandle(it.c_str());
        if (pit)
        {
            pfun_reload_play_name pfun = (pfun_reload_play_name)::GetProcAddress(pit, "reload_play_name");
            if (pfun)
            {
                pfun(CFunction::pins()->role_name());
            }
        }
    }

    return;
}