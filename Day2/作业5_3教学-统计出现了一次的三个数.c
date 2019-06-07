/*
有103个整数，其中有50个数出现了两次，3个数出现了一次， 找出出现了一次的那3个数。
*/

#include <stdio.h> 
#include <stdlib.h> 

#define N 9
void findTwoNum(int* arr, int result, int first)
//修改5.2的函数
{
	int split;//所有的数与split按位与，真的放一堆，假的放一堆
	int i;
	int find1 = 0, find2 = 0;
	split = result & -result;//一个数和其负值按位与，得到最低位为1的对应的那个数
	for (i = 0; i < N; i++)
	{
		if (split & arr[i])
		{
			find1 ^= arr[i];
		}
		else
		{
			find2 ^= arr[i];
		}
	}
	if (split & first)
	{
		find1 ^= first;
	}
	else
	{
		find2 ^= first;
	}
	printf("find2=%d\nfind3=%d\n", find1, find2);
}
int main() {
	int arr[N] = { 8,11,20,7,11,20,9,8,5 };
	int heapResult1 = 0, heapResult2 = 0;//先分为2堆，一个数在一堆，两个数在另一堆
	int heapCount1 = 0, heapCount2 = 0;//分成两堆后两堆各自元素的数目
	int split = 1;
	int i, j;
	for (j = 0; j < 32; j++)
	{
		split = 1 << j;
		heapCount1 = heapCount2 = heapResult1 = heapResult2 = 0;
		for (i = 0; i < N; i++)
		{
			if (split & arr[i])
			{
				heapCount1++;
				heapResult1 ^= arr[i];
			}
			else
			{
				heapCount2++;
				heapResult2 ^= arr[i];
			}
		}
		if (heapCount1 % 2 == 0 && heapResult1 != 0)
		{
			printf("find1=%d\n", heapResult2);
			findTwoNum(arr, heapResult1, heapResult2);
			break;
		}
		if (heapCount2 % 2 == 0 && heapResult2 != 0)
		{
			printf("find1=%d\n", heapResult1);
			findTwoNum(arr, heapResult2, heapResult1);
			break;
		}
	}
	system("pause");
}
