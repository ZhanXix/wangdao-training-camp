/*
求数组的最大值和次大值
*/


#include <stdio.h> 
#include <stdlib.h> 

void find1and2big(int arr[], int size, int* big1, int* big2)
{
	if (size > 1)
	{
		if (arr[0]>arr[1])
		{
			*big1 = arr[0];
			*big2 = arr[1];
		}
		else
		{
			*big1 = arr[1];
			*big2 = arr[0];
		}
		for (int i = 2; i < size; i++)
		{
			if (arr[i]>*big1)
			{
				*big2 = *big1;
				*big1 = arr[i];
			}
			else if (arr[i]>*big2)
			{
				*big2 = arr[i];
			}
		}
	}
}
#define N 5
int main()
{
	int arr[N] = { 0 };
	int big1 = 0, big2 = 0;
	do {
		printf("输入%d个整数组成数组:\n", N);
		for (int i = 0; i < N; ++i)
		{
			scanf("%d", &arr[i]);
		}
		find1and2big(arr, N,&big1,&big2);
		printf("MAX: %d\n", big1);
		printf("secondMAX: %d\n", big2);
		rewind(stdin);
		printf("\n若要继续，输入y:");
	} while (getchar() == 'y');
	system("pause");
}