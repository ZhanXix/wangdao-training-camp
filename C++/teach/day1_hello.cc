                    //C++的编程规范

//#include "hello.h"  //用双引号括起来的，就先在当前路径下查找
                    //再去系统路径进行查找
                    //这种自定义头文件要放在最前面

#include <stdio.h>  //C头文件要放在C++头文件的上面

#include <iostream> //C++的头文件不带.h的后缀，
                    //大部分头文件都是用模板实现的

using namespace std;    //命名空间

int main(int argc,char ** argv)
{
    printf("Hello,world!\n");   //用流操作的运算时间比printf要高一些
    cout << "Hello,world!" << endl; //cout是一个对象
                                    //运算符重载
    //相当于 operator<<(operator<<(cout,"Hello,world!")),endl)
    return 0;
}

