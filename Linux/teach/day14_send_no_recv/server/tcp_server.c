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
    //char buf[10];
    //read(0,buf,sizeof(buf));
    int buf; 
    scanf("%d",&buf);
    printf("%d\n",buf);
    return 0;
}
