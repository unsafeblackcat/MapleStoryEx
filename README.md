# MapleStoryEx
Global MapleStory v083 plugin



# 构建Detouse
1. 更新子模块 Detours
2. cmd "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat" -arch=x86 -host_arch=x86
3. cd /d MapleStoryEx\Detours
4. set DETOURS_TARGET_PROCESSOR=X86
5. set DETOURS_CONFIG=Release
6. nmake /nologo clean
7. nmake /nologo
8. bin.X86Release, lib.X86Release, include