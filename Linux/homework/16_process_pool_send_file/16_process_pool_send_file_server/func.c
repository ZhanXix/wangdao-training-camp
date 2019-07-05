#include "process_pool.h"

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