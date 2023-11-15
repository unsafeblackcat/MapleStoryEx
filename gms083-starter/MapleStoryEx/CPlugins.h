#pragma once

#include <string>
#include <list>

typedef void (__cdecl *pfun_init)();

class CPlugins
{
public:
    CPlugins(const std::wstring& current_dir);
    virtual ~CPlugins();

    void load();

private:
    void enum_plugins();

    void load_ex();

private:
    std::wstring m_plugins_dir;

    std::list<std::wstring> m_plugins;
};

