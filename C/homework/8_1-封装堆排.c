/*�Ѷ��ŷ�װΪ��qsortһ���Ľӿ�*/

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

//�����Ƚ�
int cmp(const void* a, const void* b)
{
	return *(int*)b - *(int*)a;	//��ǰ������
}

//������
void adjustHeap(int* a, int adjustNode, int arrLen, int (*cmp)(const void*, const void*))	//�������adjustNode��λ��
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
	}//�������������Ϊһ�������С������
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
	printf("�ѵõ�%d�������...\n", N);
	printArr(a);	//���
	HeapSort(a, N, cmp);	//������
	printf("------------------------------------\n");
	printArr(a);	//���
	system("pause");
}