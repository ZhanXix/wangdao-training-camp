#include "head.h"
void signalFunc(int signum)
{
    printf("%d is coming\n",signum);
}
typedef struct {
    int dataLen;
    char buf[1000];
}train_t;
#define FILENAME "file"
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
    ret=sendfile(newFd,fd,NULL,buf.st_size);
	printf("sendfile ret=%d\n",ret);
    ERROR_CHECK(ret,-1,"sendfile");
    return 0;
}
