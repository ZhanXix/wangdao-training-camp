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
    //连接
    ret=connect(socketFd,(struct sockaddr*)&socketAddr,sizeof(socketAddr));
    ERROR_CHECK(ret,-1,"connet");
    //客户端只发送一次“hello”,不发送其他任何数据，不接收任何数据
    send(socketFd,"hello",5,0);
    printf("已发送数据 hello\n");
    //结束
    printf(">>>>>>>>>测试结束<<<<<<<<<\n");
    close(socketFd);
    return 0;
}