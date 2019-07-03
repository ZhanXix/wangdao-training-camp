#include "func.h"
int tcpInit(int *, char *, char *);
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    int socketFd;
    int ret;
    ret=tcpInit(&socketFd, argv[1], argv[2]);
    if(-1==ret)
    {
        return -1;
    }
    int newFd = accept(socketFd, NULL, NULL);
    printf("newFd=%d\n",newFd);
    char buf[10]={0};
    ret=recv(newFd,buf,5,MSG_DONTWAIT);
    printf("ret=%d,buf=%s\n",ret,buf);
    close(newFd);
    close(socketFd);
    return 0;
}
