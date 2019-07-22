#include <stdio.h>

//C++为了兼容C

//实现了C和C++的混合编程
#ifdef __cplusplus 
extern "C" //用c的方式进行调用
{
#endif

int add(int x,int y)
{
    return x+y;
}

#ifdef __cplusplus
}//end of extern "C"
#endif

//进行名字改编：用C++的方式进行调用
//不进行名字改编：用C的方式进行调用

int add(int x,int y,int z)
{
    return x+y+z;
}

float add(float x,float y)
{
    return x+y;
}

int add(int x,float y)
{
    return x+y;
}

int add(float x,int y)
{
    return x+y;
}

//C不支持函数重载

//C++支持函数重载
//实现原理：名字改编(name mangling)
//具体的操作步骤：当函数名称相同时，
//                会根据函数参数的类型、个数、顺序进行改编

int main(int argc,char *argv[])
{
    int a=3,b=4;
    printf("add(a,b) = %d\n",add(a,b));
    return 0;
}

