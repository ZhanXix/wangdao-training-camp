#include "╤сап-squeue.h"

int main()
{
	SqQueue_t Q;
	Elemtype e;
	initQueue(&Q);
	enQueue(&Q, 10);
	enQueue(&Q, 5);
	deQueue(&Q, &e);
	system("pause");
}