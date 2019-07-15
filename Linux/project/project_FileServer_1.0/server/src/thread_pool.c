#include "thread_pool.h"

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
