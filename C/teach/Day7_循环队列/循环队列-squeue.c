#include "Ñ­»·¶ÓÁÐ-squeue.h"

void initQueue(SqQueue_t* queue)
{
	queue->front=queue->rear=0;
}
void enQueue(SqQueue_t* queue,ElemType x)
{
	if((queue->rear+1)%MaxSize==queue->front)
	{
		printf("queue is full\n");
		return;
	}
	queue->data[queue->rear]=x;
	queue->rear=(queue->rear+1)%MaxSize;
}
void deQueue(SqQueue_t* queue,ElemType *x)
{
	if(queue->front==queue->rear)
	{
		printf("queue is empty\n");
		return;
	}
	*x=queue->data[queue->front];
	queue->front=(queue->front+1)%MaxSize;
}