#define _GNU_SOURCE 
#include "func.h"

int Recv_File_Splice(int socketFd,off_t fileSize,int fileFd)
{
    int ret,spliceRet;
    int fds[2];
    pipe(fds);
    off_t downloadSize=0,lastloadSize=0,slice=fileSize/1000;
    while(downloadSize<fileSize)
    {
        spliceRet=splice(socketFd,NULL,fds[1],NULL,4096,SPLICE_F_MOVE|SPLICE_F_MORE);
        ERROR_CHECK(spliceRet,-1,"splice")
        ret=splice(fds[0],NULL,fileFd,NULL,spliceRet,SPLICE_F_MOVE|SPLICE_F_MORE);
        ERROR_CHECK(ret,-1,"splice");
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

/* splice()  
 moves  data  between  two  file  descriptors  without copying
 between kernel address space and user address space.  It  transfers  up
 to  len  bytes  of  data  from  the  file  descriptor fd_in to the file
 descriptor fd_out, where one of the file descriptors must  refer  to  a
 pipe.
 */