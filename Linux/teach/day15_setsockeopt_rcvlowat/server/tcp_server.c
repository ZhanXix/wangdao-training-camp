#include "func.h"
int tcpInit(int *, char *, char *);
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    int socketFd;
    int ret;
    ret=tcpInit(&socketFd, argv[1], argv[2]);
    if(-1==ret)
    {
        return -1;
    }
    int newFd = accept(socketFd, NULL, NULL);
    char buf[128];
    int epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.events=EPOLLIN;//监听读事件
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int revLowAtValue=20;
    ret=setsockopt(newFd,SOL_SOCKET,SO_RCVLOWAT,&revLowAtValue,sizeof(int));//提高接收缓冲区下限，减少系统调用次数，提升接收效率
    ERROR_CHECK(ret,-1,"setsockopt");
    event.data.fd=newFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,newFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int readyFdcount,i;
    while (1)
    {
        readyFdcount = epoll_wait(epfd,evs,2,-1);
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
        }
    }
end:
    close(newFd);
    close(socketFd);
    return 0;
}
