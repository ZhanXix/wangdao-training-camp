#include "func.h"

#define DEBUG

typedef struct child_process_data
{
    pid_t pid;
    int pipeFd;
    short busy;
}Child_Process_Data_t,*pChild_Process_Data_t;

typedef struct file_data
{
    int dataLen;
    char dataBuf[1000];
}File_Data_t;

//func.c
int Tcp_Init(int *pSocketFd,char *ip,char *port);
int Epoll_Add(int epFd,int socketFd);
int sendFd(int pipeFd,int Fd_needSend);
int recvFd(int pipeFd,int *pFd_recv);

//child.c
int Create_Child_Process(pChild_Process_Data_t pChildProcessData,int processNum);
int Child_Process_Function(int pipeFd);
int Send_File(int clientFd);
