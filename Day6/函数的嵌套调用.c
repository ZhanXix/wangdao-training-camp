#include <stdio.h> 
#include <stdlib.h>
#include <setjmp.h>

jmp_buf envbuf;
void b()
{
	printf("I am func b.\n");
	longjmp(envbuf,5);//�������Ĳ�������setjump�ķ���ֵ��������0
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
	ret = setjmp(envbuf);//longjmp���غ�ret�Ͳ���0�ˣ���5��
	if (ret == 0) {
		a();
	}
	return 0;
}