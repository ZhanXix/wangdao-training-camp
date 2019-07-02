//一个客户端，一个服务器端，客户端和服务器端进行即时聊天。客户端退出后，能够再次连接服务器。(通过select)
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
    char buf[128]={0};
    fd_set rdSet,allSet;
    FD_ZERO(&allSet);
    FD_SET(STDIN_FILENO,&allSet);
    FD_SET(socketFd,&allSet);
    while(1)
    {
        memcpy(&rdSet,&allSet,sizeof(fd_set));
        ret=select(5,&rdSet,NULL,NULL,NULL);
        if(ret>0)
        {
            if(FD_ISSET(socketFd,&rdSet))
            {
                newFd=accept(socketFd,NULL,NULL);
                FD_SET(newFd,&allSet);
            }
            if(FD_ISSET(STDIN_FILENO,&rdSet))
            {
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(0==ret)
                {
                    printf(">>>>>>>>>已主动断开<<<<<<<<<\n");
                    break;
                }
                ret=send(newFd,buf,strlen(buf)-1,0);
            }
            if(FD_ISSET(newFd,&rdSet))
            {
                bzero(buf,sizeof(buf));
                ret=recv(newFd,buf,sizeof(buf),0);
                if(0==ret)
                {
                    printf(">>>>>>>>>连接已断开<<<<<<<<<\n");
                    FD_CLR(newFd,&allSet);
                    close(newFd);
                }
                printf("%77s\n",buf);
            }
        }
    }
    close(socketFd);
    return 0;
}