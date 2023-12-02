#pragma once
class Client
{
public:
	static void UpdateGameStartup();
	static void EnableNewIGCipher();
	static void UpdateResolution();
	static void UpdateLogin();
	static const int m_nIGCipherHash = 0XC65053F2;
	static int m_nGameHeight;
	static int m_nGameWidth;
	static int MsgAmount;
	static double setDamageCap;
	static int speedMovementCap;
	static std::string ServerIP_AddressFromINI;
	static bool bIfMutiClient;
	static bool bIfLoadImgClient;
	static bool bIfMoveCashShopToCenter;
	static bool bVersionPosition;
	static int iVersionPositionH;
	static int iVersionPositionV;
};