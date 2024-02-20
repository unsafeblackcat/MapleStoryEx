#include "memory.h"

int 
memory::read(
    size_t address
    , int& out)
{
    memcpy((void*)&out, (void*)address, sizeof(int));
    return 0;
}
 
int 
memory::read(
    size_t address
    , unsigned char& out)
{
    memcpy((void*)&out, (void*)address, sizeof(unsigned char));
    return 0;
}
 
int 
memory::read(
    size_t address
    , unsigned char* out
    , size_t size)
{
    memcpy((void*)&out, (void*)address, size);
    return 0;
}