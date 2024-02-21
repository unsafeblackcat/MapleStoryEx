#pragma once
class CWvsApp
{
public:
	static CWvsApp* m_this;
	static CWvsApp* pins();

private:
	CWvsApp();
	virtual ~CWvsApp();
};

