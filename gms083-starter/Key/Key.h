#pragma once
#include <string>
#include <list>
#include <vector>

#include <CMutex.h>

class KeyConfig
{
public:
    KeyConfig() {
        m_key_id = 0;
        m_time = 0;
        m_msg = "";
    };
    KeyConfig(const KeyConfig& obj) {
        m_key_id = obj.m_key_id;
        m_time = obj.m_time;
        m_msg = obj.m_msg;
    };
    KeyConfig& operator=(const KeyConfig& obj)
    {
        m_key_id = obj.m_key_id;
        m_time = obj.m_time;
        m_msg = obj.m_msg;
        return *this;
    } 
    virtual ~KeyConfig() {};
     
    int m_key_id;
    int m_time;
    std::string m_msg;
};

class Key
{
public:
    static Key* m_this;
    static Key* pins();

private:
    Key();
    virtual ~Key();

public:
    static int __stdcall command_input(const char* psz);

    inline void set_log(bool status) { m_log = status; }

    inline void work(bool status) { m_start = status; }

    void auto_config(const std::string& cfg);

    void init_key_config(std::vector<std::string>& cut, KeyConfig& kc);

private:
    void cut_key_config(const std::string& cfg, std::vector<std::string>& cut);
     
    void trigger_button(const KeyConfig& kc);

    void add_config(const KeyConfig& kc);

    void add_work_list(const KeyConfig& kc);

private:
    bool m_log = false;

    bool m_start = false;

    CMutex m_mutex;
    std::list<KeyConfig> m_auto_key;
};