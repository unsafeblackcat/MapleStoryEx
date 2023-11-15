#include "stdafx.h"
#include "AddyLocations.h"
#include "codecaves.h"
#include "HaiLong.h"

int Client::m_nGameHeight = 720;
int Client::m_nGameWidth = 1280;
int Client::MsgAmount = 26;
double Client::setDamageCap = 199999.0;
int Client::speedMovementCap = 140;
std::string Client::ServerIP_AddressFromINI = "127.0.0.1";
bool Client::bIfMutiClient = false;
bool Client::bIfLoadImgClient = true;
bool Client::bIfMoveCashShopToCenter = true;

void Client::UpdateGameStartup() {

	//Memory::FillBytes(0x00C08459, 0x20, 0x00C0846E - 0x00C08459);//ɾ����������
	//Memory::WriteByte(0x00C08459, 0x22);//ɾ����������
	//Memory::WriteString(0x00C08459 + 1, "asInvoker");//��dll��ɾ����������//��������
	//Memory::WriteByte(0x00C08463, 0x22);//ɾ����������
	//Memory::WriteByte(0x0049C2CD + 1, 0x01);//ɾ����������//���ҵ�����Ȼ��������//��Ȼ���������Լ�����ԱȨ��
	//Memory::WriteByte(0x0049CFE8 + 1, 0x01);//������ҪӰ��WINAPI CreateProcess������Ҫһ��������//����Ϊ����Ŀͻ����޷�ֱ�ӱ༭��Щƫ��
	//Memory::WriteByte(0x0049D398 + 1, 0x01);//ɾ����������//��Ȼ��������

	const char* serverIP_Address = Client::ServerIP_AddressFromINI.c_str();

	SetServerIP(serverIP_Address);

	SetDamageCap(setDamageCap);

	SetMoveSpeedCap(speedMovementCap);
}

void Client::UpdateResolution() {
	nStatusBarY = Client::m_nGameHeight - 578;

	

	TopMessageExtend();

	BossBarRepair();

	//��Ч������Ļ�м�
	CenterMessage();

	//���½ǻ�ȡ����,��ȡ���ߵ������޸����������SetKeyboardPosition�������˴�ҲӦ����
	int msgAmntOffset, msgAmnt; 
	msgAmnt = MsgAmount; 
	msgAmntOffset = msgAmnt *14;//����ƶ��˼��̣����������Ҫ����
	MoreGainMsgsOffset = msgAmnt;	
	MoreGainMsgsFadeOffset = 15000;	
	MoreGainMsgsFade1Offset = 255 * 4 / 3;	
	SetKeyboardPosition();
	GainItemMessage(msgAmnt, msgAmntOffset, ccMoreGainMsgs, ccMoreGainMsgsFade, ccMoreGainMsgsFade1);//���ƶ����̶����ã���msgAmntOffsetдΪ200����


	CharacterBottomRepair();

	//�·�ע��������֤����������
	//Memory::WriteInt(0x008DE850 + 1, 580);//quickslotcheckX//�ײ���ť���໥����
	//Memory::WriteInt(0x008DE896 + 1, 647);//quickslotcheckX//�ײ���ť���໥����
	//Memory::WriteInt(0x008DE82B + 1, 507);///quickslotcheckY //�ײ���ť���໥����

	//Memory::WriteInt(0x008DA11C + 1, m_nGameHeight - 19);//??�����Ǹ���״̬��UI���
	//Memory::WriteInt(0x008DA3D4 + 1, m_nGameHeight - 56); //exphpmp%��ǩ
	//Memory::WriteInt(0x008DA463 + 1, m_nGameHeight - 51); //stat-bar���������
	//Memory::WriteInt(0x008DA4F2 + 1, m_nGameHeight - 51);//stat-bar���������
	//Memory::WriteInt(0x008DA61B + 1, m_nGameHeight - 56);//??�����Ǹ���״̬��UI���

	//Memory::WriteInt(0x008DA90F + 1, m_nGameHeight - 51);//ͳ�����ֵ�����
	//Memory::WriteInt(0x008DA9C6 + 1, m_nGameHeight - 51);
	//Memory::WriteInt(0x008DAC3F + 1, m_nGameHeight - 51);
	//Memory::WriteInt(0x008DACF1 + 1, m_nGameHeight - 51);
	//Memory::WriteInt(0x008DAF64 + 1, m_nGameHeight - 51);

	//Memory::WriteInt(0x008DFA6F + 1, m_nGameHeight - 81);//�����ѡ��, dragging box size, minus plus sign, typing interac
	//Memory::WriteInt(0x008DFB01 + 1, m_nGameHeight - 81);
	//Memory::WriteInt(0x008DFBA5 + 1, m_nGameHeight - 80);
	//Memory::WriteInt(0x008DFC10 + 1, m_nGameHeight - 85);

	//Memory::WriteInt(0x008D4AFB + 1, m_nGameHeight - 91); //��Ϊ���������Сץȡ/������С�������룩����
	//Memory::WriteInt(0x008D4C1F + 1, m_nGameHeight - 90);//??�����Ǹ���״̬��UI���
	//Memory::WriteInt(0x008D4CDD + 1, m_nGameHeight - 20);//??�����Ǹ���״̬��UI���
	//Memory::WriteInt(0x008D4BBC + 6, m_nGameHeight - 114);//??�����Ǹ���״̬��UI���
	//Memory::WriteInt(0x008D4C47 + 1, m_nGameHeight - 87);//��С�������
	//Memory::WriteInt(0x008D628B + 1, m_nGameHeight - 91); //�����ı�����ı���������
	//Memory::WriteInt(0x008D6300 + 1, m_nGameHeight - 90); //�����������ı�����Ĺ�����������
	//Memory::WriteInt(0x008D4B6D + 1, m_nGameHeight - 90);//���������
	//Memory::WriteInt(0x008D276A + 1, m_nGameHeight - 19);//??�����Ǹ���״̬��UI���

	//Memory::WriteInt(0x008D7778 + 3, m_nGameHeight - 42);//???likely various status bar UI components
	//Memory::WriteInt(0x008D7785 + 3, m_nGameHeight - 26);//??likely various status bar UI components
	//Memory::WriteInt(0x008D783A + 3, m_nGameHeight - 41);//??likely various status bar UI components
	//Memory::WriteInt(0x008D7847 + 3, m_nGameHeight - 26);//??likely various status bar UI components

	//Memory::WriteInt(0x008D2FAE + 1, m_nGameHeight - 57); //�ײ�4����ť
	//Memory::WriteInt(0x008D3056 + 1, m_nGameHeight - 57);
	//Memory::WriteInt(0x008D311F + 1, m_nGameHeight - 57);
	//Memory::WriteInt(0x008D31E7 + 1, m_nGameHeight - 57);//�ײ�4����ť



    //�ֽ��̵��ƶ��ӽ�
	if (bIfMoveCashShopToCenter)
	{
		myHeight = (720 - 600) / 2;//cash shop fix for frame area	//recalc offsets
		myWidth = (1280 - 800) / 2;//cash shop fix for frame area		//recalc offsets
		nHeightOfsetted1 = 316; nWidthOfsetted1 = 256; nTopOfsetted1 = 0 + myHeight; nLeftOfsetted1 = 0 + myWidth; //parameters for fix1
		nHeightOfsetted2 = 104; nWidthOfsetted2 = 256; nTopOfsetted2 = 318 + myHeight; nLeftOfsetted2 = -1 + myWidth; //parameters for fix2
		nHeightOfsetted3 = 163; nWidthOfsetted3 = 246; nTopOfsetted3 = 426 + myHeight; nLeftOfsetted3 = 0 + myWidth; //parameters for fix3
		nHeightOfsetted4 = 78; nWidthOfsetted4 = 508; nTopOfsetted4 = 17 + myHeight; nLeftOfsetted4 = 272 + myWidth; //parameters for fix4
		nHeightOfsetted5 = 430; nWidthOfsetted5 = 412; nTopOfsetted5 = 95 + myHeight; nLeftOfsetted5 = 275 + myWidth; //parameters for fix5
		nHeightOfsetted6 = 358; nWidthOfsetted6 = 90; nTopOfsetted6 = 157 + myHeight; //parameters for fix6
		nHeightOfsetted7 = 56; nWidthOfsetted7 = 545; nTopOfsetted7 = 530 + myHeight; nLeftOfsetted7 = 254 + myWidth; //parameters for fix7
		nHeightOfsetted8 = 22; nWidthOfsetted8 = 89; nTopOfsetted8 = 97 + myHeight; nLeftOfsetted8 = 690 + myWidth; //parameters for fix8
		nHeightOfsettedPrev = 165 + myHeight; nWidthOfsettedPrev = 212 + myWidth; nTopOfsettedPrev = 40 + myHeight; nLeftOfsettedPrev = 24 + myWidth; //parameters for fix cash preview
		CashShopMove2Center(CashShopFix1, CashShopFix2, CashShopFix3, CashShopFix4, CashShopFix5, CashShopFix6, CashShopFix7, CashShopFix8, CashShopFixOnOff, CashShopFixPrev, myWidth);

	}


	//��ͼ�Ĳ���
	myAlwaysViewRestoreFixOffset = myHeight; 
	CameraRepair(AlwaysViewRestoreFix);


	//20231110
	//��λ��¼����汾�ŵ�λ��
	nTopOfsettedVerFix = 10 + myHeight;
	nLeftOfsettedVerFix = 645 + myWidth; 
	VersionRightTop(VersionNumberFix, true);
	
	
	if (0) {
		nHeightOfsettedLoginBackCanvasFix = 352 + myHeight;
		nWidthOfsettedLoginBackCanvasFix = 125 + myWidth;//para for world select buttonsViewRec
		nTopOfsettedLoginBackCanvasFix = 125 + myHeight;
		nLeftOfsettedLoginBackCanvasFix = 0 + myWidth;
		nHeightOfsettedLoginViewRecFix = 167 + myHeight; 
		nWidthOfsettedLoginViewRecFix = 540 + myWidth;//para for ViewRec fix
		nTopOfsettedLoginViewRecFix = 51 + myHeight; 
		nLeftOfsettedLoginViewRecFix = 136 + myWidth;
		a1x = 0 + myWidth; 
		a2x = -149 + myWidth; 
		a2y = 0 + myHeight; 
		a3 = 25; a1y = -250; //a4 = 0;	//��¼����������
		WorldSelectDlgMove2Right(a1y, ccLoginBackCanvasFix, ccLoginViewRecFix, ccLoginDescriptorFix);
	}
}

void Client::EnableNewIGCipher() {//??not called //no idea what cipher is
	const int nCipherHash = m_nIGCipherHash;
	Memory::WriteInt(dwIGCipherHash + 3, nCipherHash);
	Memory::WriteInt(dwIGCipherVirtual1 + 3, nCipherHash);
	Memory::WriteInt(dwIGCipherVirtual2 + 3, nCipherHash);
	Memory::WriteInt(dwIGCipherDecrypt + 3, nCipherHash);
	Memory::WriteInt(dwIGCipherDecryptStr + 3, nCipherHash);
}

void Client::UpdateLogin() {	//un-used //may still contain some useful addresses for custom login
	Memory::CodeCave(PositionLoginDlg, dwLoginCreateDlg, 14);
	Memory::CodeCave(PositionLoginUsername, dwLoginUsername, 11);
	Memory::CodeCave(PositionLoginPassword, dwLoginPassword, 8);
	Memory::WriteInt(dwLoginInputBackgroundColor + 3, 0xFFF8FAFF); // ARGB value
	Memory::WriteByte(dwLoginInputFontColor + 3, 1); // bool: true=black, false=white
	Memory::WriteInt(dwLoginLoginBtn + 1, -127); // x-pos
	Memory::WriteInt(dwLoginFindPasswordBtn + 1, -127); // x-pos
	Memory::WriteInt(dwLoginQuitBtn + 1, -127); // x-pos
	Memory::WriteInt(dwLoginFindIDBtn + 1, -127); // x-pos
	Memory::WriteByte(dwLoginFindIDBtn + 1, -127); // x-pos
	Memory::WriteByte(dwLoginWebHomeBtn + 1, -127); // x-pos
	Memory::WriteByte(dwLoginWebRegisterBtn + 1, -127); // x-pos
}