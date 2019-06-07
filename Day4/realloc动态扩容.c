#include <stdio.h>
#include <stdlib.h>

//realloc动态扩容
//真正的动态数组
#define CAPACITY 10
int main()
{
	char* p = (char*)malloc(CAPACITY);
	char c;
	int i = 0,cap=CAPACITY;
	while (scanf("%c", &c) != EOF)
	{
		if (i == cap - 1)
		{
			cap *= 2;
			p = (char*)realloc(p, cap);
		}
		p[i] = c;
		++i;
	}
	p[i] = 0;
	puts(p);
	free(p);
	system("pause");
}
