//使用多进程，实现多个客户端同时下载大文件，有进度显示,实现mmap，sendfile的性能优化
#include "process_pool.h"
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
    //监听客户端的请求
    int epFd=epoll_create(1);
    ERROR_CHECK(epFd,-1,"epoll_create");
    Epoll_Add(epFd,socketFd);//将socketFd加入监听
    for(i=0;i<processNum;i++)
    {
        Epoll_Add(epFd,pChildProcessData[i].pipeFd);//将所有子进程加入监听
    }
    struct epoll_event *pEvents;
    pEvents=(struct epoll_event*)calloc(processNum,sizeof(struct epoll_event));
    int readyFdCount=0;
    int busyFlag;
    while(1)
    {
        readyFdCount=epoll_wait(epFd,pEvents,processNum+1,-1);
        for(i=0;i<readyFdCount;i++)
        {
            if(pEvents[i].data.fd==socketFd)
            {
                newFd=accept(socketFd,NULL,NULL);
                ERROR_CHECK(newFd,-1,"accept");
                for(j=0;j<processNum;j++)
                {
                    if(pChildProcessData[j].busy==0)
                    {
                        sendFd(pChildProcessData[j].pipeFd,newFd);
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