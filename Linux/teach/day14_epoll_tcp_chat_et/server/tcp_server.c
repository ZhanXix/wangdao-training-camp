#include "func.h"
int tcpInit(int *, char *, char *);
int setNonBlock(int);
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
    char buf[10];
    int epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.events=EPOLLIN;//监听读事件
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    setNonBlock(newFd);
	event.events=EPOLLIN|EPOLLET;//监听读事件,边沿触发
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
                while(1)
                {
                    bzero(buf, sizeof(buf));
                    ret = recv(newFd, buf, sizeof(buf), 0);
                    if (0 == ret)
                    {
                        printf("byebye\n");
                        goto end;
                    }else if(-1==ret)//内和接收缓冲区读空
                    {
                        break;
                    }else{
                    printf("%s", buf);
                    }
                }
                printf("\n");
            }
        }
    }
end:
    close(newFd);
    close(socketFd);
    return 0;
}
