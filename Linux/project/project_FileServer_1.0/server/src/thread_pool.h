#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "head.h"
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

//thread_pool.c
int ThreadPool_Init(pThread_Pool_Info_t pThreadPool,int ThreadNum);
int ThreadPool_Start(pThread_Pool_Info_t pThreadPool);

//thread_func.c
void *Thread_Func(void *p);
int Command_Deal(char *command,int clientFd,MYSQL *connect,int *pPrecode);
int GET_PATH(int code,char *path,MYSQL *connect);
int Command_cd(int clientFd,int *code,MYSQL *connect);
int Command_ls(int clientFd,int *pCode,MYSQL *connect);
int Command_puts(int clientFd,int *pCode,MYSQL *connect);
int Command_gets(int clientFd,int *pCode,MYSQL *connect);
int Command_remove(int clientFd,int *pCode,MYSQL *connect);
int Command_pwd(int clientFd,int *pCode,MYSQL *connect);

#endif // !THREAD_POOL_H
