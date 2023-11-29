#pragma once

typedef int(__fastcall* pfun_skills)(void* pthis, int dummy, int id, int param1, int param2);

class CFunctionEx
{
public:
    CFunctionEx();
    virtual ~CFunctionEx();

public:
    void skills(int lparam, bool bkey = true);

    void send_msg(const char* msg);

private:
    pfun_skills m_skills;
    int m_skills_this;
};

