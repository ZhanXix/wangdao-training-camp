#include <stdlib.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

void test0()
{
    int *pint = (int*)malloc(sizeof(int));  //系统调用
    *pint = 10;

    int *pint2 = (int*)malloc(sizeof(int)*10);
    memset(pint2,0,sizeof(int)*10);

    free(pint);
    free(pint2);
}

//
//malloc/free与new/delete表达式的区别？
//1.malloc/free是库函数；new/delete是表达式
//2.malloc开辟空间的时候，没有进行初始化
//  new表达式是开辟空间的同时，还进行了初始化
//  

void test1()
{
    int *pint = new int(1); //new表达式
    cout << "*pint = " << *pint << endl;

    int *pint3 = new int[10];//没有进行初始化
    int *pint2 = new int[10]();//加了小括号会进行初始化，全部清零

    delete pint;//delete表达式
                //new和delete成对出现

    delete [] pint2;
}

int main()
{
    test1();
    return 0;
}

