#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"
typedef struct{
    Que_t que;
    pthread_cond_t cond;
    pthread_t *pthid;
    int threadNum;
    int startFlag;
}Factory_t,*pFactory_t;
typedef struct{
    int dataLen;//代表后面存储的数据长度
    char buf[1000];
}train_t;
#define FILENAME "file"
int factoryInit(pFactory_t,int,int);
int factoryStart(pFactory_t);
int tcpInit(int *sFd,char* ip,char* port);
int tranFile(int);
#endif

