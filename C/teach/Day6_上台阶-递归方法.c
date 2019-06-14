#include <stdio.h> 
#include <stdlib.h>

//递归的性能<非递归
//函数递归调用是有上限的，实验了一下，上限差不多是4790
int f(n)
{
	if (n == 1)
	{
		return 1;
	}
	if (n == 2)
	{
		return 2;
	}
	else
	{
		return f(n - 1) + f(n - 2);
	}
}
int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		printf("走上%d阶台阶有%d种方法\n", n, f(n));
	}
}
