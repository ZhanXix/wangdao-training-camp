//练习一边发送，一边不接收，看看send的阻塞效果，然后修改描述符为非阻塞，再看看send效果
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
    accept(socketFd,NULL,NULL);
    char buf[10]="helloworld";
    scanf("%s",buf);
    puts(buf);
    close(socketFd);
    return 0;
}