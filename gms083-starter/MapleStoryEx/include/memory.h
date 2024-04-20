#pragma once
#include "community.h"

namespace memory
{
    EXPORT int read(size_t address, int& out);

    EXPORT int read(size_t address, unsigned char& out);

    EXPORT int read(size_t address, unsigned char* out, size_t size);

    EXPORT int write(size_t address, unsigned char ch);

    EXPORT int write(size_t address, unsigned int value);
};

