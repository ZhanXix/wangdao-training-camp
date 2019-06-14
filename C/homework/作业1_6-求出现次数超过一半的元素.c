/*
给定一个n个整型元素的数组a，其中有一个元素出现次数超过n / 2，求这个元素。
(xz注：这个元素一定存在)
*/

#include <stdio.h>
#include <stdlib.h> 

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
		printf("给定一个%d个整型元素的数组a，其中有一个元素出现次数超过一半:\n", len);
		for (int i = 0; i < len; ++i)
		{
			scanf("%d", &arr[i]);
		}
		//计算出现次数超过一半的元素
		int count = 1;	//计数器
		int lastNum = arr[0];	//上一个处理的元素
		for (int i = 1; i < len; ++i) {
			if (arr[i] == lastNum)
			{
				++count;
			}
			else
			{
				--count;
				if (count < 0)
				{
					lastNum = arr[i];
					count = 1;
				}
			}
		}
		printf("出现次数超过一半的元素为 %d\n", lastNum);
		//释放空间
		free(arr);
		arr = NULL;
		rewind(stdin);
		printf("\n若要继续，输入y:");
	} while (getchar() == 'y');
	system("pause");
}

//教学：可以使用计数排序