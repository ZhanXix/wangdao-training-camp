#include <stdio.h> 
#include <stdlib.h> 

//二维数组
void print(int arr[][4], int row)//arr[][4]必需写清楚列数
//如果这里是arr[][3]，那么也可以，不过会变成每行3个输出，注意此时下面函数调用时row值要输4
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < sizeof(arr[0]) / sizeof(int); j++)
		{
			printf("%3d", arr[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	int a[3][4] = { 1,3,5,7,2,4,6,8,9,11,13,15 };
	//{{1,3,5,7},{2,4,6,8},{9,11,13,15}}
	int b[3][4] = { {1},{5},{6,9} };
	print(a, 3);
	system("pause");
}
