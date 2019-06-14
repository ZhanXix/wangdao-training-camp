#include <stdio.h> 
#include <stdlib.h> 

//while循环
int main()
{
	int i = 1, sum = 0;
	while (i <= 100)
	{
		sum += i;
		++i;
	}
	printf("sum=%d\n", sum);
	system("pause");
}
