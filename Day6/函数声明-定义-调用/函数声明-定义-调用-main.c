//函数声明-定义-调用-main.c
#include "函数声明-定义-调用-func.h"//双引号优先在当前路径搜索

int main()
{
	int a = 10;
	a=printStar(a);//函数调用
	printMessage();
	system("pause");
}

