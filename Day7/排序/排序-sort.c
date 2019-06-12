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
void arrQuick(int* arr,int left,int right)
{
	int pivot;
	if (left < right)
	{
		pivot = partition(arr, left, right);
		arrQuick(arr, left, pivot - 1);
		arrQuick(arr, pivot + 1, right);
	}
}