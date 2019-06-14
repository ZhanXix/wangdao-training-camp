#include "排序-sort.h"

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
	//N过大时不能用栈空间，windows下单个函数的栈空间只有1M
	int* arr = (int*)malloc(N * sizeof(int));
	time_t start, end;
	srand(time(NULL));
	//time(NULL)返回距离1970.1.1的秒数
	for (i = 0; i < N; i++)
	{
		arr[i] = rand() % R;
	}
	printf("rand %d complete.\n", N);
	//arrPrint(arr);	//N过大时就不合适再输出每个数了
	start = time(NULL);
	//arrSelect(arr);
	//arrInsert(arr);
	//arrShell(arr);
	//arrQuick(arr, 0, N-1);	//N过大时递归过多，造成溢出
	//qsort(arr, N, sizeof(int), cmp);	//qsort会直接先分配空间，不会造成我们写的快排的溢出问题
	//arrHeap(arr);
	arrCount(arr);
	end = time(NULL);
	//arrPrint(arr);	//N过大时就不合适再输出每个数了
	printf("use time = %ds\n", end - start);
	system("pause");
}