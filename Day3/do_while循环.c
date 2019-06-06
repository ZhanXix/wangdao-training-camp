#include <stdio.h> 
#include <stdlib.h> 

//do_while循环
int main()
{
	int i = 1, sum = 0;
	do 
	{
		sum += i;
		i++;
	} while (i <= 100);//这里必须加分号
	printf("sum=%d\n", sum);
	system("pause");
}
