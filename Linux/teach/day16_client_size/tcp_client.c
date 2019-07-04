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
    off_t fileSize,downLoadSize=0,lastLoadSize=0,slice;
    recvCycle(socketFd,&dataLen,4);
    recvCycle(socketFd,&fileSize,dataLen);
    slice=fileSize/1000;
	struct timeval start,end;
    gettimeofday(&start,NULL);
    while(1)
    {
        recvCycle(socketFd,&dataLen,4);
        if(dataLen>0)
        {
            recvCycle(socketFd,buf,dataLen);
            write(fd,buf,dataLen);
            downLoadSize+=dataLen;
            if(downLoadSize-lastLoadSize>=slice)
            {
                printf("%5.2f%s\r",(float)downLoadSize/fileSize*100,"%");
                fflush(stdout);
                lastLoadSize=downLoadSize;
            }
        }else{
            printf("100.00%%\n");
            break;
        }
    }
	gettimeofday(&end,NULL);
    printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(fd);
    close(socketFd);
    return 0;
}

