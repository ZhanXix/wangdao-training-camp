/*
打印如下图形：
    *
   * *
  * * *
 * * * *
* * * * *
 * * * *
  * * *
   * *
    *

*/

#include <stdio.h> 
#include <stdlib.h> 

int main()
{
	for (int i = 0; i < 9; ++i)	//行数
	{
		for (int j = 0; j < abs(i - 4); ++j) //打印*前的空格
		{
			putchar(' ');
		}
		for (int j = 0; j < 9 - 2 * abs(i - 4); ++j)	//打印菱形
		{
			if (j % 2)
			{
				putchar(' ');
			}
			else
			{
				putchar('*');
			}
		}
		putchar('\n');	//换行
	}
	system("pause");
}