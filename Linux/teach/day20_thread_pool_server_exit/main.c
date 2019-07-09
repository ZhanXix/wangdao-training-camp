#include "factory.h"

int exitFds[2];
void sigExitFunc(int signum)
{
    printf("%d is coming\n",signum);
    write(exitFds[1],&signum,1);
}
int epollAdd(int epfd,int fd)
{
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.fd=fd;
    int ret;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}
int main(int argc,char *argv[])
{
    if(argc!=5)
    {
        printf("./server ip port threadNum capacity\n");
        return -1;
    }
    pipe(exitFds);
    while(fork())
    {
        signal(SIGUSR1,sigExitFunc);
        int status;
        wait(&status);
        if(WIFEXITED(status))
        {
            printf("exit suceess\n");
            exit(0);
        }
    }
    close(exitFds[1]);
    Factory_t threadMainData;
    int threadNum=atoi(argv[3]);
    int capacity=atoi(argv[4]);
    factoryInit(&threadMainData,threadNum,capacity);
    factoryStart(&threadMainData);
    int socketFd,newFd;
    tcpInit(&socketFd,argv[1],argv[2]);
    pQue_t pq=&threadMainData.que;
    pNode_t pNew;
    int epfd=epoll_create(1);
    struct epoll_event evs[2];
    epollAdd(epfd,socketFd);
    epollAdd(epfd,exitFds[0]);
    int readyFdCount,i,j;
    while(1)
    {
        readyFdCount=epoll_wait(epfd,evs,2,-1);
        for(i=0;i<readyFdCount;i++)
        {
            if(evs[i].data.fd==socketFd)
            {
                newFd=accept(socketFd,NULL,NULL);
                pNew=(pNode_t)calloc(1,sizeof(Node_t));
                pNew->newFd=newFd;
                //放入队列
                pthread_mutex_lock(&pq->mutex);
                queInsert(pq,pNew);
                pthread_mutex_unlock(&pq->mutex);
                //通知子线程有任务
                pthread_cond_signal(&threadMainData.cond);
            }
            if(evs[i].data.fd==exitFds[0])
            {
                //给每一个子线程发送cancel
                for(j=0;j<threadNum;j++)
                {
                    pthread_cancel(threadMainData.pthid[j]);
                }
                for(j=0;j<threadNum;j++)
                {
                    pthread_join(threadMainData.pthid[j],NULL);
                }
                exit(0);
            }
        }
    }
    return 0;
}

