#define WIN32_LEAN_AND_MEAN
#include "CMutex.h"
 
CMutex::CMutex()
{
    ::InitializeCriticalSection(&m_mutex);
}

CMutex::~CMutex()
{
    ::DeleteCriticalSection(&m_mutex);
}

void 
CMutex::lock()
{
    ::EnterCriticalSection(&m_mutex);
}

void 
CMutex::unlock()
{
    ::LeaveCriticalSection(&m_mutex);
}

AutoMutex::AutoMutex(
    CMutex* mutex)
{
    m_mutex = mutex;
    m_mutex->lock();
}

AutoMutex::~AutoMutex()
{
    m_mutex->unlock();
}