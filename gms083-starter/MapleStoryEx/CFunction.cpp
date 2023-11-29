#include "CFunction.h" 
#include "CFunctionEx.h" 
 
CFunctionEx* m_fex = nullptr;

CFunction* CFunction::m_this = nullptr;
CFunction* CFunction::pins()
{
    if (m_this == nullptr)
    {
        m_this = new CFunction;
    }

    return m_this;
}

CFunction::CFunction()
{
    m_fex = new CFunctionEx;
}

CFunction::~CFunction()
{ 
}

void 
CFunction::skills(
    int id
    , bool bkey)
{ 
    return m_fex->skills(id, bkey);
}

void 
CFunction::sendmsg(
    const char* psz)
{
    m_fex->send_msg(psz);
}