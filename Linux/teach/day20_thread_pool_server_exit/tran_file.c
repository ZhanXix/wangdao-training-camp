#include "factory.h"

#define FILENAME "file"
int tranFile(int newFd)
{
    train_t train;
    int ret;
    //发送文件名
    train.dataLen=strlen(FILENAME);
    strcpy(train.buf,FILENAME);
    printf("send\n");
    ret=send(newFd,&train,4+train.dataLen,0);
    printf("send ret=%d\n",ret);
    ERROR_CHECK(ret,-1,"send");
    int fd=open(FILENAME,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    /* printf("send filename done\n"); */
    //文件大小
    struct stat buf;
    fstat(fd,&buf);
    train.dataLen=sizeof(buf.st_size);
    memcpy(train.buf,&buf.st_size,train.dataLen);
    ret=send(newFd,&train,4+train.dataLen,0);
    ERROR_CHECK(ret,-1,"send");
    /* printf("send filesize done\n"); */
    //发文件内容
    while((train.dataLen = read(fd,train.buf,1000)))
    {
        ret = send(newFd,&train,4+train.dataLen,0);
        ERROR_CHECK(ret,-1,"send");
    }
    //发送结束标志
    train.dataLen = 0;
    ret=send(newFd,&train,4,0);
    ERROR_CHECK(ret,-1,"send");
    close(fd);
    return 0;
}
