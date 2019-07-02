//通过epoll的边沿触发模式实现即时聊天。注意用非阻塞模式，客户端断开后，能够再次连接
#include "func.h"
int main()
{
    int ret;
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in socketAddr;
    bzero(&socketAddr,sizeof(socketAddr));
    socketAddr.sin_family=AF_INET;
    socketAddr.sin_addr.s_addr=inet_addr("192.168.5.192");
    socketAddr.sin_port=htons(2000);
    ret=bind(socketFd,(struct sockaddr*)&socketAddr,sizeof(socketAddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);
    int newFd;
    char buf[10]={0};
    int epFd=epoll_create(1);
    struct epoll_event event,events[3];
    event.events=EPOLLIN;
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epFd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int status;
    event.events=EPOLLIN;
    event.data.fd=socketFd;
    ret=epoll_ctl(epFd,EPOLL_CTL_ADD,socketFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int allFd,i;
    while(1)
    {
        allFd=epoll_wait(epFd,events,3,-1);
        for(i=0;i<allFd;++i)
        {
            if(events[i].data.fd==socketFd)
            {
                newFd=accept(socketFd,NULL,NULL);
                status=fcntl(newFd,F_GETFL);
                status=status|O_NONBLOCK;
                fcntl(newFd,F_SETFL,status);
                event.events=EPOLLIN|EPOLLET;
                event.data.fd=newFd;
                ret=epoll_ctl(epFd,EPOLL_CTL_ADD,newFd,&event);
                ERROR_CHECK(ret,-1,"epoll_ctl");
            }
            if(events[i].events==EPOLLIN&&events[i].data.fd==STDIN_FILENO)
            {
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(0==ret)
                {
                    printf(">>>>>>>>>已主动断开<<<<<<<<<\n");
                    goto end;
                }
                ret=send(newFd,buf,strlen(buf)-1,0);
            }
            if(events[i].data.fd==newFd)
            {
                while(1)
                {
                    bzero(buf,sizeof(buf));
                    ret=recv(newFd,buf,sizeof(buf),0);
                    if(0==ret)
                    {
                        printf(">>>>>>>>>连接已断开<<<<<<<<<\n");
                        ret=epoll_ctl(epFd,EPOLL_CTL_DEL,newFd,&event);
                        ERROR_CHECK(ret,-1,"epoll_ctl");
                        close(newFd);
                        break;
                    }else if(-1==ret){
                        break;
                    }else
                    {
                        printf("%s",buf);
                    }
                }
                printf("\n");
            }
        }
    }
end:
    close(epFd);
    close(socketFd);
    return 0;
}