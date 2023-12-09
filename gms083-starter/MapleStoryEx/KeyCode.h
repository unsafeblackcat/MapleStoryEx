#pragma once

#include <map>
  
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

