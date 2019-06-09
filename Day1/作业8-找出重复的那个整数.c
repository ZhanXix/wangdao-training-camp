/*
给定含有1001个元素的数组，其中存放了1 - 1000之内的整数，只有一个整数是重复的，请找出这个数
提示： A1 + … + A1001 –(1 + … + 1000)
*/

#include <stdio.h>
#include <stdlib.h> 

int main()
{
	int arr[1001];
	int result = 0;
	for (int i = 0; i < 1001; ++i)
	{//建立数组
		if (i == 555)
		{
			arr[i] = 999;	//重复的数
		}
		else if (i < 555)
		{
			arr[i] = i + 1;
		}
		else
		{
			arr[i] = i;
		}
	}
	//找出重复的数
	for (int i = 0; i < 1001; ++i) {
		result = result + arr[i] - i;
	}
	printf("数组中重复的那个数的为:%d\n",  result);
	system("pause");
}
