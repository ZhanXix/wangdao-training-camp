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
    fd_set rdset;
    char buf[1024];
    while (1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(newFd, &rdset);
        ret = select(newFd+1, &rdset, NULL, NULL, NULL);
        if (ret > 0)
        {
            if (FD_ISSET(STDIN_FILENO, &rdset))
            {
                bzero(buf, sizeof(buf));
                ret = read(STDIN_FILENO, buf, sizeof(buf));
                if (0 == ret)
                {
                    printf("byebye\n");
                    break;
                }
                send(newFd, buf, strlen(buf) - 1, 0);
            }
            if (FD_ISSET(newFd, &rdset))
            {
                bzero(buf, sizeof(buf));
                ret = recv(newFd, buf, sizeof(buf), 0);
                if (0 == ret)
                {
                    printf("byebye\n");
                    break;
                }
                printf("%s\n", buf);
            }
        }
    }
    return 0;
}
