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
    ret=bind(socketFd,(struct sockaddr*)&socketAddr,sizeof(socketAddr));
    ERROR_CHECK(ret,-1,"bind");
    socklen_t socketLen=sizeof(socketAddr);
    struct sockaddr_in clientAddr;
    bzero(&clientAddr,sizeof(clientAddr));
    char buf[128]={0};
    ret=recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr*)&clientAddr,&socketLen);
    ERROR_CHECK(ret,-1,"recvfrom");
    printf("Client %s:%d says %s\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port),buf);
    ret=sendto(socketFd,"HELLO WORLD",11,0,(struct sockaddr*)&clientAddr,sizeof(clientAddr));
    ERROR_CHECK(ret,-1,"sendto");
    close(socketFd);
    return 0;
}