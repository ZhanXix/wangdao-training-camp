#include "../include/thread_pool.h"

int ThreadPool_Init(pThread_Pool_Info_t pThreadPool,int ThreadNum)
{
    //printf("线程池初始化开始\n");
    printf("线程数%d，最大队列长度%d\n",ThreadNum,ThreadNum*2);
    pthread_cond_init(&pThreadPool->cond,NULL);
    pThreadPool->threadNum=ThreadNum;
    pThreadPool->pthId=(pthread_t*)calloc(pThreadPool->threadNum,sizeof(pthread_t));
    WorkQueue_Init(&pThreadPool->pWorkQueue,ThreadNum*2);
    pThreadPool->WorkFlag=0;
    //printf("线程池初始化完毕\n");
    return 0;
}

int ThreadPool_Start(pThread_Pool_Info_t pThreadPool)
{
    if(0==pThreadPool->WorkFlag)
    {
        int i;
        for(i=0;i<pThreadPool->threadNum;i++)
        {
            pthread_create(&(pThreadPool->pthId[i]),NULL,Thread_Func,pThreadPool);
            printf("创建线程%ld\n",pThreadPool->pthId[i]);
        }
        pThreadPool->WorkFlag=1;
    }
    return 0;
}

//*********************************************
//原fd_work_queue.c

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


