#pragma once

#include <map>

#define KEY_CODE(KEY) KeyCode::pins()->get(KEY);

class KeyCode
{
public:
    static KeyCode* m_this;
    static KeyCode* pins();
private:
    KeyCode();
    virtual ~KeyCode();

public:
    int get(int k);

private:
    std::map<int, int> m_key_code;
};

