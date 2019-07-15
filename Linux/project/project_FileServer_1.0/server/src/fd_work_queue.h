#ifndef FD_WORK_QUEUE_H
#define FD_WORK_QUEUE_H

#include "head.h"

typedef struct fd_work_node
{
    int clientFd;
    struct fd_work_node* pNext;
}Fd_Work_Node_t,*pFd_Work_Node_t;

typedef struct work_queue
{
    pFd_Work_Node_t pWorkQueueHead,pWorkQueueTail;
    pthread_mutex_t WorkQueuemutex;
    int WorkQueueSize;
    int WorkQueueCapacity;
}Work_Queue_t,*pWork_Queue_t;

int WorkQueue_Init(pWork_Queue_t* ppWorkQueue,int workQueueCapacity);
int WorkQueue_Get(int *pclientFd,pWork_Queue_t pW);
int WorkQueue_Add(int newFd,pWork_Queue_t pW);

#endif // !FD_WORK_QUEUE_H












