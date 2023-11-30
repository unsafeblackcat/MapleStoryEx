#pragma once 
#include "community.h"
#include <windows.h>

class EXPORT CMutex
{
public:
    CMutex();
    virtual ~CMutex();

    void lock();
    void unlock();

private:
    CRITICAL_SECTION m_mutex;
};


class EXPORT AutoMutex
{
public:
    AutoMutex(CMutex* mutex);
    virtual ~AutoMutex();

private:
    CMutex* m_mutex;
};

