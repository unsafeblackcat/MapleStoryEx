// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"           
#include <Windows.h>
#include <process.h>

unsigned __stdcall start_work(LPVOID lpParam);

BOOL 
APIENTRY 
DllMain( 
    HMODULE hModule
    , DWORD  ul_reason_for_call
    , LPVOID lpReserved)
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

#include "COutPacket.h"
#include "CClientSocket.h"
#include "CSystemInfo.h"
#include "CWvsApp.h"
#include "CConfig.h"

unsigned 
__stdcall 
start_work(
    LPVOID lpParam)
{
    while (1)
        ::Sleep(1000); 

	DWORD tdi = ::GetCurrentThreadId();

    CSystemInfo sysi;
	sysi.Init();  

	ZXString<char> user("admin");
	ZXString<char> password("admin");

    COutPacket loading(1);
    if (tdi)
	{ 
		loading.EncodeStr(user); 
		loading.EncodeStr(password); 
    }
    else
    { 
// 		char user[256] = "admin";
// 		char password[256] = "admin";
// 
// 		COutPacket loading(1);
// 		loading.EncodeStr(user);
// 		loading.EncodeStr(password);
// 
// 		loading.EncodeStr("admin");
// 		loading.EncodeStr("admin");

        struct _tagString
        {
            int m_max_buffer = 0;
            char m_str[0];
        };

        char name_buffer[256];
        _tagString* name = (_tagString*)name_buffer; 
	    strcpy(name->m_str, "admin");
        name->m_max_buffer = strlen("admin"); 
        loading.EncodeStr(name->m_str);


	    char password_buffer[256];
	    _tagString* password2 = (_tagString*)password_buffer; 
	    strcpy(password2->m_str, "admin");
	    password2->m_max_buffer = strlen("admin");
        loading.EncodeStr(password2->m_str);
    }
      
    unsigned char* pMachineId = sysi.GetMachineId();
    loading.EncodeBuffer(pMachineId, 0x10);

    int GameRoomClient = sysi.GetGameRoomClient();
    loading.Encode4(GameRoomClient);
    
    unsigned char* pCWvsApp = (unsigned char* )CWvsApp::pins();
    char ch = *(pCWvsApp + 0x24);
    loading.Encode1(ch);
    loading.Encode1(0);
    loading.Encode1(0);

	int ccpc = CConfig::pins()->GetPartnerCode();
	loading.Encode4(ccpc);

    CClientSocket::pins()->SendPacket(&loading);
     
    do 
    {
        ::Sleep(1000);
    } while (true); 
    return 0;
}