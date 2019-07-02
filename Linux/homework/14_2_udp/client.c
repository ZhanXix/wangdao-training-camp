#include "func.h"
int main()
{
    int ret;
    int socketFd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in socketAddr;
    bzero(&socketAddr,sizeof(socketAddr));
    socketAddr.sin_family=AF_INET;
    socketAddr.sin_addr.s_addr=inet_addr("192.168.5.192");
    socketAddr.sin_port=htons(2000);
    socklen_t socketLen=sizeof(socketAddr);
    ret=sendto(socketFd,"HI I AM CLIENT",14,0,(struct sockaddr*)&socketAddr,sizeof(socketAddr));
    ERROR_CHECK(ret,-1,"sendto");
    char buf[128]={0};
    ret=recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr*)&socketAddr,&socketLen);
    printf("SERVER %s:%d says %s\n",inet_ntoa(socketAddr.sin_addr),ntohs(socketAddr.sin_port),buf);
    ERROR_CHECK(ret,-1,"recvfrom");
    close(socketFd);
    return 0;
}