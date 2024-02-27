#include "ZAllocEx2.h"

typedef void (__fastcall* pfunZAllocEx_Free)(void* pthis, int dumm, void* buffer);
static pfunZAllocEx_Free g_ZAllocEx_Free = nullptr;

 
void* 
ZAllocEx2::Alloc(int len)
{
	return nullptr;
}

void 
ZAllocEx2::Free(
	void* buffer)
{
	if (g_ZAllocEx_Free == nullptr)
	{
		g_ZAllocEx_Free = (pfunZAllocEx_Free)0x004031ED;
	}

	g_ZAllocEx_Free((void*)0x00BF0B00, 0, buffer);
	return ;
}