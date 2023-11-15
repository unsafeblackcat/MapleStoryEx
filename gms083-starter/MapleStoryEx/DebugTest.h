#pragma once


class DebugTest
{
public:
    DebugTest();
    virtual ~DebugTest() {};
     
    //人物HP,MP当前显示
    int sub_8D850B(int, int, int, int, int, int Unknown, char* pcVal);

    //键盘按键回调
    int onkey(int wparam, int lparam); 
};


void __stdcall send_msg(char** param1, int param2);