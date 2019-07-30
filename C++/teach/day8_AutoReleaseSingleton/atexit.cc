/*
函数名: atexit
头文件: #include<stdlib.h>
功 能: 注册终止函数(即main执行结束后调用的函数)
用 法: void atexit(void (*func)(void));
注意：exit调用这些注册函数的顺序与它们 登记时候的顺序相反。同一个函数如若登记多次，则也会被调用多次。
*/

#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;

void display()
{
	cout << "display() " << endl;
}
 
int main(void)
{
	cout << "enter main function..." << endl;
	::atexit(display);
	::atexit(display);
 
	cout << "exit main function..." << endl;
	return 0;
}
