#include "Mylogger.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#define prefix(msg) string("[").append(__FILE__)\
        .append(":").append(__FUNCTION__)\
        .append(":").append(std::to_string(__LINE__))\
        .append("] ").append(msg)
            

void test0()
{
    wd::Mylogger::getInstance()->error(prefix("this is error message").c_str());
    wd::Mylogger::getInstance()->warn(prefix("this is warn message").c_str());
    wd::Mylogger::getInstance()->info(prefix("this is info message").c_str());
    wd::Mylogger::getInstance()->debug(prefix("this is debug message").c_str());
    
    wd::Mylogger::destroy();
}

void test1()
{
    //系统提供给我们的内置宏
    cout << __FILE__ << endl
         << __LINE__ << endl
         << __FUNCTION__ << endl;
}

void test2()
{
    LogError("this is error message");
    LogWarn("this is warn message");
    LogInfo("this is info message");
    LogDebug("this is debug message");

    wd::Mylogger::destroy();
}

int main()
{
    //test0();
    //test1();
    test2();
    return 0;
}

