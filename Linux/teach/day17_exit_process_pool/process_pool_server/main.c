#include "process_pool.h"
int exitFds[2];
void SigExitFunc(int sigNum)
{
    write(exitFds[1],"1",1);
}
int main(int argc,char *argv[])
{
    if(argc!=4)
    {
        printf("./process_pool_server ip port process_num\n");
        return -1;
    }
    int processNum=atoi(argv[3]);//得到进程数
    process_data_t *pData=(process_data_t*)calloc(processNum,sizeof(process_data_t));
    makeChild(pData,processNum);//创建子进程
    //退出机制
    pipe(exitFds);
    signal(SIGUSR1,SigExitFunc);
    int i;
#ifdef DEBUG
    for(i=0;i<processNum;i++)
    {
        printf("pid=%d pipeFd=%d\n",pData[i].pid,pData[i].pipeFd);
    }
#endif
    int socketFd;
    tcpInit(&socketFd,argv[1],argv[2]);//初始化socket并开启监听
    int epfd=epoll_create(1);
    struct epoll_event *evs;
    evs=(struct epoll_event*)calloc(processNum+2,sizeof(struct epoll_event));
    epollInAdd(epfd,socketFd);
    epollInAdd(epfd,exitFds[0]);
    for(i=0;i<processNum;i++)
    {
        epollInAdd(epfd,pData[i].pipeFd);//注册监听每一个子进程的管道对端
    }
    int readyFdCount,newFd,j;
	char noBusyFlag;
    while(1)
    {
        readyFdCount=epoll_wait(epfd,evs,processNum+2,-1);
        for(i=0;i<readyFdCount;i++)
        {
            if(evs[i].data.fd==exitFds[0])
            {
                for(j=0;j<processNum;j++)//给所有子进程发送10号信号
                {
                    kill(pData[j].pid,SIGUSR1);
                }
                for(j=0;j<processNum;j++)
                {
                    wait(NULL);
                }
				printf("I will exit ok\n");
                exit(0);
            }
            if(evs[i].data.fd==socketFd)
            {
                newFd=accept(socketFd,NULL,NULL);//接收客户端请求
                for(j=0;j<processNum;j++)//要找非忙碌的子进程
                {
                    if(0==pData[j].busy)
                    {
                        sendFd(pData[j].pipeFd,newFd);//把任务发给对应的子进程
                        pData[j].busy=1;//子进程标识为忙碌
                        printf("%d is busy\n",pData[j].pid);
                        break;
                    }
                }
                close(newFd);
            }
            for(j=0;j<processNum;j++)
            {
                if(evs[i].data.fd==pData[j].pipeFd)
                {
                    read(pData[j].pipeFd,&noBusyFlag,1);//收到子进程的通知
                    pData[j].busy=0;//子进程设置为非忙碌
                    printf("%d is not busy\n",pData[j].pid);
                    break;
                }
            }
        }
    }
    return 0;
}