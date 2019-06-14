/*
从（0,0）到（m,n),每次走一步，只能向上或者向右走，有多少种路径走到(m,n)
*/

#include <stdio.h> 
#include <stdlib.h> 

void walk(int m1, int n1, int m2, int n2)
{
	printf("(%d,%d)->(%d,%d)", m1, n1, m2, n2);
}

int road(int m, int n)
{
	int result1 = 0, result2 = 0;
	if (0 == m)
	{
		putchar('\n');
		for (int i = 0; i < n; ++i)
		{
			walk(0, i, 0, i + 1);
		}
		return 1;
	}
	else if (0 == n)
	{
		putchar('\n');
		for (int i = 0; i < m; ++i)
		{

			walk(i, 0, i + 1, 0);
		}
		return 1;
	}
	else
	{
		result1 = road(m - 1, n);
		walk(m - 1, n, m, n);
		result2 = road(m, n - 1);
		walk(m, n-1, m, n);
		return result1+result2;
	}
}
int main()
{
	int m, n;
	while (scanf("%d%d", &m, &n) != EOF)
	{
		printf("\n从(0,0)有%d种路径走到(%d,%d)\n", road(m, n), m, n);
	}
	system("pause");
	return 0;
}
//打印的路径不太完整，但是每行都不一样，需要对照下行来看具体路径
//暂时没有想到打印完整路径的较好方法，待日后改良