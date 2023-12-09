#include "CIni.h"

CIni::CIni(
    const char* path)
{
    m_path = path;
}


CIni::~CIni()
{ 
}

int 
CIni::write_int(
    const char* node
    , const char* key
    , int value)
{
    char psz[256] = { 0x0 };
    sprintf(psz, "%d", value);

    BOOL bret = ::WritePrivateProfileStringA(node, key, psz, m_path.c_str());
    return (bret) ? 0 : 1;
}

int 
CIni::read_int(
    const char* node
    , const char* key
    , int& value)
{
    char vret[256] = "";
    BOOL bret = ::GetPrivateProfileStringA(node, key, "", vret, 256, m_path.c_str()); 
    value = atoi(vret);
    return (bret) ? 0 : 1;
}

int 
CIni::write_string(
    const char* node
    , const char* key
    , const char* value)
{
    BOOL bret = ::WritePrivateProfileStringA(node, key, value, m_path.c_str());
    return (bret) ? 0 : 1;
}

int 
CIni::read_string(
    const char* node
    , const char* key
    , std::string& value)
{
    char vret[256] = "";
    BOOL bret = ::GetPrivateProfileStringA(node, key, "", vret, 256, m_path.c_str());
    value = vret;
    return (bret) ? 0 : 1;
}