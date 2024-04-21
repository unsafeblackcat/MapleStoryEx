// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <Hook.h>
#include <process.h>
 
unsigned __stdcall start_work(LPVOID lpParam);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: 
        _beginthreadex(nullptr, 0, start_work, nullptr, 0, nullptr); 
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

typedef int(_stdcall* pfunTextInputHostCreate)(int p1, int p2, int p3);
pfunTextInputHostCreate g_pfunTextInputHostCreate = nullptr;

int _stdcall HookTextInputHostCreate(int p1, int p2, int p3)
{
	return 0;
}

unsigned __stdcall start_work(LPVOID lpParam)
{   
	do
	{
		Sleep(100); 

		HMODULE hmodule = ::GetModuleHandle(L"textinputframework.dll");
		if (hmodule)
		{
			g_pfunTextInputHostCreate = (pfunTextInputHostCreate)::GetProcAddress(hmodule, "TextInputHostCreate");
			if (g_pfunTextInputHostCreate)
			{
				chook(&(PVOID&)g_pfunTextInputHostCreate, HookTextInputHostCreate);
				break;
			}
		} 
	} while (true);
	return 0;
}