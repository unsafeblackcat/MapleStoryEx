#define WIN32_LEAN_AND_MEAN
#include "Hook.h"
#include <windows.h>
#include <detours.h>
 
int 
chook(
    PVOID* old_address
    , PVOID new_address)
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread()); 
    DetourAttach(old_address, new_address); 
    DetourTransactionCommit();
    return 0;
}