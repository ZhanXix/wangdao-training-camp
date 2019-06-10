#include <stdio.h> 
#include <stdlib.h>

//使用非递归方法
int main()
{
	int n, i, first, second, third;
	while (scanf("%d", &n) != EOF)
	{
		first = 0, second = 1;
		for (i = 0; i < n; i++)
		{
			third = first + second;
			first = second;
			second = third;
		}
		printf("走上%d阶台阶有%d种方法\n", n, third);
	}
}
