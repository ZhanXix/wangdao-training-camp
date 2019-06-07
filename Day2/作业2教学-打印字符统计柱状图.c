#include <stdio.h> 
#include <stdlib.h> 

//增量编写法
int main()
{
	char c;
	int arr[3] = { 0 };
	int temp;
	char* p[3] = { "alp","num","oth" };
	char* pTemp;
	while (scanf("%c", &c) != EOF)
	{
		if (c > 'A' && c <= 'Z' || c >= 'a' && c <= 'z')
		{
			arr[0]++;
		}
		else if (c >= '0' && c <= '9')
		{
			arr[1]++;
		}
		else if (c != '\n')
		{
			arr[2]++;
		}
	}
	printf("alp=%d,num=%d,oth=%d\n", arr[0], arr[1], arr[2]);
	//排序时，同步交换
	for (int i = 3; i > 1; i--)//无序数的数目
	{
		for (int j = 0; j < i - 1; j++)//内层控制比较
		{
			if (arr[j] < arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				pTemp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = pTemp;
			}
		}
	}
	for (int i = 0; i <= arr[0]; ++i)
	{
		if (i == 0)
		{
			printf("%3d  ", arr[0]);
		}
		else
		{
			printf("*****");
		}
		if (i == arr[0] - arr[1])
		{
			printf(" %3d  ", arr[1]);
		}
		else if (i > arr[0] - arr[1])
		{
			printf(" *****");
		}
		if (i == arr[0] - arr[2])
		{
			printf(" %3d  ", arr[2]);
		}
		else if (i > arr[0] - arr[2])
		{
			printf(" *****");
		}
		printf("\n");
	}
	printf("%4s  %4s  %4s\n", p[0], p[1], p[2]);
	system("pause");
}
