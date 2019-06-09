/*
有103个整数，其中有50个数出现了两次，3个数出现了一次， 找出出现了一次的那3个数。
*/

#include <stdio.h> 
#include <stdlib.h> 

int findTwo(int a[], int len, int heap1, int* find2, int* find3)
{
	int x = 0;
	for (int i = 0; i < len; ++i) {
		if (a[i] != heap1)
		{
			x ^= a[i];
		}
	}	//得到两个不相同的数的异或结果
	int y = x & -x;	//最低位为1的那个数
	//分成两堆，分别求两个数
	for (int i = 0; i < len; ++i) {
		if (a[i] ^ heap1) {	//确保a[i]不是第一个被找出的那个数
			if (a[i] & y) {
				*find2 ^= a[i];
			}
			else {
				*find3 ^= a[i];
			}
		}
	}
}
#define N 9
int main()
{
	int a[N] = { 2,3,2,4,4,5,6,7,6 };
	int x1 = 0, x2 = 0, x3 = 0;	//结果
	int heap1 = 0, heap2 = 0;	//两堆的结果
	int count1 = 0, count2 = 0;	//两堆的元素数目
	int split = 1;	//用于分割两堆
	for (int i = 0; i < 32; ++i)
	{
		split = split << 1;	//每次将split左移一位
		for (int j = 0; j < N; ++j)
		{
			if (a[j] & split)
			{
				heap1 ^= a[j];
				++count1;
			}
			else
			{
				heap2 ^= a[j];
				++count2;
			}
		}
		if (count2 % 2 && heap1 != 0)
		{
			x1 = heap2;
			findTwo(a, N, heap2, &x2, &x3);
			break;
		}
		else if (count1 % 2 && heap2 != 0)
		{
			x1 = heap1;
			findTwo(a, N, heap1, &x2, &x3);
			break;
		}
	}
	printf("出现了一次的那三个数为:%d %d %d\n", x1, x2, x3);
	system("pause");
}