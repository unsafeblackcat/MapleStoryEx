#pragma once
#include "AddyLocations.h"

/*ָ���ƹ�*/
void SetDamageCap(double dDamage);

/*ָ����������*/
void SetMoveSpeedCap(int iSpeedValue);

/*���÷�����IP*/
void SetServerIP(const char* serverIP_Address);


/*��ɫ���޸�����������*/
void CharacterBottomRepair();

/*����λ���ƶ�*/
void SetKeyboardPosition();

/*����������Ϣ�Ƿ����ȫ��*/
void TopMessageExtend();

/*BOSSѪ���Ƿ���ʾ�����ģ�ԭ����������Ҳ���Ļ��Ե*/
void BossBarRepair();

/*ȫͼ��Ч��Ϣ�Ƿ���ʾ����Ļ�м�*/
void CenterMessage();

/*��ȡ���ߣ�����ȵ���Ϣλ���Ƿ���ʾ�ڽ������½ǵĲ˵����Ϸ�*/
void GainItemMessage();
void GainItemMessage(int msgAmnt, int msgAmntOffset, void* ptrMoreGainMsgs, void* ptrMoreGainMsgsFade1, void* ptrMoreGainMsgsFade);

/*�Ƿ񽫰汾���ƶ������Ͻ�*/
void VersionRightTop(void* ptrCodeCave, bool bUsed);

/*���ֽ��̵��ƶ�����Ļ����(ԭ��WZ�벻Ҫʹ��)*/
void CashShopMove2Center(void* ptrCashShopFix1, void* ptrCashShopFix2, void* ptrCashShopFix3, void* ptrCashShopFix4, void* ptrCashShopFix5, void* ptrCashShopFix6,
                         void* ptrCashShopFix7, void* ptrCashShopFix8, void* ptrCashShopFixOnOff, void* ptrCashShopFixPrev, int imyWidth);
/*�޸�����ӽ�*/
void CameraRepair(void* ptrAlwaysViewRestoreFix);

/*�ƶ���¼����Ĵ���ѡ���*/
void WorldSelectDlgMove2Right(int a1y, void* ptrLoginBackCanvasFix, void* ptrLoginViewRecFix, void* ptrLoginDescriptorFix);

/*��������룬���ף����к��������Ϣ��ʾ�ƶ������촰�ڵ����Ű�ť��*/
void PartyTradeChatMove();

/*������չ*/
void ExtraHere();

void LongKeyboard(unsigned int Array_aDefaultQKM_0, unsigned int Array_Expanded, unsigned int Array_ptShortKeyPos, unsigned int Array_ptShortKeyPos_Fixed_Tooltips,
	unsigned int  cooldown_Array, void* CompareValidateFuncKeyMappedInfo_cave, void* sub_9FA0CB_cave, void* sDefaultQuickslotKeyMap_cave, void* DefaultQuickslotKeyMap_cave,
	void* Restore_Array_Expanded);

void SuperTubi();

void SetFont();