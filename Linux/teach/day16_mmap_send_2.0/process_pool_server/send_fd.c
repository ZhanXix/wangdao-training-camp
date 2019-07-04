#include "process_pool.h"
int sendFd(int pipeFd,int fd)
{
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    struct iovec iov[2];
    char buf1[10]="hello";
    iov[0].iov_base=buf1;
    iov[0].iov_len=5;
    char buf2[10]="world";
    iov[1].iov_base=buf2;
    iov[1].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    struct cmsghdr *cmsg;
    int cmsgLen=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,cmsgLen);
    cmsg->cmsg_len=cmsgLen;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    *(int*)CMSG_DATA(cmsg)=fd;//把要传递的描述符告诉内核
    msg.msg_control=cmsg;
    msg.msg_controllen=cmsgLen;
    int ret;
    ret=sendmsg(pipeFd,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}
int recvFd(int pipeFd,int *fd)
{
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    struct iovec iov[2];
    char buf1[10]="hello";
    iov[0].iov_base=buf1;
    iov[0].iov_len=5;
    char buf2[10]="world";
    iov[1].iov_base=buf2;
    iov[1].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    struct cmsghdr *cmsg;
    int cmsgLen=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,cmsgLen);
    cmsg->cmsg_len=cmsgLen;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    msg.msg_control=cmsg;
    msg.msg_controllen=cmsgLen;
    int ret;
    ret=recvmsg(pipeFd,&msg,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    *fd=*(int*)CMSG_DATA(cmsg);
    return 0;
}