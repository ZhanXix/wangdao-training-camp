#include <iostream>
using std::cout;
using std::endl;

//带参数的宏定义
#define multiply(x,y) x*y
#define multiply_ture(x,y) ((x)*(y))//正确写法

//函数调用是有开销的
//
//inline函数是可以取代带参数的宏定义的
inline int divide(int x,int y);//函数声明

int main()
{
    int a=5, b=4;
    cout << multiply(a,b) << endl;
    cout << multiply(a+b,b) << endl;//试图得到(a+b)*b,实际替换为 a+b*b
                                    //运行时错误
    cout << multiply_ture(a+b,b) << endl;

    cout << divide(a,b) << endl;

    return 0;
}

inline int divide(int x,int y)//函数实现(inline函数的实现和声明必须在一个文件里面)
{
    return x/y;
}
