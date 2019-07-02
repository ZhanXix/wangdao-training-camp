#include "func.h"
int setNonBlock(int fd)
{
    int status;
    status=fcntl(fd,F_GETFL);
    status=status|O_NONBLOCK;
    fcntl(fd,F_SETFL,status);
    return 0;
}
int main()
{
    setNonBlock(0);
    char buf[128]={0};
    int ret;
    sleep(5);
    ret=read(0,buf,sizeof(buf));
    printf("ret=%d,errno=%d,buf=%s\n",ret,errno,buf);
    return 0;
}