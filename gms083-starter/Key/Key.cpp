#include "Key.h" 
#include <community.h>
#include <algorithm>

Key* Key::m_this = nullptr;
Key* Key::pins()
{
    if (m_this == nullptr)
    {
        m_this = new Key;
    }

    return m_this;
}

Key::Key()
{ 
}

Key::~Key()
{ 
}

int 
__stdcall 
Key::command_input(
    const char* psz)
{

#define IS_COMMAND(cm) (command.compare(0, cm.length(), cm) == 0)

    int iret = 1;

    std::string command(psz);
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
      
    std::string Key_log_start("!key.log.start");
    std::string Key_log_stop("!key.log.stop");
    std::string Key_auto_start("!key.auto.start");
    std::string Key_auto_stop("!key.auto.stop");
    std::string Key_auto("!key.auto:");

    if (IS_COMMAND(Key_log_start))
    {
        Key::pins()->set_log(true);
    }
    else if (IS_COMMAND(Key_log_stop))
    {
        Key::pins()->set_log(false);
    }
    else if (IS_COMMAND(Key_auto_start))
    {
        Key::pins()->work(true);
    }
    else if (IS_COMMAND(Key_auto_stop))
    {
        Key::pins()->work(false);
    }
    else if (IS_COMMAND(Key_auto))
    {
        command.replace(0, Key_auto.length(), "");
        Key::pins()->auto_config(command);
    }
    else
    {
        iret = 0;
    }

    return iret;
}

void 
Key::auto_config(
    const std::string& cfg)
{
    std::vector<std::string> cut_command;
    cut_key_config(cfg, cut_command);
    if (cut_command.empty())
    {
        return;
    }
     
    KeyConfig kc;
    init_key_config(cut_command, kc);
    
    trigger_button(kc);

    add_config(kc);
     
    add_work_list(kc);
    return;
}

void 
Key::cut_key_config(
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
Key::init_key_config(
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
Key::trigger_button(
    const KeyConfig& kc)
{
    return;
}

void 
Key::add_config(
    const KeyConfig& kc)
{
    return;
}

void 
Key::add_work_list(
    const KeyConfig& kc)
{
    AutoMutex a(&m_mutex);
    m_auto_key.push_back(kc);
    return;
}