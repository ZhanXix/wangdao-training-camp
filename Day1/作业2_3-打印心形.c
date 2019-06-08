/*
打印如下图形：
   * *       * *
  * * *     * * *
 * * * *   * * * *
* * * * * * * * * *
 * * * * * * * * *
  * * * * * * * *
   * * * * * * *
	* * * * * *
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
	int i, j;
	for (i = 0; i < 13; ++i)	//行数
	{
		for (j = 0; j < abs(i - 3); ++j) //打印*前的空格
		{
			putchar(' ');
		}
		for (j = 0; j < 19 - 2 * abs(i - 3); ++j)	//打印心形
		{
			if (j % 2 || (i < 3 && abs(6 + i - j) < 3 - i))
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