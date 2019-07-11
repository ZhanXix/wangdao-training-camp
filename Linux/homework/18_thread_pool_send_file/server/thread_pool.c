#include "thread_pool.h"

int ThreadPool_Init(pThread_Pool_Info_t pThreadPool,char *ThreadNum,char *workQueueCapacity)
{
    //printf("线程池初始化开始\n");
    printf("线程数%d，最大队列长度%d\n",atoi(ThreadNum),atoi(workQueueCapacity));
    pthread_cond_init(&pThreadPool->cond,NULL);
    pThreadPool->threadNum=atoi(ThreadNum);
    pThreadPool->pthId=(pthread_t*)calloc(pThreadPool->threadNum,sizeof(pthread_t));
    WorkQueue_Init(&pThreadPool->pWorkQueue,atoi(workQueueCapacity));
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

void cleanup(void *p)
{
    pWork_Queue_t pW=(pWork_Queue_t)p;
    pthread_mutex_unlock(&pW->WorkQueuemutex);
}

void *Thread_Func(void *p)
{
    int ret;
    pThread_Pool_Info_t pT=(pThread_Pool_Info_t)p;
    pWork_Queue_t pW=pT->pWorkQueue;
    int clientFd;
    while(1)
    {
        //printf("线程开始加锁\n");
        pthread_mutex_lock(&pW->WorkQueuemutex);
        pthread_cleanup_push(cleanup,pW);
        if(pW->WorkQueueSize==0)
        {
            printf("线程开始等待>\n");
            pthread_cond_wait(&pT->cond,&pW->WorkQueuemutex);
        }
        printf("<线程开始工作\n");
        ret=WorkQueue_Get(&clientFd,pW);
        pthread_cleanup_pop(1);
        pthread_mutex_unlock(&pW->WorkQueuemutex);
        if(-1==ret)//未能成功取得队列结点
        {
            continue;
        }
        ret=Send_File(clientFd);
        if(0==ret)//文件传输完毕
        {
            printf("文件传输完毕!\n");
        }
        close(clientFd);
   }
   return NULL;
}