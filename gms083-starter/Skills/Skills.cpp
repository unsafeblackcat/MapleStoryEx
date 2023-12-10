#include "Skills.h" 

#include <process.h>
#include <time.h>

#include <community.h>
#include <algorithm>

#include <CFunction.h>
#include <CIni.h>
  
unsigned
__stdcall
start_work(LPVOID lpParam)
{ 
    Skills::pins()->start_workex();
    return 0;
}

Skills* Skills::m_this = nullptr;
Skills* Skills::pins()
{
    if (m_this == nullptr)
    {
        m_this = new Skills;
    }

    return m_this;
}

Skills::Skills()
{ 
    _beginthreadex(nullptr, 0, start_work, nullptr, 0, nullptr);
}

Skills::~Skills()
{ 
}
 
void 
Skills::start_workex()
{
    do 
    {
        ::Sleep(800);

        if (!m_start)
        {
            continue;
        }
        
        { 
            AutoMutex a(&m_mutex);
            for (auto& it : m_auto_key)
            {
                trigger_button(it);
                ::Sleep(1000);
            }
        }


    } while (true);

    return;
}

void
Skills::read_ini()
{ 
    { 
        AutoMutex a(&m_mutex);
        auto it = m_auto_key.begin();
        for (it; it != m_auto_key.end(); )
        {
            it = m_auto_key.erase(it);
        } 
    }
     
    std::string Skillsini;
    Skillsini = m_current_dir + m_play_role_name + "_Skills.ini";
    CIni ini(Skillsini.c_str());

    int count = 0;
    ini.read_int("main", "count", count);
      
    for (int i = 0; i < count; i++)
    { 
        char node[256] = { 0x0 };
        sprintf(node, "%d", i + 1);
         
        int idel = 0;
        ini.read_int(node, "delete", idel);
        if (idel)
        {
            continue;
        }

        KeyConfig kc;

        ini.read_int(node, "key", kc.m_key_id);
        ini.read_int(node, "time", kc.m_time);
        ini.read_string(node, "msg", kc.m_msg);

        add_work_list(kc);
    } 

    work((count != 0)? true : false); 
    return;
}
  
int 
__stdcall 
Skills::command_input(
    const char* psz)
{
#define IS_COMMAND(cm) (command.compare(0, cm.length(), cm) == 0)

    int iret = 1;

    std::string command(psz);
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
      
    std::string Skills_log_start("!skills.log.start");
    std::string Skills_log_stop("!skills.log.stop");
    std::string Skills_auto_start("!skills.auto.start");
    std::string Skills_auto_stop("!skills.auto.stop");
    std::string Skills_auto_show("!skills.auto.show");
    std::string Skills_auto_delete("!skills.auto.delete:");
    std::string Skills_auto("!skills.auto:");

    if (IS_COMMAND(Skills_log_start))
    {
        Skills::pins()->set_log(true);
    }
    else if (IS_COMMAND(Skills_log_stop))
    {
        Skills::pins()->set_log(false);
    }
    else if (IS_COMMAND(Skills_auto_start))
    {
        Skills::pins()->work(true);
    }
    else if (IS_COMMAND(Skills_auto_stop))
    {
        Skills::pins()->work(false);
    }
    else if (IS_COMMAND(Skills_auto_show))
    {
        Skills::pins()->auto_show();
    }
    else if (IS_COMMAND(Skills_auto_delete))
    {
        command.replace(0, Skills_auto_delete.length(), "");
        Skills::pins()->auto_delete(command);
    }
    else if (IS_COMMAND(Skills_auto))
    {
        command.replace(0, Skills_auto.length(), "");
        Skills::pins()->auto_config(command);
    }
    else
    {
        iret = 0;
    }

    return iret;
}

void 
Skills::auto_show()
{
    AutoMutex a(&m_mutex);

    int i = 1;
    for (auto& it : m_auto_key)
    {
        char msg[1024] = { 0x0 };
        sprintf(msg, "index=%d: Skills=%C,time=%d,msg=%s", i, it.m_key_id, it.m_time, it.m_msg.c_str());
        CFunction::pins()->sendmsg(msg);
    }
}

void 
Skills::auto_delete(
    const std::string& cfg)
{
    AutoMutex a(&m_mutex);
    
    int index = atoi(cfg.c_str());
    int i = 1;

    auto it = m_auto_key.begin();
    for (it; it != m_auto_key.end(); it++)
    {
        if (i == index)
        {
            std::string Skillsini;
            Skillsini = m_current_dir + m_play_role_name + "_Skills.ini";
            CIni ini(Skillsini.c_str());

            char node[256] = { 0x0 };
            sprintf(node, "%d", i); 
            ini.write_int(node, "delete", 1);

            m_auto_key.erase(it);
            break;
        }
    } 
    return;
}

void 
Skills::auto_config(
    const std::string& cfg)
{
    std::vector<std::string> cut_command;
    cut_skills_config(cfg, cut_command);
    if (cut_command.empty())
    {
        return;
    }
     
    KeyConfig kc;
    init_skills_config(cut_command, kc);
      
    add_config(kc);
      
    add_work_list(kc);
    return;
}

void 
Skills::cut_skills_config(
    const std::string& cfg
    , std::vector<std::string>& cut)
{
    std::string command(cfg);
    size_t pos = 0; 
    do
    {
        pos = command.find(",", pos);
        if (pos == -1)
        {
            break;
        }

        std::string str(command.substr(0, pos));
        if (!str.empty())
        {
            cut.push_back(str);
        } 
        command.replace(0, pos + 1, "");
    } while (true);

    if (cfg.length())
    {
        cut.push_back(command);
    }
    return;
}

void 
Skills::init_skills_config(
    std::vector<std::string>& cut
    , KeyConfig& kc)
{
    if (cut.size() >= 2)
    {
        if (cut[0].length() == 1)
        {
            kc.m_key_id = toupper(cut[0][0]);
        } 
        else
        {
            kc.m_key_id = atoi(cut[0].c_str());
        }
         
        kc.m_time = atoi(cut[1].c_str());
    }

    if (cut.size() == 3)
    {
        kc.m_msg = cut[2];
    }
    return;
} 

void 
Skills::add_config(
    const KeyConfig& kc)
{
    std::string Skillsini;
    Skillsini = m_current_dir + m_play_role_name + "_Skills.ini";
    CIni ini(Skillsini.c_str());
     
    int count = 0;
    ini.read_int("main", "count", count);

    count++;
    ini.write_int("main", "count", count);

    char node[256] = { 0x0 };
    sprintf(node, "%d", count);

    ini.write_int(node, "key", kc.m_key_id);
    ini.write_int(node, "time", kc.m_time);
    ini.write_string(node, "msg", kc.m_msg.c_str()); 
    return; 
}

void
Skills::trigger_button(
    KeyConfig& kc)
{  
    DWORD current_tick = time(nullptr);

    if ((kc.m_last_time == 0)
        || (kc.m_last_time + kc.m_time) < current_tick)
    {
        int key_id = KEY_CODE(kc.m_key_id);
          
        DWORD iret = CFunction::pins()->skills(key_id);
        if (iret == 0) 
        {
            CFunction::pins()->block_keyboard_input(true);
            ::Sleep(1000);
            iret = CFunction::pins()->skills(key_id);
            CFunction::pins()->block_keyboard_input(false);
        }

        if (iret)
        {
            if (!kc.m_msg.empty())
            {
                CFunction::pins()->sendmsg(kc.m_msg.c_str());
            }

            kc.m_last_time = current_tick;
        }
    }
    return;
}

void 
Skills::add_work_list(
    const KeyConfig& kc)
{
    bool bfind = true;

    AutoMutex a(&m_mutex);      
    for (auto& it : m_auto_key)
    {
        if (it.m_key_id == kc.m_key_id)
        {
            it = kc;
            bfind = false;
            break;
        }
    }

    if (bfind)
    {
        m_auto_key.push_back(kc);
    }

    return;
} 