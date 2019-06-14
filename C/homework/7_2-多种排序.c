/*选择排序、插入排序、快速排序、堆排序、计数排序、归并排序*/

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

//选择排序
void SelectSort(int* a)
{
	int i, j;
	int max;
	for (i = N; i > 1; --i)
	{
		max = 0;
		for (j = 1; j < i; ++j)
		{
			if (a[j] > a[max])
			{
				max = j;
			}
		}
		SWAP(a[i - 1], a[max]);
	}
}

//插入排序
void InsertSort(int* a)
{
	int i, j;
	int num;
	for (i = 1; i < N; ++i)
	{
		num = a[i];
		for (j = i - 1; j >= 0; --j)
		{
			if (a[j] > num)
			{
				a[j + 1] = a[j];
			}
			else
			{
				a[j + 1] = num;
				break;
			}
		}
		if (-1 == j)
		{
			a[0] = num;
		}
	}
}

//快速排序
int FindSplit(int* a, int left, int right)	//找到分割点
{
	int i, j;
	for (i = left, j = left; i < right; ++i)
	{
		if (a[i] < a[right])
		{
			SWAP(a[i], a[j]);
			++j;
		}
	}
	SWAP(a[right], a[j])
		return j;
}
void QuickSort(int* a, int left, int right)
{
	int split;
	if (right > left)
	{
		split = FindSplit(a, left, right);
		QuickSort(a, left, split - 1);
		QuickSort(a, split + 1, right);
	}
}

//堆排序
void adjustHeap(int* a, int adjustNode, int arrLen)	//调整结点adjustNode的位置
{
	int father = adjustNode;
	int son = father * 2 + 1;
	while (son < arrLen)
	{
		if (son + 1 < arrLen)
		{
			if (a[son] < a[son + 1])
			{
				++son;
			}
		}
		if (a[son] > a[father])
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
void HeapSort(int* a)
{
	int i;
	for (i = N / 2 - 1; i >= 0; --i)
	{
		adjustHeap(a, i, N);
	}//把整个数组调整为一个大根堆
	SWAP(a[0], a[N - 1]);
	for (i = N - 1; i > 1; --i)
	{
		adjustHeap(a, 0, i);
		SWAP(a[0], a[i - 1]);
	}
}

//计数排序
void CountSort(int* a)
{
	int count[R] = { 0 };
	int i, j;
	for (i = 0; i < N; ++i)
	{
		++count[a[i]];
	}
	j = 0;
	for (i = 0; i < R; ++i)
	{
		while (count[i])
		{
			a[j] = i;
			++j;
			--count[i];
		}
	}
}

//归并排序
void mergeArr(int* a, int left, int mid, int right)	//归并有序数组
{
	int i, j, k;
	int* b;
	b = (int*)malloc((right - left + 1) * sizeof(int));
	for (i = left; i <= right; ++i)
	{
		b[i - left] = a[i];
	}
	i = left;
	for (j = 0, k = mid - left + 1; j <= mid - left && k <= right - left;)
	{
		if (b[j] > b[k])
		{
			a[i++] = b[k++];
		}
		else
		{
			a[i++] = b[j++];
		}
	}
	while (j <= mid - left)
	{
		a[i++] = b[j++];
	}
	while (k <= right - left)
	{
		a[i++] = b[k++];
	}
	free(b);
	b = NULL;
}
void MergeSort(int* a, int left, int right)
{
	int mid;
	if (right > left)
	{
		mid = (right + left) / 2;
		MergeSort(a, left, mid);
		MergeSort(a, mid + 1, right);
		mergeArr(a, left, mid, right);
	}
}

//qsort用的辅助函数
int cmp(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

int main()
{
	int* a;
	int i;
	time_t start, end;
	srand(time(NULL));
	a = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; ++i)
	{
		a[i] = rand() % R;
	}
	printf("已得到%d个随机数...\n", N);
	start = time(NULL);
	printArr(a);	//输出
	//SelectSort(a);	//选择排序
	//InsertSort(a);	//插入排序
	//QuickSort(a, 0, N - 1);	//快速排序
	//HeapSort(a);	//堆排序
	//CountSort(a);	//计数排序
	MergeSort(a, 0, N - 1); //归并排序
	//qsort(a, N, sizeof(int), cmp);	//qsort
	end = time(NULL);
	printf("------------------------------------\n");
	printf("排序完毕，用时 %d 秒\n", end - start);
	printArr(a);	//输出
	system("pause");
}