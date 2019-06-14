#include "变量及函数的作用域-func.h"

//变量及函数的作用域
int k = 10;//全局变量作用域在定义位置到本文件结束
//千万不能在头文件定义全局变量,因为这样会造成重定义
static int k2 = 10;
//全局变量如果前面加上static,其他文件就不能借用了
//若用static修饰函数，那么该函数将不能被其他文件引用
void print()
{
	static int i = 0;//静态局部变量只会初始化一次
	//不同函数内可以有同名的局部变量
	i++;
	printf("i=%d\n", i);
}
int main()
{
	int i = 10;
	{
		int j = 5;//变量在离自己最近的大括号内有效
	}
	//printf("%d\n", j);
	print();
	print();
	printf("I am main, k=%d\n", k);
	printf("I am main, k2=%d\n", k2);
	print2();
	system("pause");
}