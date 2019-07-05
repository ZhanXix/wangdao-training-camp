#include "func.h"

int Recv_Circle(int socketFd,off_t fileSize,void* pFile)
{
    char *p=(char*)pFile;
    int ret;
    off_t downloadSize=0,lastloadSize=0,slice=fileSize/1000;
    while(downloadSize<fileSize)
    {
        ret=recv(socketFd,p+downloadSize,fileSize-downloadSize,0);
        if(0==ret)
        {
            return -1;
        }
        downloadSize+=ret;
        if(downloadSize-lastloadSize>slice)
        {
            printf("已下载：%5.2f%%\r",(float)downloadSize/fileSize);
            fflush(stdout);
            lastloadSize=downloadSize;
        }
    }
    printf("已下载：100.00%%\n");
    return 0;
}