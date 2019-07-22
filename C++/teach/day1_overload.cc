#include <stdio.h>

int add(int x,int y)
{
    return x+y;
}

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

