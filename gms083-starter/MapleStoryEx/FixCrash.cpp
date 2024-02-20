#include "FixCrash.h"       
#include "Hook.h"
#include <string>
#include <string.h>

#include <windows.h>

extern std::string g_current_dir;

typedef HMODULE (WINAPI *pfunLoadLibraryA)(_In_ LPCSTR lpLibFileName);
pfunLoadLibraryA g_LoadLibraryA = nullptr;


HMODULE WINAPI HookLoadLibraryA(
    _In_ LPCSTR lpLibFileName)
{   
    if (stricmp(lpLibFileName, "PCOM.dll") == 0)
    {
        HMODULE hmodule = GetModuleHandle(L"msvcrt.dll");
        if (hmodule == NULL)
        {
            MessageBox(0, L"111", 0, 0);
            g_LoadLibraryA("msvcrt.dll");
            if (hmodule == NULL)
            {
                MessageBox(0, L"222", 0, 0);
            }
        }

        std::string dll_path;
        dll_path = g_current_dir + lpLibFileName;   
        return g_LoadLibraryA(dll_path.c_str());
    }

    return g_LoadLibraryA(lpLibFileName);
}
                
void 
fix_crash::fix_load_pcom_crash()
{
    do 
    {      
        HMODULE hmodule = ::GetModuleHandle(L"Kernel32.dll");
        if (hmodule == NULL)
        {
            break;
        }       

        g_LoadLibraryA = (pfunLoadLibraryA)::GetProcAddress(hmodule, "LoadLibraryA");
        if (g_LoadLibraryA)
        {
            chook(&(PVOID&)g_LoadLibraryA, HookLoadLibraryA);     
        }
    } while (false);

    return;
}