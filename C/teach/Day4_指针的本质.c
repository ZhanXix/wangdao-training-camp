#include <stdio.h>
#include <stdlib.h>

//指针的本质
int main()
{
	int i = 10;
	scanf("%d", &i);
	printf("i=%d\n", i);	//直接访问
	int* iPointer = &i;	//指针初始化一定是某个变量的取地址
	printf("*iPointer=%d\n", *iPointer);	//间接访问
	system("pause");
}
