/*
��ӡ����ͼ�Σ�
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
	for (int i = 0; i < 9; ++i)	//����
	{
		for (int j = 0; j < abs(i - 4); ++j) //��ӡ*ǰ�Ŀո�
		{
			putchar(' ');
		}
		for (int j = 0; j < 9 - 2 * abs(i - 4); ++j)	//��ӡ����
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
		putchar('\n');	//����
	}
	system("pause");
}