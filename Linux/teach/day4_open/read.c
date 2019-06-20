#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    printf("fd=%d\n",fd);
    char buf[128]={0};
    int ret=read(fd,buf,sizeof(buf));
    printf("buf=%s,ret=%d\n",buf,ret);
    close(fd);
    return 0;
}
