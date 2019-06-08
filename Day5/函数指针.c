#include <stdio.h>
#include <stdlib.h>

//函数指针
void b()
{
	printf("I am b func.\n");
}
void a(void (*p)())//面向接口编程
{
	p();
}
int main()
{
	void(*p)();//p函数指针
	a(b);
	system("pause");
}
