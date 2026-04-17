# MapleStoryEx
Global MapleStory v083 plugin


# 构建Detouse
1. 更新子模块 Detours
2. cmd "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat" -arch=x86 -host_arch=x86
3. cd /d MapleStoryEx\Detours
set DETOURS_TARGET_PROCESSOR=X86
set DETOURS_CONFIG=Release
nmake /nologo clean
nmake /nologo
bin.X86Release, lib.X86Release, include