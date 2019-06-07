#include <stdio.h>
#include <stdlib.h>

//指针与自增自减运算符组合
int main()
{
	int a[] = { 2,7,8 };
	int* p;
	int j;
	p = a;
	j = *p++;//j=*p;p++;  *与++优先级相同
	printf("a[0]=%d,j=%d,*p=%d\n", a[0], j, *p);//2,2,7
	j = p[0]++;
	//p[0]与(*p)相同，即j=(*p)++
	//j=*p;(*p)++;
	printf("a[0]=%d,j=%d,*p=%d\n", a[0], j, *p);//2,7,8
	system("pause");
}
