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
        m_last_time = 0;
    };
    KeyConfig(const KeyConfig& obj) {
        m_key_id = obj.m_key_id;
        m_time = obj.m_time;
        m_msg = obj.m_msg;
        m_last_time = obj.m_last_time;
    };
    KeyConfig& operator=(const KeyConfig& obj)
    {
        m_key_id = obj.m_key_id;
        m_time = obj.m_time;
        m_msg = obj.m_msg;
        m_last_time = obj.m_last_time;
        return *this;
    } 
    virtual ~KeyConfig() {};
     
    int m_key_id;
    int m_time;
    std::string m_msg;

    int m_last_time;
};

class Skills
{
    friend  unsigned __stdcall start_work(LPVOID lpParam);

public:
    static Skills* m_this;
    static Skills* pins();
      
private:
    Skills();
    virtual ~Skills();
     
    void start_workex();
       
public:
    inline void set_dir(const char* path) { m_current_dir = path; };

    inline void set_play_role_name(const char* role) { m_play_role_name = role; }

    void read_ini();

    static int __stdcall command_input(const char* psz);

    inline void set_log(bool status) { m_log = status; }

    inline void work(bool status) { m_start = status; }

    void auto_show();

    void auto_delete(const std::string& cfg);

    void auto_config(const std::string& cfg);

    void init_skills_config(std::vector<std::string>& cut, KeyConfig& kc);

private:
    
    void cut_skills_config(const std::string& cfg, std::vector<std::string>& cut);
      
    void add_config(const KeyConfig& kc);
     
    void trigger_button(KeyConfig& kc);

    void add_work_list(const KeyConfig& kc);
      
private:
    std::string m_current_dir;
    std::string m_play_role_name;

    bool m_log = false;
      
    bool m_start = false;

    CMutex m_mutex;
    std::list<KeyConfig> m_auto_key;
};