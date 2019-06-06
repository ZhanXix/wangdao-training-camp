#include <stdio.h> 
#include <stdlib.h> 

//打印空心菱形-作业教学
int main()
{
	int i, j;
	for (i = 0; i < 9; i++)//外层控制行
	{
		for (j = 0; j < abs(4 - i); j++)//每一列打印什么
		{
			putchar(' ');
		}
		for (j = 0; j < 9 - 2 * abs(4 - i); j++)
		{
			if (j == 0 || j == (8 - 2 * abs(4 - i)))
			{
				putchar('*');
			}
			else {
				putchar(' ');
			}
		}
		putchar('\n');
	}
	system("pause");
}
