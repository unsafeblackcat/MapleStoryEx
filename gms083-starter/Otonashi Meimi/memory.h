#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


namespace memory
{
    int read(size_t address, int& out);

    int read(size_t address, unsigned char& out);

    int read(size_t address, unsigned char* out, size_t size);
};

