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
    int newFd;
    char buf[10];
    int epfd=epoll_create(1);
    struct epoll_event event,evs[3];
    event.events=EPOLLIN;//监听读事件
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int readyFdcount,i;
    while (1)
    {
        readyFdcount = epoll_wait(epfd,evs,3,-1);
        for (i = 0; i < readyFdcount; i++)
        {
            if(evs[i].data.fd==socketFd)
            {
                newFd=accept(socketFd,NULL,NULL);
                event.data.fd=newFd;
                ret=epoll_ctl(epfd,EPOLL_CTL_ADD,newFd,&event);
                ERROR_CHECK(ret,-1,"epoll_ctl");
            }
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
                    event.data.fd=newFd;
                    ret=epoll_ctl(epfd,EPOLL_CTL_DEL,newFd,&event);
                    ERROR_CHECK(ret,-1,"epoll_ctl");
                    close(newFd);
					break;
                }
                printf("%s\n", buf);
            }
        }
    }
end:
    close(socketFd);
    return 0;
}
