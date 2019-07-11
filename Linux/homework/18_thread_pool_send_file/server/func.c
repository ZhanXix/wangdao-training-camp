#include "thread_pool.h"

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
        printf("文件不存在，打开失败\n");
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

int Tcp_Init(int *pSocketFd,char *ip,char *port)
{
    int ret;
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in socketAddr;
    bzero(&socketAddr,sizeof(socketAddr));
    socketAddr.sin_family=AF_INET;
    socketAddr.sin_addr.s_addr=inet_addr(ip);
    socketAddr.sin_port=htons(atoi(port));
    int reuse=1;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    ret=bind(socketFd,(struct sockaddr*)&socketAddr,sizeof(socketAddr));
    ERROR_CHECK(ret,-1,"bind");
    ret=listen(socketFd,10);
    ERROR_CHECK(ret,-1,"listen");
    *pSocketFd=socketFd;
    return 0;
}

int Epoll_Add(int epFd,int socketFd)
{
    int ret;
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.fd=socketFd;
    ret=epoll_ctl(epFd,EPOLL_CTL_ADD,socketFd,&event);
#ifdef DEBUG
    printf("epoll已添加监视%d\n",socketFd);
#endif // DEBUG
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}

int sendFd(int pipeFd,int Fd_needSend,char exitFlag_needSend)
{
    int ret;
    struct iovec iov[2];    //iov
    char buf1[2]="1";
    iov[0].iov_base=&exitFlag_needSend;//结束标志
    iov[0].iov_len=1;
    iov[1].iov_base=buf1;
    iov[1].iov_len=1;
    struct cmsghdr *cmsg;    //cmsg
    int cmsgLen=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)malloc(cmsgLen);
    bzero(cmsg,cmsgLen);
    cmsg->cmsg_len=cmsgLen;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    *(int*)CMSG_DATA(cmsg)=Fd_needSend;
    struct msghdr msg;      //msg
    bzero(&msg,sizeof(msg));
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    msg.msg_control=cmsg;
    msg.msg_controllen=cmsgLen;
    ret=sendmsg(pipeFd,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}
int recvFd(int pipeFd,int *pFd_recv,char *pExitFlag_recv)
{
    int ret;
    struct iovec iov[2];    //iov
    char buf1[2]="1";
    iov[0].iov_base=pExitFlag_recv;//结束标志
    iov[0].iov_len=1;
    iov[1].iov_base=buf1;
    iov[1].iov_len=1;
    struct cmsghdr *cmsg;    //cmsg
    int cmsgLen=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)malloc(cmsgLen);
    bzero(cmsg,cmsgLen);
    cmsg->cmsg_len=cmsgLen;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    struct msghdr msg;      //msg
    bzero(&msg,sizeof(msg));
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    msg.msg_control=cmsg;
    msg.msg_controllen=cmsgLen;
    ret=recvmsg(pipeFd,&msg,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    *pFd_recv=*(int*)CMSG_DATA(cmsg);
    return 0;
}