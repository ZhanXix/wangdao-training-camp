#include "process_pool.h"
//创建子进程，并初始化主数据结构
int makeChild(process_data_t *p,int procseeNum)
{
    int i;
    pid_t pid;
    int fds[2];
    int ret;
    for(i=0;i<procseeNum;i++)
    {
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(0==pid)
        {
            close(fds[0]);
            childHandle(fds[1]);
        }
        close(fds[1]);
        p[i].pid=pid;//子进程pid
        p[i].pipeFd=fds[0];//存储每个子进程的管道对端
        p[i].busy=0;
    }
    return 0;
}
int childHandle(int pipeFd)
{
    int newFd;
    char finishFlag;
    while(1)
    {
        recvFd(pipeFd,&newFd);//接收任务，没有任务时会睡觉
        tranFile(newFd);//给客户端发文件
        close(newFd);//关闭连接
        write(pipeFd,&finishFlag,1);//子进程通知父进程完成任务啦
    }
}