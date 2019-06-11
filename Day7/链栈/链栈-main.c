#include "Á´Õ»-stack.h"

int main()
{
	Stack_t stack;
	int ret;
	initStack(&stack);
	push(&stack, 10);
	push(&stack, 5);
	pop(&stack);
	ret = top(&stack);
	system("pause");
}