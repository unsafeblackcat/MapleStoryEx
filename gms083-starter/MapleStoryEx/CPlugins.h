#pragma once

#include <string>
#include <list>

typedef void (__cdecl *pfun_init)();
typedef void (__cdecl* pfun_show)();

class CPlugins
{
public:
    static CPlugins* m_this;
    static CPlugins* pins();

private:
    CPlugins(const std::wstring& current_dir);
    virtual ~CPlugins();

public:
    void load();

    void show();

private:
    void enum_plugins();

    void load_ex();

private:
    std::wstring m_plugins_dir;

    std::list<std::wstring> m_plugins;
};

