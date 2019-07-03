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
    recv(newFd,buf,5,MSG_PEEK);
    /* MSG_PEEK 
     * This flag causes the receive operation to return data  from  the
     * beginning  of  the receive queue without removing that data from
     * the queue.  Thus, a subsequent receive call will return the same
     * data.
     */
    puts(buf);
    recv(newFd,buf,5,0);
    puts(buf);
    close(newFd);
    close(socketFd);
    return 0;
}
