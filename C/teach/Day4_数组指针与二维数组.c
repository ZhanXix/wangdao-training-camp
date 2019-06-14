#include <stdio.h>
#include <stdlib.h>

//数组指针与二维数组
void print(int(*p)[4], int row)//数组指针 传递 二维数组
{
	printf("sizeof(p)=%d\n", sizeof(p));//4
	printf("sizeof(p[0])=%d\n", sizeof(p[0]));//16，p[0]即*(p+0)
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < sizeof(*p) / sizeof(int); ++j)
		{
			printf("%3d", *(*(p + i)+j));
			//等价于printf("%3d", p[i][j]);
		}
		putchar('\n');
	}
}
int main()
{
	int a[3][4] = { 1,3,5,7,2,4,6,8,9,11,13,15 };
	int(*p)[4];	//数组指针，p指向长度为4的一维数组
	int b[4] = { 1,2,3,4 };
	p = a;
	print(p, 3);
	p = (int(*)[4])malloc(16 * 100);//动态二维数组
	p[99][3] = 1000;
	system("pause");
}
