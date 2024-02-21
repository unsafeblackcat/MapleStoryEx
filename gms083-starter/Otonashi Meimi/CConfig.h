#pragma once

class CConfig
{
public:
	static CConfig* m_this;
	static CConfig* pins();

private:
	CConfig();
	virtual ~CConfig();

	void init();

public:
	int GetPartnerCode();

};

