#include <stdio.h>
#include <stdlib.h>

//野指针的危险性
int main()
{
	int* p1, * p2, * p3;
	p1 = (int*)malloc(4);
	*p1 = 1;
	printf("*p1=%d\n", *p1);
	p2 = (int*)malloc(4);
	*p2 = 2;
	printf("*p2=%d\n", *p2);
	free(p2);	//这里已经free了
	//p2=NULL	//free以后没有设置为NULL的指针称为野指针
	p3 = (int*)malloc(4);
	*p3 = 3;
	printf("*p3=%d\n", *p3);	//3
	*p2 = 100;	//p2是野指针，而且实际上指向了p3的地址，上次free的空间给了下一个malloc分配
	printf("*p3=%d\n", *p3);	//100
	system("pause");
}
