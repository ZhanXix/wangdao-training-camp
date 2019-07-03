//使用sendmsg实现描述符从一个进程传递给另一个进程
#include "func.h"
int sendFd(int pipeFd,int Fd_needSend)
{
    int ret;
    struct iovec iov[2];    //iov
    char buf0[2]="0",buf1[2]="1";
    iov[0].iov_base=buf0;
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
int recvFd(int pipeFd,int *pFd_recv)
{
    int ret;
    struct iovec iov[2];    //iov
    char buf0[2]="0",buf1[2]="1";
    iov[0].iov_base=buf0;
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
int main(int argc,char* argv[])
{
    int ret;
    ARGS_CHECK(argc,2);
    int pipe[2];//0写端，1读端
    socketpair(AF_LOCAL,SOCK_STREAM,0,pipe);
    char buf[32]={0};
    int childId=fork();
    ERROR_CHECK(childId,-1,"fork");
    if(childId)//父进程传送文件描述符
    {
        close(pipe[1]);
        int fd=open(argv[1],O_RDWR);
        ret=sendFd(pipe[0],fd);
        if(-1==ret)
        {
            wait(NULL);
            return -1;
        }
        printf("父进程 fd=%d\n",fd);
        wait(NULL);
    }else{//子进程
        close(pipe[0]);
        int fd;
        ret=recvFd(pipe[1],&fd);
        if(-1==ret)
        {
            return -1;
        }
        read(fd,buf,sizeof(buf));
        printf("子进程 fd=%d,buf=%s\n",fd,buf);
    }
    return 0;
}