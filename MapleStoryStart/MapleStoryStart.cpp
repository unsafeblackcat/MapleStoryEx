// MapleStoryStart.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "MapleStoryStart.h"
#include <string>
#include <detours.h>

static bool FileExistsW(const std::wstring& path)
{
    DWORD attrs = GetFileAttributesW(path.c_str());
    return attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY);
}

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

    char file_name_str[MAX_PATH];
    GetModuleFileNameA(hmodule, file_name_str, MAX_PATH);

    std::string str_path_str(file_name_str);
    std::wstring str_path(file_name);
    size_t pos = str_path.rfind(L"\\");
    if (pos != -1)
    {
        str_path = str_path.substr(0, pos + 1); 
        str_path_str = str_path_str.substr(0, pos + 1);

        std::wstring MapleStory;
        std::string MapleStoryEx;

        MapleStory = str_path + L"MapleStory.exe";
        if (!FileExistsW(MapleStory))
        {
            std::wstring parent = str_path;
            if (!parent.empty() && parent.back() == L'\\')
            {
                parent.pop_back();
            }
            const size_t parent_pos = parent.rfind(L'\\');
            if (parent_pos != std::wstring::npos)
            {
                parent = parent.substr(0, parent_pos + 1);
                const std::wstring parent_target = parent + L"MapleStory.exe";
                if (FileExistsW(parent_target))
                {
                    MapleStory = parent_target;
                }
            }
        }

        MapleStoryEx = str_path_str + "MapleStoryEx.dll";

        if (!FileExistsW(MapleStory))
        {
            MessageBoxW(nullptr, L"MapleStory.exe not found near MapleStoryStart.exe", L"MapleStoryStart", MB_ICONERROR);
            return 1;
        }
        if (!FileExistsW(std::wstring(MapleStoryEx.begin(), MapleStoryEx.end())))
        {
            MessageBoxW(nullptr, L"MapleStoryEx.dll not found near MapleStoryStart.exe", L"MapleStoryStart", MB_ICONERROR);
            return 1;
        }

        STARTUPINFOW si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
        si.cb = sizeof(STARTUPINFO);

        std::wstring GameLaunching;
        GameLaunching = str_path + L"MapleStory.exe";
        BOOL bret = DetourCreateProcessWithDllExW(
            MapleStory.c_str(),
            &GameLaunching[0],
            NULL,
            NULL,
            FALSE,
            CREATE_DEFAULT_ERROR_MODE,
            NULL,
            NULL,
            &si,
            &pi,
            MapleStoryEx.c_str(),
            NULL);
        if (!bret)
        {
            wchar_t msg[256] = {};
            wsprintfW(msg, L"DetourCreateProcessWithDllExW failed. GetLastError=%lu", GetLastError());
            MessageBoxW(nullptr, msg, L"MapleStoryStart", MB_ICONERROR);
            return 1;
        }

        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }

    return 0;
}
