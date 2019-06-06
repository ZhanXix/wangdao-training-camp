#include <stdio.h> 
#include <stdlib.h> 

//goto无条件跳转
int main()
{
	int i = 1, sum = 0;
lable://标签符合变量命名规范
	sum += i;
	++i;
	if (i <= 100)
	{
		goto lable;
	}
	printf("sum=%d\n", sum);
	system("pause");
}
