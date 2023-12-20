#include "stdafx.h"
#include "HaiLong.h"


void SetDamageCap(double dDamage)
{
	//破功
	Memory::WriteDouble(0x00AFE8A0, dDamage);	//ty rain
	int setDamageCapInt = static_cast<int>(dDamage < 0 ? dDamage - 0.5 : dDamage + 0.5);
	Memory::WriteInt(0x008C3304 + 1, setDamageCapInt); //ty rain
}
void SetMoveSpeedCap(int iSpeedValue)
{
	//移速
	Memory::WriteInt(0x00780743 + 3, iSpeedValue);
	Memory::WriteInt(0x008C4286 + 1, iSpeedValue);
	Memory::WriteInt(0x0094D91E + 1, iSpeedValue);
}
void SetServerIP(const char* serverIP_Address)
{
	Memory::FillBytes(0x00AFE084, 0x00, 0x006FE0B2 - 0x006FE084);//删除客户端中现有的服务器IP地址
	Memory::WriteString(0x00AFE084, serverIP_Address);//写入用户设置的IP地址
	Memory::WriteString(0x00AFE084 + 16, serverIP_Address);//写入用户设置的IP地址
	Memory::WriteString(0x00AFE084 + 32, serverIP_Address);//写入用户设置的IP地址
}

void CharacterBottomRepair()
{
	int m_nGameWidth = 1280;
	int m_nGameHeight = 720;
	Memory::WriteInt(0x008D3F73 + 1, m_nGameHeight - 93);//bottom frame, white area
	Memory::WriteInt(0x008D3FE5 + 1, m_nGameHeight - 93);//bottom frame, grey area
	Memory::WriteInt(0x008D8353 + 1, m_nGameHeight - 46); //bottom frame, character level
	Memory::WriteInt(0x008D83D1 + 1, m_nGameHeight - 55); //role
	Memory::WriteInt(0x008D8470 + 1, m_nGameHeight - 40); //name of character
}
void SetKeyboardPosition()
{
	//键盘
	Memory::WriteInt(dwQuickSlotInitVPos + 1, 722 );//721
	Memory::WriteInt(dwQuickSlotInitHPos + 1, 890); //798
	Memory::WriteInt(dwQuickSlotVPos + 2, 722 );//721
	Memory::WriteInt(dwQuickSlotHPos + 1, 890);

	//屏蔽原来的窗口
	Memory::WriteInt(dwQuickSlotCWndVPos + 2, -120);//(600 - 720) / 2 - 427
	Memory::WriteInt(dwQuickSlotCWndHPos + 2, -120);//-798
}

void TopMessageExtend()
{
	int m_nGameWidth = 1280;
	int m_nGameHeight = 720;
	Memory::WriteInt(dwByteAvatarMegaHPos + 1, m_nGameWidth); //push 800 ; CAvatarMegaphone::ByeAvatarMegaphone ; IWzVector2D::RelMove
	Memory::WriteInt(dwAvatarMegaWidth + 1, m_nGameWidth); //push 800 ; CAvatarMegaphone ; CreateWnd
	Memory::WriteInt(0x0043717B + 1, m_nGameHeight);//mov edi,600
	Memory::WriteInt(0x00437181 + 1, m_nGameWidth);	//mov esi,800 ; CreateWnd
	Memory::WriteInt(0x0053808B + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x00538091 + 1, m_nGameWidth);	//push 800 ; RelMove?
	Memory::WriteInt(0x004CC160 + 1, m_nGameWidth);	//mov [ebp-16],800 ; CreateWnd
	Memory::WriteInt(0x004CC2C5 + 2, m_nGameHeight);//cmp ecx,600
	Memory::WriteInt(0x004CC2B0 + 1, m_nGameWidth);	//mov eax,800 ; CreateWnd
	Memory::WriteInt(0x004D59B2 + 1, m_nGameHeight);//mov eax,800
	Memory::WriteInt(0x004D599D + 1, m_nGameWidth);	//mov eax,800 ; CreateWnd
	Memory::WriteInt(0x0085F36C + 2, m_nGameWidth);	//cmp edx,800
	Memory::WriteInt(0x0085F374 + 1, m_nGameWidth - 80);	//mov ecx,720 ; CreateDlg
	Memory::WriteInt(0x008EBC58 + 1, m_nGameHeight);//mov eax,600
	Memory::WriteInt(0x008EBC3C + 1, m_nGameWidth);	//mov eax,800 ; RelMove?
	Memory::WriteInt(0x009966B5 + 1, m_nGameHeight);//mov ecx,600
	Memory::WriteInt(0x009966CA + 2, m_nGameWidth);	//cmp edi,800
	Memory::WriteInt(0x009966D2 + 1, m_nGameWidth - 100);	//mov edx,700 ; CreateDlg
	Memory::WriteInt(0x009A3E7F + 1, m_nGameHeight);//mov edx,600
	Memory::WriteInt(0x009A3E72 + 1, m_nGameWidth);	//mov edx,800 ; CreateDlg
	//Memory::WriteInt(0x0045B898 + 1, m_nGameHeight - 25);	//push 575
	Memory::WriteInt(0x0045B898 + 1, m_nGameWidth - 225);	//push 575 ##ED  //smega x axis fade
	//Memory::WriteInt(0x0045B97E + 1, m_nGameWidth);	//push 800 ; RelMove? ##REDUN
	//Memory::WriteInt(0x004D9BD1 + 1, m_nGameWidth);	//push 800	; StringPool#1443 (BtMouseCilck)		//click ???related?? for tabs and numbers in cash shop
	//Memory::WriteInt(0x004D9C37 + 1, m_nGameWidth);	//push 800	; StringPool#1443 (BtMouseCilck)		//click ???related?? for tabs and numbers in cash shop
	//Memory::WriteInt(0x004D9C84 + 1, m_nGameWidth);	//push 800 ; StringPool#1443 (BtMouseCilck)		//click ???related?? for tabs and numbers in cash shop
	Memory::WriteInt(0x005386F0 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x005386F5 + 1, m_nGameWidth);	//push 800 ; CField::DrawFearEffect
	Memory::WriteInt(0x0055B808 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x0055B80D + 1, m_nGameWidth);	//mov edi,800
	Memory::WriteInt(0x0055B884 + 1, m_nGameWidth);	//push 600 ; RelMove?
	Memory::WriteInt(0x007E15BE + 1, m_nGameWidth);	//push 800 ; CreateWnd
	Memory::WriteInt(0x007E16B9 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x007E16BE + 1, m_nGameWidth);	//push 800 ; CWnd::GetCanvas //!!length of server message at top
	Memory::WriteInt(0x008AA266 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x008AA26B + 1, m_nGameWidth);	//push 800 ; CreateWnd
	Memory::WriteInt(0x009F6E99 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x009F6EA0 + 1, m_nGameWidth);	//push 800 ; StringPool#1162 (MapleStoryClass)

	Memory::WriteInt(0x007CF48F + 1, m_nGameHeight);//mov eax,600 ; 
	Memory::WriteInt(0x007CF49D + 1, m_nGameWidth);	//mov eax,800 ; IWzVector2D::RelMove
	Memory::WriteInt(0x008A12F4 + 1, m_nGameHeight);//mov eax,600 ; 
	Memory::WriteInt(0x008A1302 + 1, m_nGameWidth);	//mov eax,800 ; IWzVector2D::RelMove
	Memory::WriteInt(0x007F257E + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x007F258F + 1, m_nGameWidth);	//push 800 ; CWnd::CreateWnd
	Memory::WriteInt(0x0046B85C + 1, m_nGameHeight);//mov eax,600
	Memory::WriteInt(0x0046B86A + 1, m_nGameWidth);	//mov eax,800 ; IWzVector2D::RelMove
	Memory::WriteInt(0x009994D8 + 1, m_nGameHeight);//mov ecx,600
	Memory::WriteInt(0x009994ED + 2, m_nGameWidth);	//cmp edi,800
	Memory::WriteInt(0x009994F5 + 1, m_nGameWidth - 100);	//mov edx,700 ; CreateDlg

	Memory::WriteInt(0x0062FC4A + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x0062FC4F + 1, m_nGameWidth);	//push 800 ; IWzGr2DLayer::Getcanvas
	Memory::WriteInt(0x0062FE63 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x0062FE68 + 1, m_nGameWidth);	//push 800 ; IWzGr2DLayer::Getcanvas
	Memory::WriteInt(0x0062F9C6 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x0062F9CB + 1, m_nGameWidth);	//push 800; (UI/Logo/Wizet)
	Memory::WriteInt(0x0062F104 + 1, m_nGameHeight);//mov eax,600
	Memory::WriteInt(0x0062F109 + 1, m_nGameWidth);	//mov eax,800 ; Rectangle
	Memory::WriteInt(0x006406D5 + 1, m_nGameHeight);//mov ecx,600
	Memory::WriteInt(0x006406C3 + 1, m_nGameWidth);	//mov ecx,800
	Memory::WriteInt(0x0064050A + 1, m_nGameHeight);//mov ecx,600
	Memory::WriteInt(0x006404F8 + 1, m_nGameWidth);	//mov ecx,800
	Memory::WriteInt(0x00640618 + 1, m_nGameHeight);//mov ecx,600
	Memory::WriteInt(0x00640690 + 1, m_nGameHeight);//mov ecx,600
	Memory::WriteInt(0x0064061D + 1, m_nGameHeight);//mov ecx,600
	Memory::WriteInt(0x0064064B + 1, m_nGameHeight);//mov ecx,600
	Memory::WriteInt(0x00640606 + 1, m_nGameWidth);	//mov ecx,800
	Memory::WriteInt(0x0064067E + 1, m_nGameWidth);	//mov ecx,800
	Memory::WriteInt(0x00640639 + 1, m_nGameWidth);	//mov ecx,800
	Memory::WriteInt(0x0064043E + 1, (unsigned int)floor(m_nGameWidth / 2));	//mov edi,400
	Memory::WriteInt(0x00640443 + 1, (unsigned int)floor(m_nGameHeight / 2));	//mov esi,300
	Memory::WriteInt(0x00640626 + 1, (unsigned int)floor(m_nGameWidth / 2));	//add eax,400 ; bunch of modulus stuff
}


void BossBarRepair()
{
	int m_nGameWidth = 1280;
	int m_nGameHeight = 720;
	Memory::WriteByte(0x00533B03, 0xb8);	//boss bar extend to window
	Memory::WriteInt(0x00533B03 + 1, m_nGameWidth - 15);	//boss bar	extend to window
	Memory::WriteByte(0x00534370, 0xb9);	//boss bar	extend to window
	Memory::WriteInt(0x00534370 + 1, m_nGameWidth - 22);	//boss bar	extend to window
}

void CenterMessage()
{
	int m_nGameWidth = 1280;
	int m_nGameHeight = 720;
	Memory::WriteInt(0x00641038 + 2, m_nGameHeight);//??possibly related to player display
	Memory::WriteInt(0x0064103F + 2, m_nGameWidth);//??possibly related to player display
	Memory::WriteInt(0x00641048 + 1, (unsigned int)floor(-m_nGameHeight / 2));	//mov esi,-300
	Memory::WriteInt(0x00641050 + 1, (unsigned int)floor(-m_nGameWidth / 2));		//mov esi,-400 ;
	Memory::WriteInt(0x00641A19 + 3, m_nGameHeight);//mov [ebp+28],600
	Memory::WriteInt(0x00641A12 + 3, m_nGameWidth);	//mov [ebp+32],800 ; idk
	Memory::WriteInt(0x00641B38 + 3, m_nGameHeight);//mov [ebp-32],600
	Memory::WriteInt(0x00641B2E + 3, m_nGameWidth);	//mov [ebp-36],800 ; CAnimationDisplayer::SetCenterOrigin

	Memory::WriteInt(0x006CD842 + 1, (unsigned int)floor(m_nGameWidth / 2));	//push 400 ; RelMove?

	Memory::WriteInt(0x0059A0A2 + 6, (unsigned int)floor(m_nGameHeight / 2));	//mov [ebx+2364],300
	Memory::WriteInt(0x0059A09C + 2, (unsigned int)floor(m_nGameWidth / 2));	//mov [esi],400	; CInputSystem::LoadCursorState
	Memory::WriteInt(0x0080546C + 1, m_nGameHeight);//mov edi,600
	Memory::WriteInt(0x00805459 + 1, m_nGameWidth);	//mov edx,800 ; CUIEventAlarm::CreateEventAlarm
	Memory::WriteInt(0x008CFD4B + 1, m_nGameHeight - 22);	//push 578
	Memory::WriteInt(0x008CFD50 + 1, m_nGameWidth);	//push 800
	Memory::WriteInt(0x0053836D + 1, (unsigned int)floor(-m_nGameHeight / 2));//push -300
	Memory::WriteInt(0x00538373 + 1, (unsigned int)floor(-m_nGameWidth / 2));	//push -400	; RelMove?
	Memory::WriteInt(0x0055BB2F + 1, (unsigned int)floor(-m_nGameHeight / 2));//push -300
	Memory::WriteInt(0x0055BB35 + 1, (unsigned int)floor(-m_nGameWidth / 2));	//push -400 ; RelMove?

	Memory::WriteInt(0x005A8B46 + 1, m_nGameHeight);//mov eax,600
	Memory::WriteInt(0x005A8B56 + 1, m_nGameWidth);	//mov eax,800 ; RelMove?
	Memory::WriteInt(0x005A9B42 + 1, m_nGameHeight);//mov eax,600
	Memory::WriteInt(0x005A9B52 + 1, m_nGameWidth);	//mov eax,800 ; RelMove?
	Memory::WriteInt(0x005AADAA + 1, m_nGameHeight);//mov eax,600
	Memory::WriteInt(0x005AADBA + 1, m_nGameWidth);	//mov eax,800 ; RelMove?
	Memory::WriteInt(0x005ABC65 + 1, m_nGameHeight);//mov eax,600
	Memory::WriteInt(0x005ABC75 + 1, m_nGameWidth);	//mov eax,800 ; RelMove?
	Memory::WriteInt(0x005ACB29 + 1, m_nGameHeight);//mov eax,600
	Memory::WriteInt(0x005ACB39 + 1, m_nGameWidth);	//mov eax,800 ; RelMove?
	Memory::WriteInt(0x005C187E + 1, m_nGameHeight);//mov eax,600
	Memory::WriteInt(0x005C188E + 1, m_nGameWidth);	//mov eax,800 ; RelMove?
	Memory::WriteInt(0x005C2D62 + 1, m_nGameHeight);//mov eax,600
	Memory::WriteInt(0x005C2D72 + 1, m_nGameWidth);	//mov eax,800 ; RelMove?
	Memory::WriteInt(0x005E3FA0 + 1, m_nGameHeight);//push 600

	Memory::WriteInt(0x005F64DE + 1, (unsigned int)floor(-m_nGameHeight / 2));	//push -300 ;
	Memory::WriteInt(0x005F6627 + 1, (unsigned int)floor(-m_nGameHeight / 2));	//push -300 ;
	Memory::WriteInt(0x005F464D + 1, (unsigned int)floor(m_nGameWidth / 2));//??related to login game frame

	Memory::WriteInt(0x0060411C + 1, m_nGameHeight);//push 600
	//Memory::WriteInt(0x00604126 + 1, floor(-m_nGameWidth / 2));	//push -300 //moves characters side to side on char select //unnecessary atm
	Memory::WriteInt(0x0060F79B + 1, (m_nGameHeight / 2) - 201);//??possibly related to login utildlg
	Memory::WriteInt(0x0060F7A4 + 1, (m_nGameHeight / 2) - 181);//??possibly related to login utildlg
	Memory::WriteInt(0x0060F7AC + 1, (m_nGameWidth / 2) - 201);//??possibly related to login utildlg
	Memory::WriteInt(0x0060F7B5 + 1, (m_nGameWidth / 2) - 181);//??possibly related to login utildlg
	Memory::WriteInt(0x00613093 + 1, (m_nGameHeight / 2) - 200);//??likely related to login pop-up msg
	Memory::WriteInt(0x00613099 + 1, (m_nGameWidth / 2) - 45);//??likely related to login pop-up msg
	Memory::WriteInt(0x0061DAFF + 1, (m_nGameHeight / 2) - 150);//??likely related to login pop-up msg
	Memory::WriteInt(0x0061DB08 + 1, (m_nGameHeight / 2) - 130);//??likely related to login pop-up msg
	Memory::WriteInt(0x0061DB10 + 1, (m_nGameWidth / 2) - 201);//??likely related to login pop-up msg
	Memory::WriteInt(0x0061DB19 + 1, (m_nGameWidth / 2) - 181);//??likely related to login pop-up msg

	Memory::WriteInt(0x004372B1 + 1, (unsigned int)floor(-m_nGameHeight / 2));//push -300
	Memory::WriteInt(0x004372B6 + 1, (unsigned int)floor(-m_nGameWidth / 2));	//push -400 ; RelMove?
	Memory::WriteInt(0x006CE3AB + 1, m_nGameWidth);	//push 800
	Memory::WriteInt(0x007E1CB7 + 1, m_nGameWidth);	//push 800
	Memory::WriteInt(0x008D82F5 + 1, m_nGameHeight - 22);	//push 578
	Memory::WriteInt(0x008D82FA + 1, m_nGameWidth);	//push 800 ; CreateWnd?
	Memory::WriteInt(0x00935870 + 1, (unsigned int)floor(m_nGameHeight / 2));	//push 300
	Memory::WriteInt(0x0093586B + 1, m_nGameWidth);	// push 800 ; RelMove? (Skills)
	Memory::WriteInt(0x009DFD5C + 1, m_nGameWidth);	//mov ecx,800
	Memory::WriteInt(0x009DFED2 + 1, m_nGameHeight);//mov ecx,600	; IWzVector2D::RelMove
	Memory::WriteInt(0x009F6ADD + 1, (unsigned int)floor(m_nGameHeight / 2)); //push 300 ; MapleStoryClass
	Memory::WriteInt(0x006D50D8 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x0074BAA9 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x0074B951 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x0074B4A2 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x0074B3B7 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x006421B3 + 1, m_nGameHeight);//push 600 ; CSoundMan::PlayBGM

	Memory::WriteInt(0x0059EB49 + 1, m_nGameHeight);//push 600 ; CSoundMan::PlayBGM
	Memory::WriteInt(0x008D247B + 1, m_nGameHeight - 33);	//push 567 ; IWzVector2D::RelMove
	Memory::WriteInt(0x008DEB93 + 1, m_nGameHeight - 20);	//push 580
	Memory::WriteInt(0x008DEE2F + 1, m_nGameHeight - 20);	//push 580
	Memory::WriteInt(0x008D2765 + 1, m_nGameHeight - 19);	//push 581
	Memory::WriteInt(0x008D29B4 + 1, m_nGameHeight - 19);	//push 581
	Memory::WriteInt(0x008D8BFE + 1, m_nGameHeight - 19);	//push 581
	Memory::WriteInt(0x008D937E + 1, m_nGameHeight - 19);	//push 581 //008D9373  move mana bar outline? //ty rynyan
	Memory::WriteInt(0x008D9AC9 + 1, m_nGameHeight - 19);	//push  
	Memory::WriteInt(0x008D1D50 + 1, m_nGameHeight - 22);	//push 578
	Memory::WriteInt(0x008D1D55 + 1, m_nGameWidth);	//push 800
	Memory::WriteInt(0x008D1FF4 + 1, m_nGameHeight - 22);	//push 578
	Memory::WriteInt(0x008D1FF9 + 1, m_nGameWidth);	//push 800 ; CUIStatusBar
	Memory::WriteInt(0x0062F5DF + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x0062F5E4 + 1, m_nGameWidth);	//push 800 ; (UI/Logo/Nexon)
	Memory::WriteInt(0x004EDB89 + 1, m_nGameWidth);	//mov ecx,800
	Memory::WriteInt(0x004EDB78 + 1, m_nGameHeight);//mov ecx,600 ; CreateWnd
	Memory::WriteInt(0x004EDAD8 + 1, m_nGameWidth);	//mov ecx,800
	Memory::WriteInt(0x009F7079, m_nGameHeight);	// dd 600
	Memory::WriteInt(0x009F707E, m_nGameWidth);	// dd 800
	Memory::WriteInt(0x00BE2738, (unsigned int)floor(m_nGameWidth / 2));	// dd 400
	Memory::WriteInt(0x00BE2DF4, (unsigned int)floor(m_nGameHeight / 2));	// dd 300
	Memory::WriteInt(0x00BE2DF0, (unsigned int)floor(m_nGameWidth / 2));	// dd 400
	Memory::WriteInt(0x00640656 + 2, (unsigned int)floor(-m_nGameWidth / 2));		//add edi,-400 ;


	Memory::WriteInt(0x006CE4C6 + 1, (unsigned int)floor(-m_nGameWidth / 2));		//push -400 ;
	Memory::WriteInt(0x009E2E85 + 1, (unsigned int)floor(-m_nGameHeight / 2));	//push -300		overall screen visible UI scaling
	Memory::WriteInt(0x009E2E8B + 1, (unsigned int)floor(-m_nGameWidth / 2));		//push -400 ;	overall screen visible UI scaling

	Memory::WriteInt(0x0093519A + 1, (unsigned int)floor(-m_nGameHeight / 2));	//push -300 ;
	Memory::WriteInt(0x00954433 + 1, (unsigned int)floor(-m_nGameHeight / 2));	//push -300 ;
	Memory::WriteInt(0x00981555 + 1, (unsigned int)floor(-m_nGameHeight / 2));	//push -300 ;
	Memory::WriteInt(0x00981F7A + 2, (unsigned int)floor(-m_nGameHeight / 2));	//push -300 ;
	Memory::WriteInt(0x00A448B0 + 2, (unsigned int)floor(-m_nGameHeight / 2));	//push -300 ; CWvsPhysicalSpace2D::Load]

	Memory::WriteInt(0x0066BACE + 2, (unsigned int)floor(-m_nGameWidth / 2));		//and ecx,-400
	Memory::WriteInt(0x009B76BD + 3, (unsigned int)floor(-m_nGameHeight / 2));	//push -300
	Memory::WriteInt(0x009B76CB + 3, (unsigned int)floor(m_nGameHeight / 2));		//push 300

	Memory::WriteInt(0x009F7078 + 1, m_nGameHeight);//??related to application dimensions	//(ragezone release merge)//thanks mr mr of ragezone for these addresses
	Memory::WriteInt(0x009F707D + 1, m_nGameWidth);//??related to application dimensions

	Memory::WriteInt(0x0058C8A6 + 1, m_nGameWidth);//??

	Memory::WriteInt(0x004EDABF + 1, m_nGameHeight);//??

	Memory::WriteInt(0x00991854 + 1, m_nGameHeight);//??unknown cwnd function
	Memory::WriteInt(0x0099185F + 1, (m_nGameWidth / 2) - 134);//??unknown cwnd function
	Memory::WriteInt(0x00991867 + 1, (m_nGameWidth / 2) - 133);//??unknown cwnd function
	Memory::WriteInt(0x00992BA7 + 1, (unsigned int)floor(m_nGameWidth / 2));//??unknown cwnd function, possibly related to cutildlg
	Memory::WriteInt(0x00992BAC + 1, (unsigned int)floor(m_nGameHeight / 2));//??unknown cwnd function, possibly related to cutildlg

	Memory::WriteInt(0x007E1E07 + 2, m_nGameWidth);//??related to displaying server message at top of screen
	Memory::WriteInt(0x007E19CA + 2, m_nGameWidth);//??related to displaying server message at top of screen

	Memory::WriteInt(0x005362B2 + 1, (m_nGameWidth / 2) - 129);//??related to boss bar
	Memory::WriteInt(0x005364AA + 2, (m_nGameWidth / 2) - 128);//??related to boss bar

	Memory::WriteInt(0x00592A08 + 1, (m_nGameWidth / 2) - 125);//??likely related to mouse pos

	Memory::WriteInt(0x00621226 + 1, (m_nGameWidth / 2) - 216);//??possibly related to logo
	Memory::WriteByte(0x0062121E + 1, 0x01);//??possibly related to logo

	Memory::WriteInt(0x008C069F + 1, (m_nGameHeight / 2) - 14);//??related to status bar
	Memory::WriteInt(0x008C06A4 + 1, (m_nGameWidth / 2) - 158);//???related to status bar

	Memory::WriteInt(0x00A24D0B + 1, (m_nGameWidth / 2) - 129);//??


}

void GainItemMessage()
{
	int m_nGameWidth = 1280;
	int m_nGameHeight = 720;
	Memory::WriteInt(0x00BE273C, 128);//??
	Memory::WriteByte(0x00A5FC2B, 0x05);//??
	Memory::WriteByte(0x0089B636 + 2, 0x01); //与经验增益/物品拾取消息有关，似乎会影响消息高度！最初是1U，但由于unsigned int在char select后使其崩溃而更改
	Memory::WriteByte(0x00592A06 + 1, 0x01);//???可能与鼠标位置有关

	Memory::WriteInt(0x00744EB4 + 1, m_nGameWidth);//??与游戏中的截屏功能相关
	Memory::WriteInt(0x00744EB9 + 1, m_nGameHeight);//??与游戏中的截屏功能相关
	Memory::WriteInt(0x00744E2A + 1, 3 * m_nGameWidth * m_nGameHeight);//??与游戏中的截屏功能相关
	Memory::WriteInt(0x00744E43 + 1, m_nGameWidth * m_nGameHeight);//??与游戏中的截屏功能相关
	Memory::WriteInt(0x00744DA6 + 1, 4 * m_nGameWidth * m_nGameHeight);//??与游戏中的截屏功能相关
	Memory::WriteInt(0x00897BB4 + 1, (m_nGameWidth / 2) - 143);//??与经验增益/物品拾取消息相关
}

void GainItemMessage(int msgAmnt, int msgAmntOffset,void* ptrMoreGainMsgs,void* ptrMoreGainMsgsFade, void* ptrMoreGainMsgsFade1)
{
	int m_nGameWidth = 1280;
	int m_nGameHeight = 720;
	Memory::WriteInt(0x0089B639 + 1, m_nGameHeight - 6 - msgAmntOffset);//inventory/exp gain y axis //####hd100 //90
	Memory::WriteInt(0x0089B6F7 + 1, m_nGameWidth - 405);//inventory/exp gain x axis //310 //####hd415 //405
	Memory::WriteInt(0x0089AF33 + 1, 400);//在Davi的帮助下找到拾取和exp增益消息画布//的长度
	Memory::WriteInt(0x0089B2C6 + 1, 400);//地址将上面调整过的画布中的消息移动到新画布的中心//谢谢chris
	Memory::WriteInt(0x0089AEE2 + 3, msgAmnt);//moregainmsgs part 1
	Memory::CodeCave(ptrMoreGainMsgs, dwMoreGainMsgs, MoreGainMsgsNOPs); //moregainmsgs part 2
	Memory::CodeCave(ptrMoreGainMsgsFade, dwMoreGainMsgsFade, MoreGainMsgsFadeNOPs); //moregainmsgsFade
	Memory::CodeCave(ptrMoreGainMsgsFade1, dwMoreGainMsgsFade1, MoreGainMsgsFade1NOPs); //moregainmsgsFade1
	Memory::WriteInt(0x0045B337 + 1, m_nGameWidth);//与smega显示相关//smega可能开始弹出的屏幕区域
	Memory::WriteInt(0x0045B417 + 1, m_nGameWidth - 225);//带有头像x轴的smega在屏幕上持续时间
	Memory::WriteInt(0x007C2531 + 1, m_nGameHeight - 80);//??
	Memory::WriteInt(0x0089B796 + 2, m_nGameHeight - 18);//???related to exp gain/item pick up msg
	Memory::WriteInt(0x0089BA03 + 1, m_nGameHeight - 96); //??related to exp gain/item pick up msg
}

void VersionRightTop(void* ptrCodeCave, bool bUsed)
{
	int m_nGameWidth = 1280;
	if (bUsed) {
		Memory::WriteInt(0x005F464D + 1, m_nGameWidth - 165);	//mov eax,800 ; RelMove?	//紧贴屏幕一侧的登录框架的游戏版本号//您仍然需要偏移ntop，如果您的高度分辨率太大，则可能需要代码洞穴
	}
	else {
		Memory::CodeCave(ptrCodeCave, dwVersionNumberFix, dwVersionNumberFixNOPs);
	}
}

void CashShopMove2Center(void* ptrCashShopFix1, void* ptrCashShopFix2, void* ptrCashShopFix3, void* ptrCashShopFix4, void* ptrCashShopFix5, void* ptrCashShopFix6,
	void* ptrCashShopFix7, void* ptrCashShopFix8, void* ptrCashShopFixOnOff, void* ptrCashShopFixPrev, int imyWidth)
{
	Memory::CodeCave(ptrCashShopFix1, dwCashFix1, dwCashFix1NOPs);
	Memory::CodeCave(ptrCashShopFix2, dwCashFix2, dwCashFix2NOPs);
	Memory::CodeCave(ptrCashShopFix3, dwCashFix3, dwCashFix3NOPs);
	Memory::CodeCave(ptrCashShopFix4, dwCashFix4, dwCashFix4NOPs);
	Memory::CodeCave(ptrCashShopFix5, dwCashFix5, dwCashFix5NOPs);	//main part of shop, item listings	//thanks angel for stuff that helped
	Memory::CodeCave(ptrCashShopFix6, dwCashFix6, dwCashFix6NOPs);//code cave 6 //best sellers
	Memory::WriteInt(0x004694BA + 1, imyWidth + 690);//nleft, actual drawn part	//best sellers
	Memory::CodeCave(ptrCashShopFix7, dwCashFix7, dwCashFix7NOPs);
	Memory::CodeCave(ptrCashShopFix8, dwCashFix8, dwCashFix8NOPs);
	Memory::CodeCave(ptrCashShopFixOnOff, dwCashFixOnOff, dwCashFixOnOffNOPs);	//fix for preview On/Off button not being accurate on entering cash shop //thanks windyboy
	Memory::CodeCave(ptrCashShopFixPrev, dwCashFixPrev, dwCashFixPrevNOPs); //cash shop preview fix
}

void WorldSelectDlgMove2Right(int a1y, void* ptrLoginBackCanvasFix, void* ptrLoginViewRecFix, void* ptrLoginDescriptorFix)
{
	Memory::CodeCave(ptrLoginBackCanvasFix, dwLoginBackCanvasFix, LoginBackCanvasFixNOPs);	//worldselect按钮修复//感谢teto指出我在查找构造函数时的错误
	//yOffsetOfLoginBackBtnFix = 300 + myHeight; xOffsetOfLoginBackBtnFix = 0 + myWidth;	//后退按钮的参数
	//Memory::CodeCave(ccLoginBackBtnFix, dwLoginBackBtnFix, LoginBackBtnFixNOPs); //世界上的后退按钮选择//按钮随画布移动时不需要
	Memory::CodeCave(ptrLoginViewRecFix, dwLoginViewRecFix, LoginViewRecFixNOPs);	//world ViewRec fix	
	Memory::WriteInt(0x0060D849 + 1, 300 + a1y); //speed 1	//通过提高显示速度来临时修复，直到我在程序编程方面做得足够好
	//and memory management and reverse engineering to use nexon's own functions to put a black layer with greater z value to cover the tabs being shown off screen at origin
	Memory::CodeCave(ptrLoginDescriptorFix, dwLoginDescriptorFix, LoginDescriptorFixNOPs);	//world LoginDescriptor fix	
}

void CameraRepair(void* ptrAlwaysViewRestoreFix)
{
	int m_nGameWidth = 1280;
	int m_nGameHeight = 720;
	Memory::WriteInt(0x00641F61 + 1, (unsigned int)floor(m_nGameWidth / 2));	//mov ebc,400 ;  VRleft		//camera movement
	Memory::WriteInt(0x00641FC8 + 1, (unsigned int)floor(m_nGameHeight / 2));	//add eax,300  ; VRTop //camera movement //not working for most maps
	//Memory::WriteInt(0x0064202F + 2, (unsigned int)floor(m_nGameWidth / 2));	//mov ebc,400 ;  VRright		//camera movement	//crashes
	Memory::WriteInt(0x0064208F + 1, (unsigned int)floor(m_nGameHeight / 2));	//add eax,300  ; VRbottom 相机移动//不适用于大多数地图
	Memory::CodeCave(ptrAlwaysViewRestoreFix, dwAlwaysViewRestoreFix, dwAlwaysViewRestoreFixNOPs);	//修复所有地图上的视图恢复，目前什么都不做；我可能看错地方了
}

void PartyTradeChatMove()
{
	int m_nGameWidth = 1280;
	int m_nGameHeight = 720;
	Memory::WriteInt(0x00849E39 + 1, m_nGameHeight - 177); //系统菜单弹出
	Memory::WriteInt(0x0084A5B7 + 1, m_nGameHeight - 281); //快捷键弹出//0x84A5BD-系统选项“X”位置。如果需要

	Memory::WriteInt(0x00522C73 + 1, m_nGameHeight - 92);// ??v各种请求，如聚会，公会，朋友，家人，弹出的邀请
	Memory::WriteInt(0x00522E65 + 1, m_nGameHeight - 92); // ??various requests like party, guild, friend, family, invites that pop up
	Memory::WriteInt(0x0052307E + 1, m_nGameHeight - 92);// 各种请求，如聚会，公会，朋友，家人，弹出的邀请
	Memory::WriteInt(0x00523359 + 1, m_nGameHeight - 92);// various requests like party, guild, friend, family, invites that pop up
	Memory::WriteInt(0x00523595 + 1, m_nGameHeight - 92);// various requests like party, guild, friend, family, invites that pop up //quest complete y axis
	Memory::WriteInt(0x0052378B + 1, m_nGameHeight - 92);// various requests like party, guild, friend, family, invites that pop up
	Memory::WriteInt(0x0052397D + 1, m_nGameHeight - 92);// various requests like party, guild, friend, family, invites that pop up
	Memory::WriteInt(0x00523BB1 + 1, m_nGameHeight - 92);// various requests like party, guild, friend, family, invites that pop up
	Memory::WriteInt(0x00523DA5 + 1, m_nGameHeight - 92);// various requests like party, guild, friend, family, invites that pop up
	Memory::WriteInt(0x00523FA3 + 1, m_nGameHeight - 92);// various requests like party, guild, friend, family, invites that pop up
	Memory::WriteInt(0x005243DB + 1, m_nGameHeight - 92);// various requests like party, guild, friend, family, invites that pop up
	Memory::WriteInt(0x00523154 + 1, m_nGameHeight - 102);//?? various requests like party, guild, friend, family, invites that pop up
	Memory::WriteInt(0x0052418C + 1, m_nGameHeight - 102);//party quest available pop-up y axis		my first address find own my own
	Memory::WriteInt(0x00523092 + 1, m_nGameWidth - 942);//various requests like party, guild, friend, family, invites that pop up	//trade		 //thank you Rain for the width addresses
	Memory::WriteInt(0x0052336D + 1, m_nGameWidth - 942);//various requests like party, guild, friend, family, invites that pop up //Party Invite
	Memory::WriteInt(0x00522E79 + 1, m_nGameWidth - 942);//various requests like party, guild, friend, family, invites that pop up //friend request
	Memory::WriteInt(0x00522C87 + 1, m_nGameWidth - 942);//various requests like party, guild, friend, family, invites that pop up	// Guild Invite
	//Memory::WriteInt(0x005235A9 + 1, m_nGameWidth - 942);//various requests like party, guild, friend, family, invites that pop up	// Quest Complete, currently unneeded as working without it
	Memory::WriteInt(0x0052379F + 1, m_nGameWidth - 942);//various requests like party, guild, friend, family, invites that pop up//??
	Memory::WriteInt(0x00523991 + 1, m_nGameWidth - 942);//various requests like party, guild, friend, family, invites that pop up/??
	Memory::WriteInt(0x00523BC5 + 1, m_nGameWidth - 942);//various requests like party, guild, friend, family, invites that pop up/??
	Memory::WriteInt(0x00523DC5 + 1, m_nGameWidth - 942);//various requests like party, guild, friend, family, invites that pop up// ??
	Memory::WriteInt(0x00523FB7 + 1, m_nGameWidth - 942);//various requests like party, guild, friend, family, invites that pop up// ??
	Memory::WriteInt(0x005243EF + 1, m_nGameWidth - 942);//various requests like party, guild, friend, family, invites that pop up//??
}

void LongKeyboards(unsigned int uiArray_aDefaultQKM_0, unsigned int uiArray_Expanded, unsigned int uiArray_ptShortKeyPos, unsigned int uiArray_ptShortKeyPos_Fixed_Tooltips, unsigned int uicooldown_Array,
void* CompareValidateFuncKeyMappedInfo_cave, void* sub_9FA0CB_cave, void* sDefaultQuickslotKeyMap_cave, void* DefaultQuickslotKeyMap_cave, void* Restore_Array_Expanded)
{

	// CUIStatusBar::OnCreate
	Memory::WriteByte(0x008D155C + 1, 0xF0); // Draw rest of quickslot bar
	Memory::WriteByte(0x008D155C + 2, 0x03);
	Memory::WriteByte(0x008D182E + 1, 0xF0); // Draw rest of hotkeys
	Memory::WriteByte(0x008D182E + 2, 0x03);
	Memory::WriteByte(0x008D1AC0 + 1, 0xF0); // Draw rest of cooldowns, who tf knows why. TY Rulax
	Memory::WriteByte(0x008D1AC0 + 2, 0x03);

	//----CQuickslotKeyMappedMan::CQuickslotKeyMappedMan?????
	Memory::WriteInt(0x0072B7CE + 1, uiArray_aDefaultQKM_0);
	Memory::WriteInt(0x0072B8EB + 1, uiArray_aDefaultQKM_0);

	//----CUIStatusBar::CQuickSlot::CompareValidateFuncKeyMappedInfo
	Memory::WriteByte(0x008DD916, 0x1A); // increase 8 --> 26
	Memory::WriteByte(0x008DD8AD, 0x1A); // increase 8 --> 26
	Memory::WriteByte(0x008DD8FD, 0xBB);
	Memory::WriteInt(0x008DD8FD + 1, uiArray_Expanded);
	Memory::WriteByte(0x008DD8FD + 5, 0x90); //Errant byte
	Memory::WriteByte(0x008DD898, 0xB8);
	Memory::WriteInt(0x008DD898 + 1, uiArray_Expanded);
	Memory::WriteByte(0x008DD898 + 5, 0x90); //Errant Byte

	//----CUIStatusBar::CQuickSlot::Draw
	Memory::WriteByte(0x008DE75E + 3, 0x6C);
	Memory::WriteByte(0x008DDF99, 0xB8);
	Memory::WriteInt(0x008DDF99 + 1, uiArray_Expanded);
	Memory::FillBytes(0x008DDF99 + 5, 0x90, 3); // Nopping errant operations

	//----CUIStatusBar::OnMouseMove
	Memory::WriteByte(0x008D7F1E + 1, 0x34);
	Memory::WriteByte(0x008D7F1E + 2, 0x85);
	Memory::WriteInt(0x008D7F1E + 3, uiArray_Expanded);

	//----CUIStatusBar::CQuickSlot::GetPosByIndex
	Memory::WriteInt(0x008DE94D + 2, uiArray_ptShortKeyPos);
	Memory::WriteInt(0x008DE955 + 2, uiArray_ptShortKeyPos + 4);
	Memory::WriteByte(0x008DE941 + 2, 0x1A); //change cmp 8 --> cmp 26

	//CUIStatusBar::GetShortCutIndexByPos
	Memory::WriteInt(0x008DE8F4 + 1, uiArray_ptShortKeyPos_Fixed_Tooltips + 4);
	Memory::WriteByte(0x008DE926 + 1, 0x3E);

	//CUIStatusBar::CQuickSlot::DrawSkillCooltime
	Memory::WriteByte(0x008E099F + 3, 0x1A);
	Memory::WriteByte(0x008E069D, 0xBE);
	Memory::WriteInt(0x008E069D + 1, uicooldown_Array); //Pass enlarged FFFFF array
	Memory::WriteByte(0x008E069D + 5, 0x90); //Errant byte
	Memory::WriteByte(0x008E06A3, 0xBF);
	Memory::WriteInt(0x008E06A3 + 1, uiArray_Expanded + 1);
	Memory::WriteByte(0x008E06A3 + 5, 0x90);

	//----CDraggableMenu::OnDropped
	Memory::WriteByte(0x004F928A + 2, 0x1A); //change cmp 8 --> cmp 26
	//----CDraggableMenu::MapFuncKey
	Memory::WriteByte(0x004F93F9 + 2, 0x1A); //change cmp 8 --> cmp 26
	//----CUIKeyConfig::OnDestroy
	Memory::WriteByte(0x00833797 + 2, 0x6C); // Updates the offset to 108 (triple) (old->24h)
	Memory::WriteByte(0x00833841 + 2, 0x6C); // Updates the offset to 108 (triple) (old->24h)
	Memory::WriteByte(0x00833791 + 1, 0x68); // push 68h (triple)
	Memory::WriteByte(0x0083383B + 1, 0x68); // push 68h (triple)
	//----CUIKeyConfig::~CUIKeyConfig
	Memory::WriteByte(0x0083287F + 2, 0x6C); // triple the base value at this hex (old->24h)
	Memory::WriteByte(0x00832882 + 1, 0x68); // push 68h (triple)
	//----CQuickslotKeyMappedMan::SaveQuickslotKeyMap
	Memory::WriteByte(0x0072B8C0 + 2, 0x6C); // triple the base value at this hex (old->24h)
	Memory::WriteByte(0x0072B8A0 + 1, 0x68); // push 68h, (triple) //CQuickslotKeyMappedMan::SaveQuickslotKeyMap
	Memory::WriteByte(0x0072B8BD + 1, 0x68); // push 68h, (triple) //CQuickslotKeyMappedMan::SaveQuickslotKeyMap
	//----CQuickslotKeyMappedMan::OnInit
	Memory::WriteByte(0x0072B861 + 1, 0x68); // push 68h (triple) (these ones might have to be just 60)
	Memory::WriteByte(0x0072B867 + 2, 0x6C); // triple the base value at this hex (old->24h)
	//----CUIKeyConfig::CNoticeDlg::OnChildNotify????
	Memory::WriteByte(0x00836A1E + 1, 0x68); // push 68h (triple)
	Memory::WriteByte(0x00836A21 + 2, 0x6C); // triple the base value at this hex (old->24h)


// CODECAVES CLIENT EDITS ---- 
	Memory::CodeCave(CompareValidateFuncKeyMappedInfo_cave, 0x8DD8B8, 5);
	Memory::CodeCave(sub_9FA0CB_cave, 0x9FA0DB, 5);
	Memory::CodeCave(sDefaultQuickslotKeyMap_cave, 0x72B7BC, 5);
	Memory::CodeCave(DefaultQuickslotKeyMap_cave, 0x72B8E6, 5);
	Memory::CodeCave(Restore_Array_Expanded, 0x008CFDFD, 6); //restores the skill array to 0s

	SetKeyboardPosition();
}


void ExtraHere()
{
	//如您有好用的地址请在此处添加或额外封装~！  by汪汪汉堡包
}