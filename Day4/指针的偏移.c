#include <stdio.h>
#include <stdlib.h>


//指针的偏移
#define N 5
void print(int *p)
{
	printf("sizeof(p)=%d\n", sizeof(p));
	for (int i = 0; i < N; i++)
	{	//顺序输出
		printf("%3d", *(p + i));
	}
	putchar('\n');
}
int main()
{
	int a[N] = { 1,2,3,4,5 };
	//数组里存储的是数组的起始地址，类型是整型指针
	int* p;
	int i;
	p = a;
	print(a);
	printf("-------------------------------\n");
	p = &a[4];
	for (i = 0; i < N; i++)
	{	//逆序输出
		printf("%3d", *(p - i));
	}
	putchar('\n');
	system("pause");
}
