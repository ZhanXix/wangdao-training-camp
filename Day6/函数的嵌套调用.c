#include <stdio.h> 
#include <stdlib.h>
#include <setjmp.h>

jmp_buf envbuf;
void b()
{
	printf("I am func b.\n");
	longjmp(envbuf,5);//这个后面的参数代表setjump的返回值，不能填0
}

void a()
{
	printf("Befor b, I am func a.\n");
	b();
	printf("After b, I am func a.\n");
}

int main()
{
	int ret;
	ret = setjmp(envbuf);//longjmp跳回后ret就不是0了（是5）
	if (ret == 0) {
		a();
	}
	return 0;
}