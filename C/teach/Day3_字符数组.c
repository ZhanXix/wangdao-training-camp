#include <stdio.h> 
#include <stdlib.h> 

//字符数组
void print(char c[]) 
{
	for (int i = 0; c[i] != 0; i++)
	{
		putchar(c[i]);
	}
	putchar('\n');
}
int main()
{
	//char c[6] = { 'A','B','C','D','E','F' };//最后没有'\0'，会出现问题
	char c[7] = "ABCDEF";
	char d[10];
	print(c);
	scanf("%s%s", c, d);//scanf会忽略空格和\n；scanf不能保证不越界，不安全
	printf("%s-%s\n", c, d);
	system("pause");
}
