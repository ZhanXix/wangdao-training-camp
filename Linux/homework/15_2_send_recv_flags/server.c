//使用recv的flags选项，MSG_PEEK和MSG_DONTWAIT，使用send的MSG_DONTWAIT
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
    char buf[10]={0};
    //使用recv和send的flags参数
    //客户端只发送一次“hello”,不发送其他任何数据，不接收任何数据
    ret=recv(newFd,buf,5,MSG_PEEK);
    printf("使用recv的MSG_PEEK选项 ret=%d,buf=%s\n",ret,buf);
    bzero(buf,sizeof(buf));
    ret=recv(newFd,buf,5,0);
    printf("不使用recv的任何选项 ret=%d,buf=%s\n",ret,buf);
    bzero(buf,sizeof(buf));
    ret=recv(newFd,buf,5,MSG_DONTWAIT);
    printf("使用recv的MSG_DONTWAIT选项 ret=%d,buf=%s\n",ret,buf);
    ret=send(newFd,"world",5,MSG_DONTWAIT);
    printf("使用send的MSG_DONTWAIT选项 ret=%d\n",ret);
    //结束
    printf(">>>>>>>>>测试结束<<<<<<<<<\n");
    close(socketFd);
    close(newFd);
    return 0;
}