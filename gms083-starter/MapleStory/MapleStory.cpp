// MapleStory.cpp : Defines the entry point for the application.
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "framework.h"
#include "MapleStory.h"

#include <string>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    HMODULE hmodule = GetModuleHandle(nullptr);
    
    wchar_t file_name[MAX_PATH]; 
    GetModuleFileName(hmodule, file_name, MAX_PATH);

    std::wstring str_path(file_name); 
    size_t pos = str_path.rfind(L"\\");
    if (pos != -1)
    {
        str_path = str_path.substr(0, pos + 1);
        
        std::wstring MapleStory;
        std::wstring MapleStoryEx;

        MapleStory = str_path + L"MapleStory.exe";
        MapleStoryEx = str_path + L"MapleStoryEx.dll";

        STARTUPINFO si = { 0x0 };
        si.cb = sizeof(si);
        PROCESS_INFORMATION pi = {0x0};
          
        BOOL bret = CreateProcessW(
            MapleStory.c_str()
            , L""
            , NULL
            , NULL
            , FALSE
            , CREATE_NEW_CONSOLE | CREATE_SUSPENDED
            , NULL
            , NULL
            , &si
            , &pi); 
        if (bret)
        {
            LPVOID premote_buffer = VirtualAllocEx(
                pi.hProcess
                , 0
                , (MapleStoryEx.length() * sizeof(wchar_t) + 100)
                , MEM_COMMIT
                , PAGE_READWRITE);
            if (premote_buffer)
            {
                SIZE_T write_size = 0;
                bret = WriteProcessMemory(
                    pi.hProcess
                    , premote_buffer
                    , MapleStoryEx.c_str()
                    , MapleStoryEx.length() * sizeof(wchar_t)
                    , &write_size);
                if (bret)
                { 
                    HANDLE remote_thread = CreateRemoteThread(
                        pi.hProcess
                        , nullptr
                        , 0
                        , (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW")
                        , premote_buffer
                        , 0
                        , nullptr);
                    if (remote_thread)
                    {
                        WaitForSingleObject(remote_thread, INFINITE); 
                        CloseHandle(remote_thread);  
                    }
                    else
                    {
                        std::wstring err;
                        err = L"扩展插件无法加载, 无法创建远程线程！ 错误码: " + GetLastError();
                        MessageBoxW(0, err.c_str(), L"MapleStory.exe", 0);
                    }
                }
                else
                {
                    std::wstring err;
                    err = L"扩展插件无法加载, 无法写入内存数据！ 错误码: " + GetLastError();
                    MessageBoxW(0, err.c_str(), L"MapleStory.exe", 0);
                }
            }
            else
            {
                std::wstring err;
                err = L"扩展插件无法加载, 无法申请远程内存！ 错误码: " + GetLastError();
                MessageBoxW(0, err.c_str(), L"MapleStory.exe", 0);
            }

            ResumeThread(pi.hThread);
            CloseHandle(pi.hProcess);
        }
        else
        {
            std::wstring err;
            err = L"扩展插件无法加载！ 错误码: " + GetLastError();
            MessageBoxW(0, err.c_str(), L"MapleStory.exe", 0);
        }

    }
    else
    {
        MessageBoxW(0, L"MapleStory.exe启动失败!", 0, 0);
    }

    return 0;
}