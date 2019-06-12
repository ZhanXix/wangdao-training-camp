/*ѡ�����򡢲������򡢿������򡢶����򡢼������򡢹鲢����*/

#include <stdio.h>
#include <stdlib.h>

#define N 10	//�������Ķ���
#define R 100	//�������Ĵ�С��Χ��Ŀǰ��0-99
#define SWAP(a,b) {int temp=a;a=b;b=temp;}	//����

//�������
void printArr(int* a)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		printf("%3d", a[i]);
	}
	putchar('\n');
}

//ѡ������
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

//��������
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

//��������
int FindSplit(int* a, int left, int right)	//�ҵ��ָ��
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

//������
void adjustHeap(int* a, int adjustNode, int arrLen)	//�������adjustNode��λ��
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
	}//�������������Ϊһ�������
	SWAP(a[0], a[N - 1]);
	for (i = N - 1; i > 1; --i)
	{
		adjustHeap(a, 0, i);
		SWAP(a[0], a[i - 1]);
	}
}

//��������
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

//�鲢����
void mergeArr(int* a, int left, int mid, int right)	//�鲢��������
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

//qsort�õĸ�������
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
	printf("�ѵõ�%d�������...\n", N);
	start = time(NULL);
	printArr(a);	//���
	//SelectSort(a);	//ѡ������
	//InsertSort(a);	//��������
	//QuickSort(a, 0, N - 1);	//��������
	//HeapSort(a);	//������
	//CountSort(a);	//��������
	MergeSort(a, 0, N - 1); //�鲢����
	//qsort(a, N, sizeof(int), cmp);	//qsort
	end = time(NULL);
	printf("------------------------------------\n");
	printf("������ϣ���ʱ %d ��\n", end - start);
	printArr(a);	//���
	system("pause");
}