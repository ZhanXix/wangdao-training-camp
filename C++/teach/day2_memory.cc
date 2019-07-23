#include <stdio.h>
#include <string.h>
#include <iostream>

int a=0;
char *p1;//全局变量即使没有显式进行初始化，系统也会清零

int test0()
{
    int b;
    char s[] = "hello,world";
    char *p2;//在栈上，没有显示初始化就不会清零，出现野指针

    const char *p3 = "hello,world";//文字常量区，只读，不能进行修改

    static int c = 0;//不在栈上，位于全局静态区
    ++c;

    printf("&a = %p\n",&a);
    printf("&b = %p\n",&b);
    printf("&c = %p\n",&c);
    printf("c = %d\n",c);

    printf("&p1 = %p\n",&p1);
    printf("p1 = %p\n",p1);
   
    p1 = new char[10];
    strcpy(p1,"helloworld");
    
    printf("&p1 = %p\n",&p1);
    printf("p1 = %p\n",p1);

    printf("&p2 = %p\n",&p2);
    printf("p2 = %p\n",p2);

    printf("s = %p\n",s);

    printf("&p3 = %p\n",&p3);
    printf("p3 = %p\n",p3);

    printf("&test0 = %p\n",&test0);
    return 0;
}

int main()
{
    test0();
    putchar('\n');
    test0();
    putchar('\n');
    test0();
    putchar('\n');
    return 0;
}

