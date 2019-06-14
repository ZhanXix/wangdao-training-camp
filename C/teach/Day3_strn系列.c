#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

//strn系列
int main()
{
	char c[50];
	char d[50];
	while (gets(c) != NULL)
	{
		memset(d, 0, sizeof(d));	//*重要*内存设置，把从d开始往后的每一个字节（sizeof（d）大小）都设成0
		strncpy(d, c, 7);	//strncpy不会添结束符
		//如果c字符数小于7，后面用\0填补
		//strncpy也有可能访问越界
		puts(d);
		printf("cmpresult = %d\n", strncmp(d, "李宁", 2));	//只比较前2个字节
		strncat(d, "QWQ", 1);	//只复制"QWQ"的第1个字节
		puts(d);
	}
	system("pause");
}
