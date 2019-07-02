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
    char buf[1000]={0};
    int total=0;
    int status=fcntl(socketFd,F_GETFL);
    status=status|O_NONBLOCK;
    fcntl(socketFd,F_SETFL,status);
    while(1)
    {
        ret=send(socketFd,buf,sizeof(buf),0);
        if(-1==ret)
        {
            printf("send end\n");
            break;
        }
        total+=ret;
        printf("send data=%d,total=%d\n",ret,total);
    }
    close(socketFd);
    return 0;
}