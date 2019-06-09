/*
给定一个含有n个元素的整型数组，找出数组中的两个元素x和y使得abs(x - y)值最小
*/

#include <stdio.h>
#include <stdlib.h> 

//没想到优化思路，目前是思路是先排序，然后找到元素
int cmp(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}
int main()
{
	int* arr = NULL;
	int len = 0;
	do
	{
		//建立数组
		printf("输入整型数组的长度:\n");
		scanf("%d", &len);
		arr = (int*)malloc(len * sizeof(int));
		printf("给定一个%d个整型元素的数组a:\n", len);
		for (int i = 0; i < len; ++i)
		{
			scanf("%d", &arr[i]);
		}
		//排序
		qsort(arr, len, sizeof(int), cmp);
		//找到要求的两个元素x和y
		int result = abs(arr[0] - arr[1]);
		int x = arr[0];
		int y = arr[1];
		for (int i = 1; i < len-1; ++i)
		{
			if (abs(arr[i] - arr[i + 1]) < result)
			{
				result = abs(arr[i] - arr[i + 1]);
				x = arr[i];
				y = arr[i + 1];
			}
		}
		printf("找出数组中的两个元素%d和%d使得它们相减的绝对值最小，最小值为:%d\n", x,y,result);
		//释放空间
		free(arr);
		arr = NULL;
		rewind(stdin);
		printf("\n若要继续，输入y:");
	} while (getchar() == 'y');
	system("pause");
}