/* 
 * Update Logs
 * 1.0 2019/7/4 使用多进程，实现多个客户端同时下载大文件，有进度显示,实现mmap，sendfile的性能优化
 * 2.0 2019/7/5 编写进程池退出机制，确保发送信号后，父进程依次杀掉子进程，然后自己退出；修改了一个epoll监视的数量bug
 * 3.0 2019/7/5 编写进程池退出机制，确保发送信号后，父进程通知子进程依次退出，然后自己退出；修改了服务器子进程打开文件失败的机制
 */
#include "process_pool.h"

int fds_exit[2];//用于发送退出信息的管道
void SigFunc_Exit(int sigNum)
{
    write(fds_exit[1],"1",1);
#ifdef DEBUG
    printf("已捕捉到退出信号%d\n",sigNum);
#endif // DEBUG
}

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2); //参数是输入的进程数
    int ret;
    int i,j;
    //初始化socketFd
    int socketFd,newFd;
    ret=Tcp_Init(&socketFd,"192.168.5.192","2000");
    if(-1==ret)
    {
        return -1;
    }
    //创建子进程
    pChild_Process_Data_t pChildProcessData;
    int processNum=atoi(argv[1]);
    pChildProcessData=(pChild_Process_Data_t)calloc(processNum,sizeof(Child_Process_Data_t));
    Create_Child_Process(pChildProcessData,processNum);
#ifdef DEBUG
    printf("已创建子进程：\n");    
    for(i=0;i<processNum;i++) 
    {
        printf("%d:pid=%d,pipeFd=%d\n",i,pChildProcessData[i].pid,pChildProcessData[i].pipeFd);
    }  
#endif // DEBUG
    //退出机制
    pipe(fds_exit);
    signal(SIGUSR1,SigFunc_Exit);//发送10号信号即退出
    //epoll监听
    int epFd=epoll_create(1);
    ERROR_CHECK(epFd,-1,"epoll_create");
    Epoll_Add(epFd,socketFd);//将socketFd加入监听
    Epoll_Add(epFd,fds_exit[0]);//将fds_exit[0]加入监听
    for(i=0;i<processNum;i++)
    {
        Epoll_Add(epFd,pChildProcessData[i].pipeFd);//将所有子进程加入监听
    }
    struct epoll_event *pEvents;
    pEvents=(struct epoll_event*)calloc(processNum+2,sizeof(struct epoll_event));
    int readyFdCount=0;
    int busyFlag;
    char exitFlag;
    while(1)
    {
        readyFdCount=epoll_wait(epFd,pEvents,processNum+2,-1);
        for(i=0;i<readyFdCount;i++)
        {
            if(pEvents[i].data.fd==fds_exit[0])//收到退出信号
            {
                ret=read(fds_exit[0],&exitFlag,1);
                ERROR_CHECK(ret,-1,"read");
                for(j=0;j<processNum;j++)
                {
                    sendFd(pChildProcessData[j].pipeFd,0,1);
                #ifdef DEBUG
                    printf("已向子进程%d发送结束信息\n",pChildProcessData[j].pid);
                #endif // DEBUG
                }
                for(j=0;j<processNum;j++)
                {
                    wait(NULL);
                }
                printf("退出处理完毕\n");
                exit(0);
            }
            if(pEvents[i].data.fd==socketFd)
            {
                newFd=accept(socketFd,NULL,NULL);
                ERROR_CHECK(newFd,-1,"accept");
                for(j=0;j<processNum;j++)
                {
                    if(pChildProcessData[j].busy==0)
                    {
                        sendFd(pChildProcessData[j].pipeFd,newFd,0);
                        pChildProcessData[j].busy=1;
                        printf("已向进程%d发送请求\n",pChildProcessData[j].pid); 
                        break;
                    }
                    printf("找不到空闲子进程\n");
                }
                close(newFd);
            }
            for(j=0;j<readyFdCount;j++)
            {
                if(pEvents[i].data.fd==pChildProcessData[j].pipeFd)
                {
                    recv(pChildProcessData[j].pipeFd,&busyFlag,sizeof(busyFlag),0);
                    pChildProcessData[j].busy=0;
                    printf("进程%d已空闲\n",pChildProcessData[j].pid); 
                }
            }
        }
    }
    return 0;
}