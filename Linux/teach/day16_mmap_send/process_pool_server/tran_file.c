#include "process_pool.h"
void signalFunc(int signum)
{
    printf("%d is coming\n",signum);
}
int tranFile(int newFd)
{
    signal(SIGPIPE,signalFunc);
    train_t train;
    int ret;
    train.dataLen=strlen(FILENAME);//发送文件名
    strcpy(train.buf,FILENAME);
    send(newFd,&train,4+train.dataLen,0);
    //发送文件大小给客户端
    struct stat buf;
    int fd=open(FILENAME,O_RDWR);
    fstat(fd,&buf);
    train.dataLen=sizeof(buf.st_size);
    memcpy(train.buf,&buf.st_size,train.dataLen);
    send(newFd,&train,4+train.dataLen,0);
    //发送文件内容
    char *pMap=(char*)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(pMap,(char*)-1,"mmap");
    off_t sendFileSize=0;
    while(buf.st_size-sendFileSize>=1000)
    {
        train.dataLen=sizeof(train.buf);
        memcpy(train.buf,pMap+sendFileSize,train.dataLen);
        ret=send(newFd,&train,4+train.dataLen,0);
        if(-1==ret)
        {
            return -1;
        }
        sendFileSize+=1000;
    }
    train.dataLen=buf.st_size-sendFileSize;
    memcpy(train.buf,pMap+sendFileSize,train.dataLen);
    ret=send(newFd,&train,4+train.dataLen,0);
    if(-1==ret)
    {
        return -1;
    }
    send(newFd,&train,4,0);
    return 0;
}
