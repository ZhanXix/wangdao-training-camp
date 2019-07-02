#include "func.h"

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(argv[2]));
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    char buf[128]={0};
    sendto(socketFd,"I am client",11,0,(struct sockaddr*)&serAddr,sizeof(struct sockaddr));
    recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
    printf("client gets=%s\n",buf);
    close(socketFd);
    return 0;
}