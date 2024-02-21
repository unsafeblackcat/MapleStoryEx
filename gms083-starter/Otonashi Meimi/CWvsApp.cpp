#define WIN32_LEAN_AND_MEAN
#include "CWvsApp.h"
#include <windows.h>

#include "memory.h"

CWvsApp* CWvsApp::m_this = nullptr;
CWvsApp* CWvsApp::pins()
{
	if (m_this == nullptr)
	{
		int pins_value = 0;
		do
		{
			::Sleep(1000);
			memory::read(0x00BE7B38, pins_value);
		} while (pins_value == 0);

		m_this = (CWvsApp*)pins_value;
	}

	return m_this;
}


CWvsApp::CWvsApp()
{ 
}

CWvsApp::~CWvsApp()
{ 
}