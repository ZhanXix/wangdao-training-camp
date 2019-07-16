#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "head.h"

#define DEBUG

//******************************************************************
//原fd_work_queue.h
typedef struct fd_work_node
{
    int clientFd;
    struct fd_work_node* pNext;
}Fd_Work_Node_t,*pFd_Work_Node_t;

typedef struct work_queue
{
    pFd_Work_Node_t pWorkQueueHead,pWorkQueueTail;
    pthread_mutex_t WorkQueuemutex;
    int WorkQueueSize;
    int WorkQueueCapacity;
}Work_Queue_t,*pWork_Queue_t;

//thread_pool.c
int WorkQueue_Init(pWork_Queue_t* ppWorkQueue,int workQueueCapacity);
int WorkQueue_Get(int *pclientFd,pWork_Queue_t pW);
int WorkQueue_Add(int newFd,pWork_Queue_t pW);

//******************************************************************
typedef struct thread_pool_info
{
    pWork_Queue_t pWorkQueue;
    pthread_t *pthId;
    int threadNum;
    pthread_cond_t cond;
    short WorkFlag;
    pthread_mutex_t log_mutex;
}Thread_Pool_Info_t,*pThread_Pool_Info_t;

typedef struct file_data
{
    int dataLen;
    char dataBuf[1000];
}File_Data_t;

//thread_pool.c
int ThreadPool_Init(pThread_Pool_Info_t pThreadPool,int ThreadNum);
int ThreadPool_Start(pThread_Pool_Info_t pThreadPool);

//thread_func.c
void *Thread_Func(void *p);
int Command_Deal(char *command,int clientFd,int *pCode,char *username);
int GET_PATH(int code,char *path,MYSQL *connect);
int Command_cd(int clientFd,int *pCode,MYSQL *connect,char *username);
int Command_ls(int clientFd,int *pCode,MYSQL *connect,char *username);
int Command_puts(int clientFd,int *pCode,MYSQL *connect,char *username);
int Command_gets(int clientFd,int *pCode,MYSQL *connect,char *username);
int Command_remove(int clientFd,int *pCode,MYSQL *connect,char *username);
int Command_pwd(int clientFd,int *pCode,MYSQL *connect);
int Command_mkdir(int clientFd,int *pCode,MYSQL *connect,char *username);
int Command_rmdir(int clientFd,int *pCode,MYSQL *connect,char *username);

#endif // !THREAD_POOL_H
