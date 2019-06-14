#include <stdio.h> 
#include <stdlib.h> 

#define N 8
int main() {
	int arr[N] = { 8,11,20,7,11,20,9,8 };
	int split;//所有的数与split按位与，真的放一堆，假的放一堆
	int result = 0, i;
	int find1 = 0, find2 = 0;
	for (i = 0; i < N; i++)
	{
		result ^= arr[i];
	}
	printf("result=%d\n", result);
	split = result & -result;//一个数和其负值按位与，得到最低位为1的对应的那个数
	for (i = 0; i < N; i++)
	{
		if (split & arr[i])
		{
			printf("heap1=%d\n", arr[i]);
			find1 ^= arr[i];
		}
		else
		{
			printf("heap2=%d\n", arr[i]);
			find2 ^= arr[i];
		}
	}
	printf("\nfind1=%d,efind2=%d\n", find1,find2);
	system("pause");
}
