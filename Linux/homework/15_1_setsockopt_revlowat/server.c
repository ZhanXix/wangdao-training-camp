//设定rcvlowat选项，感受效果
#include "func.h"
int main()
{
    //初始化
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
    ret=listen(socketFd,10);
    ERROR_CHECK(ret,-1,"lisen");
    //连接
    int newFd=accept(socketFd,NULL,NULL);
    ERROR_CHECK(newFd,-1,"accept");
    //SO_RCVLOWAT设置接收缓冲区下限20
    int lowAt=20;
    ret=setsockopt(newFd,SOL_SOCKET,SO_RCVLOWAT,&lowAt,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    //epoll监听对话
    int epFd=epoll_create(1);
    struct epoll_event event,events[2];
    event.events=EPOLLIN;
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epFd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=newFd;
    ret=epoll_ctl(epFd,EPOLL_CTL_ADD,newFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int fdCount,i;
    char buf[128]={0};
    while(1)
    {
        fdCount=epoll_wait(epFd,events,2,-1);
        if(fdCount>0)
        {
            for(i=0;i<fdCount;++i)
            {
                if(STDIN_FILENO==events[i].data.fd&&EPOLLIN==events[i].events)
                {
                    bzero(buf,sizeof(buf));
                    ret=read(STDIN_FILENO,buf,sizeof(buf));
                    if(0==ret)
                    {
                        printf(">>>>>>>>>已主动断开<<<<<<<<<\n");
                        goto end;
                    }
                    send(newFd,buf,strlen(buf)-1,0);
                }
                if(newFd==events[i].data.fd)
                {
                    bzero(buf,sizeof(buf));
                    ret=recv(newFd,buf,sizeof(buf),0);
                    if(0==ret)
                    {
                        printf(">>>>>>>>>连接已断开<<<<<<<<<\n");
                        goto end;
                    }
                    printf("%77s\n",buf);
                }
            }
        }
    }
    //结束
end:
    close(socketFd);
    close(newFd);
    return 0;
}