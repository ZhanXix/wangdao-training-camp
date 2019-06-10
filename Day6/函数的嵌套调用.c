#include <stdio.h> 
#include <stdlib.h>
#include <setjmp.h>

void b(jmp_buf envbuf)
{
	printf("I am func b.\n");
	longjmp(envbuf,5);//�������Ĳ�������setjump�ķ���ֵ��������0
}

void a(jmp_buf envbuf)
{
	printf("Befor b, I am func a.\n");
	b(envbuf);
	printf("After b, I am func a.\n");
}

int main()
{
	jmp_buf envbuf;
	int ret;
	ret = setjmp(envbuf);//longjmp���غ�ret�Ͳ���0�ˣ���5��
	if (ret == 0) {
		a(envbuf);
	}
	return 0;
}