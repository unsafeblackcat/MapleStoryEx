#pragma once
#include "community.h" 

#include <string>

class EXPORT CGlobal
{
public:
    static CGlobal* m_this;
    static CGlobal* pins(); 

private:
    CGlobal();
    virtual ~CGlobal();

public:
    void init();

    inline const std::wstring& get_current_dir() { return m_current_dir; };
    
    inline HMODULE get_maplestory() { return m_MapleStory_moduel; }

private:
    void init_path();

    void init_console();

private: 
    HMODULE m_MapleStory_moduel;

    std::wstring m_current_dir;
};

