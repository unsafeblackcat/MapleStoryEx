#pragma once

#include <string>
#include <list>

/**
*
*   1. 插件需要放到 plugins 目录下
*   2. 需要实现三个接口pfun_init，pfun_show和pfun_reload_play_name
* 
*   pfun_init: 负责load到内存后调用，在dllmain 之后。
* 
*   pfun_show: 每个插件做了什么，需要向别人显示什么。 
*   CFunction::sendmsg 来显示告知玩家做了什么
* 
*   pfun_check: 每个插件的状态，是否开启之类的。
* 
*   命令输入: reg_commandinput_callback 回调
*   玩家通过聊天消息窗口发送消息，当消息以!开头则会当作插件命令处理，此时会把完整消息进入回调
*   
*   键盘输入: reg_keyboard_callback
*   当产生键盘按键时触发此回调，你可以通过判断按键类型来显示你自己的程序界面？
**/

/**
*   pfun_init:      加载插件并初始化
*   current_dir:    插件所在目录
*   play_role_name: 玩家所选择的人物名字
**/
typedef void (__cdecl *pfun_init)(const char* current_dir, const char* play_role_name);
/**
*   pfun_show: 显示插件名字
**/
typedef void (__cdecl* pfun_show)();
/**
*   pfun_check: 检查插件状态
**/
typedef void (__cdecl *pfun_check)();
/**
*   pfun_reload_play_name: 当玩家重新选择角色时会触发此回调
*   play_role_name: 新登陆玩家角色名字
**/
typedef void (__cdecl* pfun_reload_play_name)(const char* play_role_name);

class CPlugins
{
public:
    static CPlugins* m_this;
    static CPlugins* pins();

private:
    CPlugins(const std::wstring& current_dir);
    virtual ~CPlugins();

public:
    void load();

    void show();

    void replay_role();

private:
    void enum_plugins();

    void load_ex();

private:
    std::wstring m_plugins_dir;

    std::list<std::wstring> m_plugins;
};

