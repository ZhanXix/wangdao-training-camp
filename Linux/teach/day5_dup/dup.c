#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd,fd1;
    fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    fd1=dup(fd);//文件描述符的复制
    printf("fd1=%d\n",fd1);
    close(fd);
    char buf[128]={0};
    read(fd1,buf,sizeof(buf));
    printf("buf=%s",buf);
    close(fd1);
    return 0;
}

