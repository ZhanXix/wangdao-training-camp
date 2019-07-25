#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::string;

void printCinStatus()
{
    cout << "cin's badbit = " << cin.bad() << endl;
    cout << "cin's failbit = " << cin.fail() << endl;
    cout << "cin's eofbit = " << cin.eof() << endl;
    cout << "cin's goodbit = " << cin.good() << endl;
}

void test0()
{
    cout << "sizeof(cin) = " << sizeof(cin) << endl;
    cout << "sizeof(cout) = " << sizeof(cout) << endl;

    int number = 0;
    printCinStatus();
    //cin >> number 其返回值还是流对象，
    //再去检测流对象是否处于有效状态
    while(cin >> number)
    {
        cout << "number = " << number << endl;
    }
    printCinStatus();

    cin.clear(); //重置流的状态
    //cin.ignore(100,'\n'); //清空缓冲区
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cout << "重置流的状态" << endl;
    printCinStatus();

    string s1;
    cin >> s1;
    cout << "s1 = " << s1 << endl;
}

void test1()
{
    int number = 0;
    cout << "pls input a valid interger:" << endl;
    while(cin >> number,!cin.eof())
    {
        if(cin.bad())
        {
            cout << "cin has corrupted!" << endl;
            return;
        }else if (cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout << "pls input a valid interger:" << endl;
            continue;
        }
        cout << "number = " << number << endl;
    }
}

int main()
{
    //test0();
    test1();

    return 0;
}

//Linux:
//Ctrl+C 终结程序
//Ctrl+D 结束流的输入
//Ctrl+Z 将当前执行程序挂起到后台运行(用fg挂到前台)
