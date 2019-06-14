#include <stdio.h>
#include <stdlib.h>

//栈空间与堆空间的差异
char* printStack()
{
	char c[] = "I am printStack";
	puts(c);
	return c;
}//函数执行完毕，栈空间释放
char* printMalloc()
{
	char* p = (char*)malloc(20);
	strcpy(p, "I am printStack");
	puts(p);
	return p;
}
int main()
{
	char* p;
	p = printStack();
	puts(p);	//打印会乱码，因为退出函数printStack之后会弹出栈
	//puts函数会占用刚刚printStack内c[]所在的地址空间
	p = printMalloc();
	puts(p);	//打印无异常
	free(p);
	p = NULL;
	system("pause");
}
