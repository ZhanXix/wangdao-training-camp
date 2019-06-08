/*
求两个有序数组的公共元素
*/

#include <stdio.h> 
#include <stdlib.h> 

int main()
{
	int a1[] = { 1,2,2,3,4,5,5,5,8,9,11,13 };
	int a2[] = { 2,3,5,6,7,7,8,9,10,12,12,13,13,14 };
	int i = 0, j = 0;
	int num;
	printf("两个有序数组的公共元素为\n");
	while (i < sizeof(a1) / sizeof(int) && j < sizeof(a1) / sizeof(int))
	{
		if (a1[i] == a2[j])
		{
			num = a1[i];
			printf("%3d", num);
			while (a1[i] == num)
			{
				i++;
			}
			while (a1[j] == num)
			{
				j++;
			}
		}
		else if (a1[i] > a2[j])
		{
			j++;
		}
		else
		{
			i++;
		}
	}
	putchar('\n');
	system("pause");
}