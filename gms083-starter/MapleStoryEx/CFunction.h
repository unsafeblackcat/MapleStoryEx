#pragma once
#include "community.h"

class EXPORT CFunction
{
public:
    static CFunction* m_this;
    static CFunction* pins();

private:
    CFunction();
    virtual ~CFunction();

public:
    /**
        需要释放技能的

        lparam: 技能ID/按键ID
        
        bkey:true:   lparam为按键ID
             false:  lparam为技能ID
    **/
    void skills(int lparam, bool bkey = true);
     
    /**
        发送聊天消息
    **/
    void sendmsg(const char* psz);
};