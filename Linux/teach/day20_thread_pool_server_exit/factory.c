#include "factory.h"

int factoryInit(pFactory_t pf,int threadNum,int capacity)
{
    queInit(&pf->que,capacity);
    pthread_cond_init(&pf->cond,NULL);
    pf->pthid=(pthread_t*)calloc(threadNum,sizeof(pthread_t));
    pf->threadNum=threadNum;
    pf->startFlag=0;
    return 0;
}
void cleanup(void *p)
{
    pQue_t pq=(pQue_t)p;
    pthread_mutex_unlock(&pq->mutex);
}
//子线程函数
void *threadFunc(void *p)
{
    pFactory_t pf=(pFactory_t)p;
    pQue_t pq=&pf->que;
    pNode_t pCur;
    int getSuccess;
    while(1)
    {
        pthread_mutex_lock(&pq->mutex);
        /* pthread_cleanup_push(cleanup,pq); */
        if(!pq->size)
        {
            pthread_cond_wait(&pf->cond,&pq->mutex);//队列为空，就睡觉
        }
        getSuccess=queGet(pq,&pCur);//从队列拿任务
        /* pthread_cleanup_pop(1); */
        if(!getSuccess)
        {
            tranFile(pCur->newFd);//发文件
            close(pCur->newFd);
            free(pCur);
        }
        pCur=NULL;
    }
}
int factoryStart(pFactory_t pf)
{
    int i;
    if(!pf->startFlag)
    {
        for(i=0;i<pf->threadNum;i++)
        {
            pthread_create(pf->pthid+i,NULL,threadFunc,pf);
        }
        pf->startFlag=1;
    }
    return 0;
}

