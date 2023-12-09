#include "KeyCode.h"

KeyCode* KeyCode::m_this = nullptr;
KeyCode* KeyCode::pins()
{
    if (m_this == nullptr)
    {
        m_this = new KeyCode;
    }

    return m_this;
}

KeyCode::KeyCode()
{
#define INSERT(k,v) m_key_code.insert(std::pair<int, int>(k,v));

    int i = 'A';
    INSERT(i++, 0x001E);
    INSERT(i++, 0x0030);
    INSERT(i++, 0x002E);
    INSERT(i++, 0x0020);
    INSERT(i++, 0x0012);
    INSERT(i++, 0x0021);
    INSERT(i++, 0x0022);
    INSERT(i++, 0x0023);
    INSERT(i++, 0x0017);
    INSERT(i++, 0x0024);
    INSERT(i++, 0x0025);
    INSERT(i++, 0x0026);
    INSERT(i++, 0x0018);
    INSERT(i++, 0x0019);
    INSERT(i++, 0x0010);
    INSERT(i++, 0x0013);
    INSERT(i++, 0x001F);
    INSERT(i++, 0x0014);
    INSERT(i++, 0x0016);
    INSERT(i++, 0x002F);
    INSERT(i++, 0x0011);
    INSERT(i++, 0x002D);
    INSERT(i++, 0x0015);
    INSERT(i++, 0x002C); 

    i = 49;
    //1~0
    INSERT(i++, 0x0002);
    INSERT(i++, 0x0003);
    INSERT(i++, 0x0004);
    INSERT(i++, 0x0005);
    INSERT(i++, 0x0006);
    INSERT(i++, 0x0007);
    INSERT(i++, 0x0008);
    INSERT(i++, 0x0009);
    INSERT(i++, 0x000A);
    INSERT(i++, 0x000B);


    i = 112;
    //F1~F12
    INSERT(i++, 0x003B);
    INSERT(i++, 0x003C);
    INSERT(i++, 0x003D);
    INSERT(i++, 0x003E);
    INSERT(i++, 0x003F);
    INSERT(i++, 0x0040);
    INSERT(i++, 0x0041);
    INSERT(i++, 0x0042);
    INSERT(i++, 0x0043);
    INSERT(i++, 0x0044);
    INSERT(i++, 0x0057);
    INSERT(i++, 0x0058);

    //~
    INSERT(229, 0x0029);

    //特殊按键
    INSERT(45, 0x152);
    INSERT(36, 0x147);
    INSERT(33, 0x149);
    INSERT(46, 0x153);
    INSERT(35, 0x14F);
    INSERT(34, 0x151);
}

KeyCode::~KeyCode()
{

}

int 
KeyCode::get(
    int k)
{
    auto it = m_key_code.find(k);
    if (it != m_key_code.end())
    {
        return it->second;
    }
    return 0;
}