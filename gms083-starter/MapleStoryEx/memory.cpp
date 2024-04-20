#include "memory.h"

EXPORT 
int 
memory::read(
    size_t address
    , int& out)
{
    memcpy((void*)&out, (void*)address, sizeof(int));
    return 0;
}

EXPORT 
int 
memory::read(
    size_t address
    , unsigned char& out)
{
    memcpy((void*)&out, (void*)address, sizeof(unsigned char));
    return 0;
}

EXPORT 
int 
memory::read(
    size_t address
    , unsigned char* out
    , size_t size)
{
    memcpy((void*)&out, (void*)address, size);
    return 0;
}

EXPORT 
int 
memory::write(
    size_t address
    , unsigned char ch)
{  
	DWORD dwOldProtect;
	VirtualProtect((LPVOID)address, sizeof(unsigned char), PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*(unsigned char*)address = ch;
	VirtualProtect((LPVOID)address, sizeof(unsigned char), dwOldProtect, &dwOldProtect); 
    return 0;
}

EXPORT
int 
memory::write(
    size_t address
    , unsigned int value)
{
	DWORD dwOldProtect;
	VirtualProtect((LPVOID)address, sizeof(unsigned char), PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*(unsigned int*)address = value;
	VirtualProtect((LPVOID)address, sizeof(unsigned char), dwOldProtect, &dwOldProtect);
    return 0;
}