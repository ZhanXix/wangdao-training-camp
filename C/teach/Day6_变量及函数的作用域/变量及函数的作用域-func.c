#include "变量及函数的作用域-func.h"

int k;//这里是借用其他文件的k
//规范写法如下,要加extern
extern int k;
int k2=0;
void print2()
{
	printf("k=%d\n", k);
	printf("k2=%d\n", k2);
}