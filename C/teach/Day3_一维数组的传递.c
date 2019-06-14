#include <stdio.h> 
#include <stdlib.h> 

//一维数组的传递
//数组名存的是数组的起始地址
//传递过去的是值，无法传递整个数组，所以需要设定传入长度arrLen
void print(int arr[],int arrLen)//函数是值传递
{
	int i;
	for (i = 0; i < arrLen; ++i)
	{
		printf("%3d", arr[i]);
	}
	printf("\n");
}
int main()
{
	int arr[5] = { 1,2,3,4,5 };
	print(arr, 5);
	system("pause");
}
