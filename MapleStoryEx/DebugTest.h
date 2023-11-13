#pragma once


class DebugTest
{
public:
    DebugTest();
    virtual ~DebugTest() {};
     
    //人物HP,MP当前显示
    int sub_8D850B(int, int, int, int, int, int Unknown, char* pcVal);

    int onkey(int wparam, int lparam);
};