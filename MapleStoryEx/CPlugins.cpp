#include "pch.h"
#include "CPlugins.h"

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
    for (auto& it : m_plugins)
    {
        HMODULE pit = ::LoadLibraryW(it.c_str());
        if (pit)
        {
            pfun_init pfun = (pfun_init)::GetProcAddress(pit, "init");
            if (pfun)
            {
                pfun();
            }
        }
    }

    return;
}