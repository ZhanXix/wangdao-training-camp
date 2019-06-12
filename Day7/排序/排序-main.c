#include "ÅÅĞò-sort.h"

int cmp(const void* left, const void* right)
{
	int* p1 = (int*)left;
	int* p2 = (int*)right;
	return *p1 - *p2;
}
int main()
{
	int i;
	int arr[N];
	time_t start, end;
	srand(time(NULL));
	//time(NULL)·µ»Ø¾àÀë1970.1.1µÄÃëÊı
	for (i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100;
	}
	arrPrint(arr);
	start = time(NULL);
	//arrSelect(arr);
	//arrInsert(arr);
	//arrShell(arr);
	//arrQuick(arr, 0, N-1);
	arrHeap(arr);
	//qsort(arr, N, sizeof(int), cmp);
	end = time(NULL);
	arrPrint(arr);
	printf("use time = %ds\n", end - start);
	system("pause");
}