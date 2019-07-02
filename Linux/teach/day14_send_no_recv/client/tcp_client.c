#include <func.h>
int setNonBlock(int);
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(argv[2]));
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    ret=connect(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"connect");
    char buf[1000];
    int total=0;
    setNonBlock(socketFd);
    while(1)
    {
        ret=send(socketFd,buf,sizeof(buf),0);
        if(-1==ret)
        {
            break;
        }
        total+=ret;
        printf("ret=%d,total=%d\n",ret,total);
    }
    close(socketFd);
    return 0;
}

