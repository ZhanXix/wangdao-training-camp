#include "func.h"
int tcpInit(int *, char *, char *);
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    int ret;
    ret=tcpInit(&socketFd, argv[1], argv[2]);
    if(-1==ret)
    {
        return -1;
    }
    int newFd = accept(socketFd, NULL, NULL);
    char buf[10];
    int epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.events=EPOLLIN;//监听读事件
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=newFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,newFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int readyFdcount,i;
    time_t pastTime,nowTime;
    pastTime=nowTime=time(NULL);
    while(1)
    {
        readyFdcount = epoll_wait(epfd,evs,2,1000);//最后一个参数代表超时时间（单位是ms），-1表示一直等，0表示不等
        for (i = 0; i < readyFdcount; i++)
        {
            if (evs[i].events==EPOLLIN&&evs[i].data.fd==STDIN_FILENO)
            {
                bzero(buf, sizeof(buf));
                ret = read(STDIN_FILENO, buf, sizeof(buf));
                if (0 == ret)
                {
                    printf("byebye\n");
                    goto end;
                }
                send(newFd, buf, strlen(buf) - 1, 0);
            }
            if (evs[i].data.fd==newFd)
            {
                bzero(buf, sizeof(buf));
                ret = recv(newFd, buf, sizeof(buf), 0);
                if (0 == ret)
                {
                    printf("byebye\n");
                    goto end;
                }
                printf("%s\n", buf);
            }
            pastTime=time(NULL);
        }
        if(0==readyFdcount)
        {
            nowTime=time(NULL);
            if(nowTime-pastTime>=5)
            {
                close(newFd);
                break;
            }
        }
    }
end:
    close(newFd);
    close(socketFd);
    return 0;
}