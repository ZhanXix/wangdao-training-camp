#include "����-sort.h"

int cmp(const void* left, const void* right)
{
	int* p1 = (int*)left;
	int* p2 = (int*)right;
	return *p1 - *p2;
}
int main()
{
	int i;
	//int arr[N];
	//N����ʱ������ջ�ռ䣬windows�µ���������ջ�ռ�ֻ��1M
	int* arr = (int*)malloc(N * sizeof(int));
	time_t start, end;
	srand(time(NULL));
	//time(NULL)���ؾ���1970.1.1������
	for (i = 0; i < N; i++)
	{
		arr[i] = rand() % R;
	}
	printf("rand %d complete.\n", N);
	//arrPrint(arr);	//N����ʱ�Ͳ����������ÿ������
	start = time(NULL);
	//arrSelect(arr);
	//arrInsert(arr);
	//arrShell(arr);
	//arrQuick(arr, 0, N-1);	//N����ʱ�ݹ���࣬������
	//qsort(arr, N, sizeof(int), cmp);	//qsort��ֱ���ȷ���ռ䣬�����������д�Ŀ��ŵ��������
	//arrHeap(arr);
	arrCount(arr);
	end = time(NULL);
	//arrPrint(arr);	//N����ʱ�Ͳ����������ÿ������
	printf("use time = %ds\n", end - start);
	system("pause");
}