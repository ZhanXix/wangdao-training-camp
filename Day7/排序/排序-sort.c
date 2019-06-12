#include "����-sort.h"

//�������
void arrPrint(int* arr)
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%3d", arr[i]);
	}
	putchar('\n');
}

//ѡ������
void arrSelect(int* arr)
{
	int i, j, maxPos;
	for (i = N; i > 1; i--)//��������������Ŀ
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

//��������
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
				break;	//�ҵ�����λ��
			}
		}
		arr[j + 1] = insertValue;
	}
}

//ϣ������
void arrShell(int* arr)
{
	int i, j, insertValue, gap;	//gap������
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
					break;	//�ҵ�����λ��
				}
			}
			arr[j + gap] = insertValue;
		}
	}
}

//��������
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

//������
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
			son = 2 * dad + 1;	//������Ҫע�⣬ʵ���ϵ�����һ��ѭ���Ĺ���
		}
		else {
			break;
		}
	}
}
void arrHeap(int* arr)
{
	int i;
	for (i = N / 2 - 1; i >= 0; i--)//����Ϊһ�������
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

//��������
void arrCount(int* arr)
{
	int i, j, k;
	int count[R] = { 0 };//Rֵ�ܴ�ʱ���������򲻺���
	for (i = 0; i < N; i++)
	{
		count[arr[i]]++;
	}
	k = 0;
	for (j = 0; j < R; j++)//Ҫ����ֵ�ķ�Χ
	{
		for (i = 0; i < count[j]; i++)//Ҫ�����ֵ������
		{
			arr[k] = j;//������Ӧ�źõ�ֵ
			k++;
		}
	}
}