#include "func.h"
int Recv_File_Splice(int socketFd,off_t fileSize,int fileFd);
int main()
{
    int ret;
    //读入要下载的文件名
    char filename[40]={0};
    printf("输入要下载的文件名：");
    fflush(stdout);
    read(STDIN_FILENO,filename,sizeof(filename));
    //连接服务器
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in socketAddr;
    bzero(&socketAddr,sizeof(socketAddr));
    socketAddr.sin_family=AF_INET;
    socketAddr.sin_addr.s_addr=inet_addr("192.168.5.192");
    socketAddr.sin_port=htons(2000);
    ret=connect(socketFd,(struct sockaddr*)&socketAddr,sizeof(socketAddr));
    ERROR_CHECK(ret,-1,"connect");
    //发送文件名
    ret=send(socketFd,filename,strlen(filename)-1,0);
    ERROR_CHECK(ret,-1,"send");
    //接收文件打开信息
    char openFlag='0';
    ret=recv(socketFd,&openFlag,sizeof(openFlag),0);
    ERROR_CHECK(ret,-1,"recv");
    if('0'==openFlag)
    {
        printf("此文件在服务器端不存在！\n");
        return -1;
    }
    //接收文件大小
    off_t fileSize;
    int dataLen;
    ret=recv(socketFd,&dataLen,sizeof(int),0);
    ERROR_CHECK(ret,-1,"recv");
    ret=recv(socketFd,&fileSize,dataLen,0);
    ERROR_CHECK(ret,-1,"recv");
    printf("文件大小：%ld\n",fileSize);
    //开始计时
    struct timeval start,end;
    gettimeofday(&start,NULL);
    //接收文件
    int filenameLen=strlen(filename);
    filename[filenameLen-1]=0;
    int fileFd=open(filename,O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fileFd,-1,"open");
    ret=Recv_File_Splice(socketFd,fileSize,fileFd);
    if(-1==ret)
    {
        printf("接收文件失败\n");
        return -1;
    }
    //结束计时
    gettimeofday(&end,NULL);
    printf("共用时%ldus\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(socketFd);
    close(fileFd);
    return 0;
}