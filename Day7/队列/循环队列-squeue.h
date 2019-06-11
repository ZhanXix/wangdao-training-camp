#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 5
typedef int ElemType;
typedef struct{
	ElemType data[MaxSize];
	int front,rear;
}SqQueue_t;

void initQueue(SqQueue_t*);
void enQueue(SqQueue_t*,ElemType);
void deQueue(SqQueue_t*,ElemType*);

