#include <stdio.h>
#include <stdlib.h>

//指针与一维字符数组
void change(char* p)
{
	*p = 'H';
	p[1] = 'E';
	*(p + 2) = 'L';
}
int main()
{
	char c[10] = "hello";
	change(c);
	puts(c);
	system("pause");
}
