/*
��ӡ����ͼ�Σ�
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
	for (i = 0; i < 13; ++i)	//����
	{
		for (j = 0; j < abs(i - 3); ++j) //��ӡ*ǰ�Ŀո�
		{
			putchar(' ');
		}
		for (j = 0; j < 19 - 2 * abs(i - 3); ++j)	//��ӡ����
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
		putchar('\n');	//����
	}
	system("pause");
}