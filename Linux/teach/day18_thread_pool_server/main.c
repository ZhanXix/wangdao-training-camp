#include "factory.h"

int main(int argc,char *argv[])
{
    if(argc!=5)
    {
        printf("./thread_pool_server IP PORT THREAD_NUM CAPACITY\n");
        return -1;
    }
    Factory_t threadInfo;
    int threadNum=atoi(argv[3]);
    int capacity=atoi(argv[4]);
    factoryInit(&threadInfo,threadNum,capacity);
    factoryStart(&threadInfo);      
    int socketFd;
    tcpInit(&socketFd,argv[1],argv[2]);
    int newFd;
    pQue_t pq=&threadInfo.que;
    pNode_t pNew;
    while(1)
    {
        newFd=accept(socketFd,NULL,NULL);
        pNew=(pNode_t)calloc(1,sizeof(Node_t));
        pNew->newFd=newFd;
        pthread_mutex_lock(&pq->mutex);
        queInsert(pq,pNew);//放任务
        pthread_mutex_unlock(&pq->mutex);
        pthread_cond_signal(&threadInfo.cond);//唤醒子线程
    }
    return 0;
}