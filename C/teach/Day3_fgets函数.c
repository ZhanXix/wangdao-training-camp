#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

//fgets函数
//注意：fgets会把\n存入字符数组
int main()
{
	char c[10];
	size_t len;	//size_t用来代表字节数
	while (fgets(c, sizeof(c), stdin) != NULL)
	{
		c[strlen(c) - 1] = 0;	//去掉最后的\n，改成\0
		puts(c);
		len = strlen(c);	//理论上需要include<string.h>,但是VS2019似乎不用
		printf("%d\n", len);
	}
	system("pause");
}
