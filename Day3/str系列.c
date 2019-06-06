#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

//str系列
//需#include <string.h>
//strcpy会发生访问越界
void myStrcpy(char to[], char from[])
{
	int i = 0;
	while (from[i])
	{
		to[i] = from[i];
		i++;
	}
	to[i] = from[i];	//把'\0'放进去
}
int main()
{
	char c[50] = "hello";
	char d[50];
	//strcpy(d, c);
	myStrcpy(d, c);
	puts(d);
	printf("compare result = %d\n", strcmp(d, "how"));	//strcmp按照ASCII码值对比
	strcat(c, "xiongda");
	puts(c);
	system("pause");
}
