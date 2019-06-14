#include <stdio.h>
#include <stdlib.h>

//二级指针的偏移
#define N 5
//排序排指针数组
void print(char(*p)[10])
{
	int i;
	for (i = 0; i < N; i++)
	{
		puts(p[i]);
	}
}
void printPointArr(char **p)
{
	int i;
	for (i = 0; i < N; i++)
	{
		puts(p[i]);
	}
}
int main()
{
	char* pArr[N];
	char b[N][10] = { "lele","lili","lilei","hanmeimei","zhousi" };
	int i, j;
	char* pTemp;
	char** p2=(char**)malloc(sizeof(char*)*N);
	//二级指针的初始化必须是某一个一级指针取地址
	for (i = 0; i < N; i++)
	{
		p2[i] = b[i];
	}
	print(b);
	for (i = N; i > 1; i--)
	{
		for (j = 0; j < i - 1; j++)
		{
			if (strcmp(p2[j], p2[j + 1]) > 0)
			{
				pTemp = p2[j];
				p2[j] = p2[j + 1];
				p2[j + 1] = pTemp;
			}
		}
	}//索引式排序
	printf("---------------------------\n");
	printPointArr(p2);
	printf("---------------------------\n");
	print(b);
	system("pause");
}
