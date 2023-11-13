# 目录介绍
~~~cpp
D:.
├───community 	    外部三方C++开源库
└───config		    VS配置文件
├───MapleStory      新的启动器
└───MapleStoryEx    用于后续注入和修改功能的注入插件
~~~

# VS开发环境介绍
1. 使用VS2022初始提交，避免混乱，编译工具请统一安装 VS2017 - XP(141_XP)编译，调试，和分发。
2. 为了避免开发环境混乱请关闭下面选项


# MapleStory
新的启动器程序，功能为拉起原始MapleStory.exe启动游戏后将MapleStoryEx.dll注入到MapleStory游戏本体。

需要将083cn冒险岛游戏本地中的MapleStory.exe重命名为MapleStory_.exe后再将编译后的MapleStory.exe和MapleStoryEx.dll放入083cn文件夹中。

# MapleStoryEx
注入插件，由上面的工程把当前插件注入到MapleStory.exe中。插件目的，调试，框架，支持插件，

> 简单的插件管理器 √