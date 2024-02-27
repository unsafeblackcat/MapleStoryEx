#pragma once

class CFunction
{
public:
	static CFunction* m_This;
	static CFunction* pins();

private:
	CFunction();
	virtual ~CFunction();

public:
	void auto_login(const char* name, const char* password);
};

