#include <iostream>
using std::cout;
using std::endl;

class Example
{
public:
    int operator()(int x, int y)
    {
        ++_count;
        return x + y;
    }

    int operator()(int x, int y, int z)
    {
        ++_count;
        return  x * y * z;
    }

    int callTime() { return _count; }

private:
    int _count = 0;
};

int add(int x,int y)
{
    static int count = 0;
    ++count;
    cout << "count = " << count << endl;
    return x + y;
}

int main()
{
    //重载了函数调用运算符的类创建的对象，称为函数对象
    //
    //携带了状态的函数对象，又可以称为闭包 ===> lambda表达式  ===> 匿名函数
    Example e1;

    int a=3, b=4, c=5;
    cout << "e1(a,b) = " << e1(a,b) << endl;
    cout << "add(a,b)= " << add(a,b) << endl;
    cout << "e1(a,b,c) = " << e1(a,b,c) << endl;
    cout << "add(a,b)= " << add(a,b) << endl;
    cout << "e1.callTime() = " << e1.callTime() << endl;

    return 0;
}

