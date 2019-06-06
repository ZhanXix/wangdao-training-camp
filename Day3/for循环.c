#include <stdio.h> 
#include <stdlib.h> 

//for循环
int main()
{
	int i, sum;
	for (i = 1, sum = 0; i <= 100; i++)
	{
		if (i % 2 == 1)
		{
			continue;//本次循环continue后面的语句不再执行
		}
		sum += i;//计算偶数和
	}
	printf("sum=%d\n", sum);
	system("pause");
}
