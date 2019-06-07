#include <stdio.h>
#include <stdlib.h>

//指针的传递
void change(int *j)
//C语言函数调用是值传递
{
	*j = *j / 2;
}
int main()
{
	int i = 10;
	printf("before change i = %d\n", i);
	change(&i);
	printf("after change i = %d\n", i);
	system("pause");
}
