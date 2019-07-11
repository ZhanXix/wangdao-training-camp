#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "func.h"
#include "fd_work_queue.h"

#define DEBUG

typedef struct thread_pool_info
{
    pWork_Queue_t pWorkQueue;
    pthread_t *pthId;
    int threadNum;
    pthread_cond_t cond;
    short WorkFlag;
}Thread_Pool_Info_t,*pThread_Pool_Info_t;

typedef struct file_data
{
    int dataLen;
    char dataBuf[1000];
}File_Data_t;

//func.c
int Send_File(int clientFd);
int Tcp_Init(int *pSocketFd,char *ip,char *port);
int Epoll_Add(int epFd,int socketFd);

//thread_pool.c
int ThreadPool_Init(pThread_Pool_Info_t pThreadPool,char *ThreadNum,char *workQueueCapacity);
int ThreadPool_Start(pThread_Pool_Info_t pThreadPool);
void *Thread_Func(void *p);

#endif // !THREAD_POOL_H
