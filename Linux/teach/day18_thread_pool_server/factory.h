#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"

typedef struct{
    Que_t que;
    pthread_cond_t cond;
    pthread_t *pthid;//存储线程ID的起始地址
    int threadNum;//线程数目
    short startFlag;//线程池是否启动
}Factory_t,*pFactory_t;
int factoryInit(pFactory_t p,int threadNum,int capacity);
int factoryStart(pFactory_t);
int tcpInit(int *psocketFd,char *ip,char *port);
int tranFile(int newFd);
#endif // !__FACTORY_H__