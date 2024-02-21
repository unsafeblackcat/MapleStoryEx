#include "CConfig.h"
#include "memory.h"

typedef int (__fastcall *pfunCConfig_GetPartnerCode)(CConfig* pthis, int dummy);
static pfunCConfig_GetPartnerCode g_CConfig_GetPartnerCode = nullptr;

CConfig* CConfig::m_this = nullptr;
CConfig* CConfig::pins()
{
	if (m_this == nullptr)
	{
		int pins_value = 0;
		do
		{
			::Sleep(1000);
			memory::read(0x00BEBF9C, pins_value);
		} while (pins_value == 0);

		m_this = (CConfig*)pins_value;
		m_this->init();
	}

	return m_this;
}

CConfig::CConfig()
{ 
}

CConfig::~CConfig()
{ 
}

void 
CConfig::init()
{ 
	g_CConfig_GetPartnerCode = (pfunCConfig_GetPartnerCode)0x005F6CFB;
	return;
}

int 
CConfig::GetPartnerCode()
{
	return g_CConfig_GetPartnerCode(this, 0);
}