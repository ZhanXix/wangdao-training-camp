#define _GNU_SOURCE233
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
    recvCycle(socketFd,buf,dataLen);
    fd=open(buf,O_CREAT|O_RDWR,0666);
    ERROR_CHECK(fd,-1,"open");
    //接收文件大小
    off_t fileSize,downLoadSize=0;
    recvCycle(socketFd,&dataLen,4);
    recvCycle(socketFd,&fileSize,dataLen);
    printf("fileSize=%ld\n",fileSize);
	struct timeval start,end;
    int fds[2];//自己用管道两端
    pipe(fds);
    gettimeofday(&start,NULL);
    while(downLoadSize<fileSize)
    {
        ret=splice(socketFd,NULL,fds[1],NULL,65536,SPLICE_F_MOVE|SPLICE_F_MORE);
        ERROR_CHECK(ret,-1,"splice");
        ret=splice(fds[0],NULL,fd,NULL,ret,SPLICE_F_MOVE|SPLICE_F_MORE);
        downLoadSize+=ret;
    }
	gettimeofday(&end,NULL);
    printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(fd);
    close(socketFd);
    return 0;
}

