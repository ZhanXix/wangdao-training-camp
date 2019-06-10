//函数声明-定义-调用-func.c
#include "函数声明-定义-调用-func.h"

void printMessage()
{
	int ret;
	printf("How do you do\n");
	ret = printStar(5);

}
int printStar(int i)//函数定义
{
	printf("*****************************\n");
	return i+3;
}