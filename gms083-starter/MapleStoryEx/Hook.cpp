#include <Hook.h>
#include <windows.h>
#include <detours.h>

EXPORT 
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