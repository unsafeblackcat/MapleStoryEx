#pragma once
#include "community.h"
#include <windows.h>

#include <string>

class EXPORT CIni
{
public:
    CIni(const char* path);
    virtual ~CIni();

    int write_int(const char* node, const char* key, int value);

    int read_int(const char* node, const char* key, int& value);

    int write_string(const char* node, const char* key, const char* value);

    int read_string(const char* node, const char* key, std::string& value);

private:
    std::string m_path;
};

