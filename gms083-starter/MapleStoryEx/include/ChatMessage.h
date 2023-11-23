#pragma once 

typedef void(__stdcall* pfunsend_msg_callback)(const char* psz);

class ChatMessage
{
public:
    static ChatMessage* m_this;
    static ChatMessage* pins();

private:
    ChatMessage();
    virtual ~ChatMessage();

public:
    void regedit(pfunsend_msg_callback cb);

    void send(const char* psz);
      
private:
    static void send_msg_callback(char** psz, int wparam);
     
};