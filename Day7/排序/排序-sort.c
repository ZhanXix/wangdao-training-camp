#include "排序-sort.h"

//输出数组
void arrPrint(int* arr)
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%3d", arr[i]);
	}
	putchar('\n');
}

//选择排序
void arrSelect(int* arr)
{
	int i, j, maxPos;
	for (i = N; i > 1; i--)//外层控制无序数数目
	{
		maxPos = 0;
		for (j = 1; j < i; j++)
		{
			if (arr[j] > arr[maxPos])
			{
				maxPos = j;
			}
		}
		SWAP(arr[maxPos], arr[i - 1]);
	}
}

//插入排序
void arrInsert(int* arr)
{
	int i, j, insertValue;
	for (i = 1; i < N; i++)
	{
		insertValue = arr[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (insertValue < arr[j])
			{
				arr[j + 1] = arr[j];
			}
			else
			{
				break;	//找到插入位置
			}
		}
		arr[j + 1] = insertValue;
	}
}

//希尔排序
void arrShell(int* arr)
{
	int i, j, insertValue, gap;	//gap即步长
	for (gap = N >> 1; gap > 0; gap >>= 1)
	{
		for (i = gap; i < N; i++)
		{
			insertValue = arr[i];
			for (j = i - gap; j >= 0; j -= gap)
			{
				if (insertValue < arr[j])
				{
					arr[j + gap] = arr[j];
				}
				else
				{
					break;	//找到插入位置
				}
			}
			arr[j + gap] = insertValue;
		}
	}
}

//快速排序
int partition(int* arr, int left, int right)
{
	int i, k;
	for (i = left, k = left; i < right; i++)
	{
		if (arr[right] > arr[i])
		{
			SWAP(arr[i], arr[k]);
			k++;
		}
	}
	SWAP(arr[k], arr[right]);
	return k;
}
void arrQuick(int* arr, int left, int right)
{
	int pivot;
	if (left < right)
	{
		pivot = partition(arr, left, right);
		arrQuick(arr, left, pivot - 1);
		arrQuick(arr, pivot + 1, right);
	}
}

//堆排序
void adjustMaxHeap(int* arr, int adjustPos, int arrLen)
{
	int dad = adjustPos;
	int son = 2 * dad + 1;
	while (son < arrLen)
	{
		if (son + 1 < arrLen && arr[son] < arr[son + 1])
		{
			son++;
		}
		if (arr[dad] < arr[son])
		{
			SWAP(arr[dad], arr[son]);
			dad = son;
			son = 2 * dad + 1;	//这里需要注意，实际上调整是一个循环的过程
		}
		else {
			break;
		}
	}
}
void arrHeap(int* arr)
{
	int i;
	for (i = N / 2 - 1; i >= 0; i--)//调整为一个大根堆
	{
		adjustMaxHeap(arr, i, N);
	}
	SWAP(arr[0], arr[N - 1]);
	for (i = N - 1; i > 1; i--)
	{
		adjustMaxHeap(arr, 0, i);
		SWAP(arr[0], arr[i-1]);
	}
}

//计数排序
void arrCount(int* arr)
{
	int i, j, k;
	int count[R] = { 0 };//R值很大时，计数排序不合适
	for (i = 0; i < N; i++)
	{
		count[arr[i]]++;
	}
	k = 0;
	for (j = 0; j < R; j++)//要填入值的范围
	{
		for (i = 0; i < count[j]; i++)//要填入的值的数量
		{
			arr[k] = j;//填入相应排好的值
			k++;
		}
	}
}