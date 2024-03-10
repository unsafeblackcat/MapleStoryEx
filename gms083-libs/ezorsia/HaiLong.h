#pragma once
#include "AddyLocations.h"

/*指定破功*/
void SetDamageCap(double dDamage);

/*指定移速上限*/
void SetMoveSpeedCap(int iSpeedValue);

/*配置服务器IP*/
void SetServerIP(const char* serverIP_Address);


/*角色框修复，包含升级*/
void CharacterBottomRepair();

/*键盘位置移动*/
void SetKeyboardPosition();

/*顶部滚动消息是否横向全屏*/
void TopMessageExtend();

/*BOSS血条是否显示在中心，原本会紧贴到右侧屏幕边缘*/
void BossBarRepair();

/*全图特效消息是否显示在屏幕中间*/
void CenterMessage();

/*获取道具，经验等的消息位置是否显示在紧贴右下角的菜单栏上方*/
void GainItemMessage();
void GainItemMessage(int msgAmnt, int msgAmntOffset, void* ptrMoreGainMsgs, void* ptrMoreGainMsgsFade1, void* ptrMoreGainMsgsFade);

/*是否将版本号移动到右上角*/
void VersionRightTop(void* ptrCodeCave, bool bUsed);

/*将现金商店移动到屏幕中心(原版WZ请不要使用)*/
void CashShopMove2Center(void* ptrCashShopFix1, void* ptrCashShopFix2, void* ptrCashShopFix3, void* ptrCashShopFix4, void* ptrCashShopFix5, void* ptrCashShopFix6,
                         void* ptrCashShopFix7, void* ptrCashShopFix8, void* ptrCashShopFixOnOff, void* ptrCashShopFixPrev, int imyWidth);
/*修复相机视角*/
void CameraRepair(void* ptrAlwaysViewRestoreFix);

/*移动登录界面的大区选择框*/
void WorldSelectDlgMove2Right(int a1y, void* ptrLoginBackCanvasFix, void* ptrLoginViewRecFix, void* ptrLoginDescriptorFix);

/*将组队邀请，交易，打招呼邀请的信息提示移动到聊天窗口的缩放按钮处*/
void PartyTradeChatMove();

/*额外扩展*/
void ExtraHere();

void LongKeyboard(unsigned int Array_aDefaultQKM_0, unsigned int Array_Expanded, unsigned int Array_ptShortKeyPos, unsigned int Array_ptShortKeyPos_Fixed_Tooltips,
	unsigned int  cooldown_Array, void* CompareValidateFuncKeyMappedInfo_cave, void* sub_9FA0CB_cave, void* sDefaultQuickslotKeyMap_cave, void* DefaultQuickslotKeyMap_cave,
	void* Restore_Array_Expanded);

void SuperTubi();

void SetFont();