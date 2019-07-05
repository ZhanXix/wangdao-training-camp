#include "process_pool.h"

int Create_Child_Process(pChild_Process_Data_t pChildProcessData,int processNum)
{
    int ret,i;
    int pipe[2];
    pid_t pid;
    for(i=0;i<processNum;++i)
    {
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,pipe);
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(!pid)//子进程
        {
            close(pipe[0]);
            Child_Process_Function(pipe[1]);
        }else{//父进程
            close(pipe[1]);
            pChildProcessData[i].busy=0;
            pChildProcessData[i].pid=pid;
            pChildProcessData[i].pipeFd=pipe[0];
        }
    }
    return 0;
}

int Child_Process_Function(int pipeFd)
{
    int clientFd;
    while(1)
    {
        //接收文件传输请求
        recvFd(pipeFd,&clientFd);
        printf("子进程已收到请求\n");
        //传输文件
        Send_File(clientFd);
        //文件传输完毕
        printf("文件传输完毕\n");
        send(pipeFd,"0",1,0);
        close(clientFd);
    }
    return 0;
}

int Send_File(int clientFd)
{
    int ret;
    char filename[40]={0};
    File_Data_t fileData;
    bzero(&fileData,sizeof(fileData));
    //接收文件名
    ret=recv(clientFd,filename,sizeof(filename),0);
    ERROR_CHECK(ret,-1,"recv");
    printf("传输文件：%s\n",filename);
    int fileFd=open(filename,O_RDWR);
    //发送文件是否存在的信息
    if(fileFd==-1)
    {
        printf("打开文件失败\n");
        send(clientFd,"0",1,0);
        return -1;
    }
    ret=send(clientFd,"1",1,0);
    ERROR_CHECK(ret,-1,"send");
    //发送文件大小
    struct stat statBuf;
    fstat(fileFd,&statBuf);//得到文件信息
    fileData.dataLen=sizeof(statBuf.st_size);
    memcpy(fileData.dataBuf,&statBuf.st_size,sizeof(statBuf.st_size));
    ret=send(clientFd,&fileData,fileData.dataLen+4,0);
    ERROR_CHECK(ret,-1,"send");
    //发送文件内容
    ret=sendfile(clientFd,fileFd,NULL,statBuf.st_size);
    ERROR_CHECK(ret,-1,"sendfile");
    close(fileFd);
    return 0;
}