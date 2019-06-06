#include <stdio.h> 
#include <stdlib.h> 

//一维数组
#define N 5
int main()
{
	int i = 10;
	int arr[N] = { 1,2,3,4,5 };//定义数组时进行初始化
	//要防止访问越界
	printf("i=%d\n", i);
	system("pause");
}
