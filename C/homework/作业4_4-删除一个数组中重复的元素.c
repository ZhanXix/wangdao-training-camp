/*
4.删除一个数组中重复的元素。例如 1,2,2,2,3,3,3,4,4,5,5,5,6,6,6 -> 1,2,3,4,5,6
(假设重复数字均相邻)
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int* arr;
	int lastNum, count, len;
	printf("输入需要处理的数组长度：\n");
	while (scanf("%d", &len)!=EOF) {
		arr = (int*)malloc(4*len);
		printf("输入需要处理的数组：\n");
		for (int i = 0; i < len; ++i) {
			scanf("%d", arr+i);
		}
		lastNum = arr[0];//上一个处理的数字
		count = 0;//当前需要移位的数目
		for (int i = 1; i < len; ++i)
		{
			if (arr[i] == lastNum)
			{
				count++;
			}
			else
			{
				arr[i - count] = arr[i];
				lastNum = arr[i];
			}
		}
		len -= count;
		arr = (int*)realloc(arr,4*len);//缩小数组长度
		printf("处理结果：");
		for (int i = 0; i < len; ++i) {
			printf("%d ", *(arr + i));
		}
		free(arr);
		arr = NULL;
		printf("\n\n输入需要处理的数组长度(0表示结束处理)：\n");
	}
	system("pause");
}