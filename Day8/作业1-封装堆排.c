/*把堆排封装为像qsort一样的接口*/

#include <stdio.h>
#include <stdlib.h>

#define N 10	//排序数的多少
#define R 100	//排序数的大小范围：目前是0-99
#define SWAP(a,b) {int temp=a;a=b;b=temp;}	//交换

//输出数组
void printArr(int* a)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		printf("%3d", a[i]);
	}
	putchar('\n');
}

//辅助比较
int cmp(const void* a, const void* b)
{
	return *(int*)b - *(int*)a;	//当前：降序
}

//堆排序
void adjustHeap(int* a, int adjustNode, int arrLen, int (*cmp)(const void*, const void*))	//调整结点adjustNode的位置
{
	int father = adjustNode;
	int son = father * 2 + 1;
	while (son < arrLen)
	{
		if (son + 1 < arrLen)
		{
			if (cmp(&a[son] , &a[son + 1])<0)
			{
				++son;
			}
		}
		if (cmp(&a[son], &a[father]) > 0)
		{
			SWAP(a[son], a[father]);
			father = son;
			son = father * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int* a, int amount, int (*cmp)(const void*, const void*))
{
	int i;
	for (i = amount / 2 - 1; i >= 0; --i)
	{
		adjustHeap(a, i, amount, cmp);
	}//把整个数组调整为一个大根（小根）堆
	SWAP(a[0], a[amount - 1]);
	for (i = amount - 1; i > 1; --i)
	{
		adjustHeap(a, 0, i, cmp);
		SWAP(a[0], a[i - 1]);
	}
}

int main()
{
	int* a;
	int i;
	srand(time(NULL));
	a = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; ++i)
	{
		a[i] = rand() % R;
	}
	printf("已得到%d个随机数...\n", N);
	printArr(a);	//输出
	HeapSort(a, N, cmp);	//堆排序
	printf("------------------------------------\n");
	printArr(a);	//输出
	system("pause");
}