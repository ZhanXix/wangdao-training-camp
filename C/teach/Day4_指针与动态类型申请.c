#include <stdio.h>
#include <stdlib.h>

//指针与动态类型申请
int main()
{
	int needSize;
	char* pStart;
	scanf("%d,", &needSize);
	pStart = (char*)malloc(needSize);	//malloc返回void*，需要强转类型
	//申请后必须释放！否则会造成内存泄漏
	strcpy(pStart, "hello");
	puts(pStart);
	free(pStart);	//必须free申请的首地址，不能偏移
	//free后pStart的值不会变
	pStart = NULL;
	//free后指针若不置成NULL，就会成为野指针
	system("pause");
}
