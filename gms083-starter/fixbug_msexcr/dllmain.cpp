// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <Hook.h>
#include <string>

typedef HANDLE (WINAPI *pfunCreateFileA)(_In_ LPCSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile);
pfunCreateFileA g_CreateFileA = nullptr;


HANDLE 
WINAPI HookCreateFileA(
    _In_ LPCSTR lpFileName
    , _In_ DWORD dwDesiredAccess
    , _In_ DWORD dwShareMode
    , _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
    , _In_ DWORD dwCreationDisposition
    , _In_ DWORD dwFlagsAndAttributes
    , _In_opt_ HANDLE hTemplateFile)
{
    std::string msexcr(lpFileName);
    int pos = msexcr.find("msexcr.ini");
    if (pos != -1)
    { 
        dwCreationDisposition = OPEN_ALWAYS;
    }

	HANDLE handle = g_CreateFileA(
		lpFileName
		, dwDesiredAccess
		, dwShareMode
		, lpSecurityAttributes
		, dwCreationDisposition
		, dwFlagsAndAttributes
		, hTemplateFile
	); 
    return handle;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_CreateFileA = CreateFileA;
        chook((PVOID*)&g_CreateFileA, HookCreateFileA);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

