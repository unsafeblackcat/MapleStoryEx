#pragma once 
#include <windows.h>

class CMutex
{
public:
    CMutex();
    virtual ~CMutex();

    void lock();
    void unlock();

private:
    CRITICAL_SECTION m_mutex;
};


class AutoMutex
{
public:
    AutoMutex(CMutex* mutex);
    virtual ~AutoMutex();

private:
    CMutex* m_mutex;
};

