#define WIN32_LEAN_AND_MEAN
#include "CFunction.h"
 
#include "COutPacket.h"
#include "CClientSocket.h"
#include "CSystemInfo.h"
#include "CWvsApp.h"
#include "CConfig.h"

static ZXString<char> g_user;
static ZXString<char> g_password;

CFunction* CFunction::m_This = nullptr;
CFunction* CFunction::pins()
{
	if (m_This == nullptr)
	{
		m_This = new CFunction();
	}

	return m_This;
}


CFunction::CFunction()
{ 
}
	
CFunction::~CFunction()
{

}

void 
CFunction::auto_login(
	const char* name
	, const char* password)
{
	CSystemInfo sysi;
	sysi.Init();
	  
	g_user = name;
	g_password = password;
	 
	COutPacket loading(1);

	loading.EncodeStr(g_user);
	loading.EncodeStr(g_password);

// 	struct _tagString
// 	{
// 		int m_max_buffer = 0;
// 		char m_str[0];
// 	};
// 
// 	char name_buffer[256];
// 	_tagString* name = (_tagString*)name_buffer;
// 	strcpy(name->m_str, "admin");
// 	name->m_max_buffer = strlen("admin");
// 	loading.EncodeStr(name->m_str);
// 
// 	SOCKET_ERROR
// 		char password_buffer[256];
// 	_tagString* password2 = (_tagString*)password_buffer;
// 	strcpy(password2->m_str, "admin");
// 	password2->m_max_buffer = strlen("admin");
// 	loading.EncodeStr(password2->m_str);

	unsigned char* pMachineId = sysi.GetMachineId();
	loading.EncodeBuffer(pMachineId, 0x10);

	int GameRoomClient = sysi.GetGameRoomClient();
	loading.Encode4(GameRoomClient);

	unsigned char* pCWvsApp = (unsigned char*)CWvsApp::pins();
	char ch = *(pCWvsApp + 0x24);
	loading.Encode1(ch);
	loading.Encode1(0);
	loading.Encode1(0);

	int ccpc = CConfig::pins()->GetPartnerCode();
	loading.Encode4(ccpc);

	CClientSocket::pins()->SendPacket(&loading);

	return;
}