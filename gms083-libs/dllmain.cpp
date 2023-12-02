// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "NMCO.h"
#include "ijl15.h"
#include "INIReader.h"
#include "ReplacementFuncs.h"
#include <comutil.h>

void CreateConsole() {
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout); //CONOUT$
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
	{
		//CreateConsole();	//

		INIReader reader("config.ini");
		if (reader.ParseError() == 0) {
			Client::MsgAmount = reader.GetInteger("Hamburgers", "MsgAmount", 26);
			Client::setDamageCap = reader.GetReal("Hamburgers", "setDamageCap", 199999.0);
			Client::speedMovementCap = reader.GetInteger("Hamburgers", "speedMovementCap", 140);
			Client::ServerIP_AddressFromINI = reader.Get("Hamburgers", "ServerIP_Address", "127.0.0.1");
			Client::bIfMutiClient = reader.GetBoolean("Hamburgers", "MutiClient", false);
			Client::bIfLoadImgClient = reader.GetBoolean("Hamburgers", "LoadImgClient", true);
			Client::bIfMoveCashShopToCenter = reader.GetBoolean("Hamburgers", "IfMoveCashShopToCenter", true);
			Client::bVersionPosition = reader.GetBoolean("Hamburgers", "IfVersionPosition", true);
			Client::iVersionPositionH = reader.GetInteger("Hamburgers", "VersionPositionH", 645);
			Client::iVersionPositionV = reader.GetInteger("Hamburgers", "VersionPositionV", 10);
		}

		//多开
		if (Client::bIfMutiClient)
		{
			Hook_CreateMutexA(true); //multiclient 
		}
		
		//img客户端
		if (Client::bIfLoadImgClient)
		{
			HookPcCreateObject_IWzResMan(true);
			HookPcCreateObject_IWzNameSpace(true);
			HookPcCreateObject_IWzFileSystem(true);
			HookCWvsApp__Dir_BackSlashToSlash(true);
			HookCWvsApp__Dir_upDir(true);
			Hookbstr_ctor(true);
			HookIWzFileSystem__Init(true);
			HookIWzNameSpace__Mount(true);
			HookCWvsApp__InitializeResMan(true); //experimental //ty to all the contributors of the ragezone release: Client load .img instead of .wz v62~v92
		}




		//Hook_StringPool__GetString(true); //hook stringpool modification //ty !! popcorn //ty darter
		//Hook_lpfn_NextLevel(true);
		//Hook_get_unknown(true);
		//Hook_get_resource_object(true); //helper function hooks  //ty teto for helping me get started
		//Hook_com_ptr_t_IWzProperty__ctor(true);
		//Hook_com_ptr_t_IWzProperty__dtor(true);

		Client::UpdateGameStartup();

		//std::cout << "Applying resolution " << Client::m_nGameWidth << "x" << Client::m_nGameHeight << std::endl;
		Client::UpdateResolution();

		//std::cout << "GetModuleFileName hook created" << std::endl;
		ijl15::CreateHook(); //NMCO::CreateHook();
		//std::cout << "NMCO hook initialized" << std::endl;
		break;
	}
	default: break;
	case DLL_PROCESS_DETACH:
		ExitProcess(0);
	}
	return TRUE;
}