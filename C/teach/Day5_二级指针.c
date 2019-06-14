#include <stdio.h>
#include <stdlib.h>

//二级指针
void change(int** pa, int* pb)
{
	*pa = pb;
}//在子函数内需要修改主函数内某个一级指针的值，需要二级指针
int main() {
	int i = 10, j = 5;
	int* pi, * pj;
	pi = &i;
	pj = &j;
	printf("i=%d,j=%d,*pi=%d,*pj=%d\n", i, j, *pi, *pj);//10,5,10,5
	change(&pi, pj);
	printf("i=%d,j=%d,*pi=%d,*pj=%d\n", i, j, *pi, *pj);//10,5,5,5
	system("pause");
}
