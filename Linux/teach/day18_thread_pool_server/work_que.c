#include "work_que.h"

void queInit(pQue_t pq,int capacity)
{
    bzero(pq,sizeof(Que_t));
    pq->queCapacity=capacity;
    pthread_mutex_init(&pq->mutex,NULL);
}

void queInsert(pQue_t pq,pNode_t pNew)
{
    if(NULL==pq->queHead)
    {
        pq->queHead=pNew;
        pq->queTail=pNew;
    }else
    {
        pq->queTail->pNext=pNew;
        pq->queTail=pNew;
    }
    pq->queSize++;
}

int queGet(pQue_t pq,pNode_t *pDel)
{
    if(NULL==pq->queHead)
    {
        return -1;
    }
    *pDel=pq->queHead;
    pq->queHead=pq->queHead->pNext;
    if(NULL==pq->queHead)
    {
        pq->queTail=NULL;
    }
    pq->queSize--;
    return 0;
}