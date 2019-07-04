#include <func.h>
int recvCycle(int sfd,void *buf,int recvLen);
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
    int fd;
    int dataLen;
    char buf[1000]={0};
    recvCycle(socketFd,&dataLen,4);//接收文件名
    recvCycle(socketFd,&buf,dataLen);
    printf("%s\n",buf);
    fd=open(buf,O_CREAT|O_RDWR,0666);
    ERROR_CHECK(fd,-1,"open");
    while(1)
    {
        recvCycle(socketFd,&dataLen,4);
        if(dataLen>0)
        {
            recvCycle(socketFd,buf,dataLen);
            write(fd,buf,dataLen);
        }else{
            break;
        }
    }
    close(fd);
    close(socketFd);
    return 0;
}

