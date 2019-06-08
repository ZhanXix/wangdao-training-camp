/*
求三个有序数组的公共元素
*/

#include <stdio.h> 
#include <stdlib.h> 

void findsame(int* a1, int len1, int* a2, int len2, int* a3, int len3)
{
	int i = 0, j = 0, k = 0;
	int num;
	memset(a3, 0, len3 * sizeof(int));
	while (i < len1 && j < len2)
	{
		if (a1[i] == a2[j])
		{
			a3[k] = a1[i];
			k++;
			num = a1[i];
			if (k >= len3)
			{
				printf( "ERROR!\n" );
				break;
			}
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
}
int main()
{
	int a1[14] = { 1,2,2,3,4,5,5,5,8,9,11,13,14,18 };
	int a2[16] = { 2,3,5,6,7,7,8,9,10,12,12,13,13,14,18,19 };
	int a3[18] = { 1,1,1,2,2,4,5,6,7,7,8,9,10,14,14,17,18,20 };
	int num[20], same[20];
	findsame(a1, 14, a2, 16, num, 20);
	findsame(num, 20, a3, 18, same, 20);
	printf("三个有序数组的公共元素为\n");
	for (int i = 0; i < 20; ++i)
	{
		printf("%d ", same[i]);
		if (i < 19 && same[i] >= same[i + 1])
		{
			break;
		}
	}
	putchar('\n');
	system("pause");
}