#include "fd_work_queue.h"

int WorkQueue_Init(pWork_Queue_t* ppWorkQueue,int workQueueCapacity)
{
    //printf("工作队列初始化开始\n");
    pWork_Queue_t pWorkQueue=(pWork_Queue_t)calloc(1,sizeof(Work_Queue_t));
    pWorkQueue->pWorkQueueHead=NULL;;
    pWorkQueue->pWorkQueueTail=NULL;
    pWorkQueue->WorkQueueCapacity=workQueueCapacity;
    pthread_mutex_init(&pWorkQueue->WorkQueuemutex,NULL);
    pWorkQueue->WorkQueueSize=0;
    *ppWorkQueue=pWorkQueue;
    //printf("工作队列初始化完毕\n");
    return 0;
}

int WorkQueue_Get(int *pclientFd,pWork_Queue_t pW)
{
    if(0==pW->WorkQueueSize)
    {
        return -1;
    }
    pFd_Work_Node_t pCur=pW->pWorkQueueHead;
    pW->pWorkQueueHead=pCur->pNext;
    if(1==pW->WorkQueueSize)
    {
        pW->pWorkQueueTail=NULL;
    }
    *pclientFd=pCur->clientFd;
    free(pCur);
    pW->WorkQueueSize--;
    //printf("已取下结点，当前工作队列长度：%d\n",pW->WorkQueueSize);
    return 0;
}

int WorkQueue_Add(int newFd,pWork_Queue_t pW)
{
    if(pW->WorkQueueSize==pW->WorkQueueCapacity)
    {
        printf("工作队列已满\n");
        return -1;
    }
    pFd_Work_Node_t pNew;
    pNew=(pFd_Work_Node_t)calloc(1,sizeof(Fd_Work_Node_t));
    pNew->clientFd=newFd;
    if(NULL==pW->pWorkQueueHead)
    {
        //printf("工作队列为空，插入第一个结点\n");
        pW->pWorkQueueHead=pNew;
        pW->pWorkQueueTail=pNew;
    }else{
        pW->pWorkQueueTail->pNext=pNew;
        pW->pWorkQueueTail=pNew;
    }
    pW->WorkQueueSize++;
    //printf("已添加结点，当前工作队列长度：%d\n",pW->WorkQueueSize);
    return 0;
}

