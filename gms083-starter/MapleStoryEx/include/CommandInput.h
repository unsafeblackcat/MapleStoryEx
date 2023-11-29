#pragma once 

typedef void(__stdcall* pfun_command_input)(const char* psz);

class CommandInput
{
public:
    static CommandInput* m_this;
    static CommandInput* pins();

private:
    CommandInput();
    virtual ~CommandInput();

public:
    void regedit(pfun_command_input cb);
     
private:
    static void msg_callback(char** psz, int wparam); 
};