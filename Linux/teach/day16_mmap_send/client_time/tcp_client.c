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
    off_t fileSize,downloadSize=0;
    recvCycle(socketFd,&dataLen,4);
    recvCycle(socketFd,&fileSize,dataLen);
    time_t lastTime,nowTime;
    lastTime=nowTime=time(NULL);
	struct timeval start,end;
    gettimeofday(&start,NULL);
    while(1)
    {
        ret=recvCycle(socketFd,&dataLen,4);
		if(-1==ret)
        {
            break;
        }
        if(dataLen>0)
        {
            ret=recvCycle(socketFd,buf,dataLen);
			if(-1==ret)
			{
				break;
			}
            write(fd,buf,dataLen);
            downloadSize+=dataLen;
            time(&nowTime);
            if(nowTime-lastTime>=1)
            {
                printf("%5.2f%s\r",(float)downloadSize/fileSize*100,"%");// \r回到行首
                fflush(stdout);
                lastTime=nowTime;
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

