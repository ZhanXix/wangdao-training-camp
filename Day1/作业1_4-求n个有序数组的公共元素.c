/*
求n个有序数组的公共元素
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
				printf("ERROR!\n");
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
#define M 10
#define N 5
int main()
{
	int arr[N][M] = { {0,1,2,3,4,5,6,7,8,9},{1,1,2,2,3,4,5,6,7,9},{1,2,3,3,4,4,4,6,6,7},{1,2,3,4,6,7,8,9,10,10},{1,1,2,2,3,3,4,4,6,8} };
	int num[M], same[M];
	findsame(arr[0], M, arr[1], M, num, M);
	for (int i = 1; i < N; ++i)
	{
		findsame(arr[i], M, num, M, same, M);
	}
	printf("%d个有序数组的公共元素为\n",N);
	for (int i = 0; i < M; ++i)
	{
		printf("%d ", same[i]);
		if (i < M - 1 && same[i] >= same[i + 1])
		{
			break;
		}
	}
	putchar('\n');
	system("pause");
}