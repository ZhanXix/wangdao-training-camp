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
    ret=connect(socketFd,(struct sockaddr*)&socketAddr,sizeof(socketAddr));
    ERROR_CHECK(ret,-1,"connect");
    fd_set rdSet;
    char buf[128]={0};
    while(1)
    {
        FD_ZERO(&rdSet);
        FD_SET(STDIN_FILENO,&rdSet);
        FD_SET(socketFd,&rdSet);
        ret=select(socketFd+1,&rdSet,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdSet))
        {
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(0==ret)
            {
                printf(">>>>>>>>>已主动断开<<<<<<<<<\n");
                break;
            }
            ret=send(socketFd,buf,strlen(buf)-1,0);
        }
        if(FD_ISSET(socketFd,&rdSet))
        {
            bzero(buf,sizeof(buf));
            ret=recv(socketFd,buf,sizeof(buf),0);
            if(0==ret)
            {
                printf(">>>>>>>>>连接已断开<<<<<<<<<\n");
                break;
            }
            printf("%77s\n",buf);
        }
    }
    close(socketFd);
    return 0;
}