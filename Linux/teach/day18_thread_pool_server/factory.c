#include "factory.h"

void *threadFunc(void *p)
{
    pFactory_t pThreadInfo=(pFactory_t)p;
    pQue_t pq=&pThreadInfo->que;
    pNode_t pGet;
    int getTaskSucess;
    while(1)
    {
        pthread_mutex_lock(&pq->mutex);
        if(!pq->queSize)
        {
            pthread_cond_wait(&pThreadInfo->cond,&pq->mutex); 
        }
        getTaskSucess=queGet(pq,&pGet);//拿任务
        pthread_mutex_unlock(&pq->mutex);
        if(!getTaskSucess)
        {
            tranFile(pGet->newFd);
            free(pGet);
            pGet=NULL;
        }
    }
}

int factoryInit(pFactory_t p,int threadNum,int capacity)
{
    queInit(&p->que,capacity);
    pthread_cond_init(&p->cond,NULL);
    p->pthid=(pthread_t*)calloc(threadNum,sizeof(pthread_t));
    p->threadNum=threadNum;
    p->startFlag=0;
    return 0;
}

int factoryStart(pFactory_t p)
{
    if(!p->startFlag)
    {
        int i;
        for(i=0;i<p->threadNum;i++)
        {
            pthread_create(p->pthid+i,NULL,threadFunc,p);
        }
        p->startFlag=1;
    }
    return 0;
}