#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    printf("fd=%d\n",fd);
    int ret=write(fd,&fd,sizeof(int));
    printf("write count=%d\n",ret);
    close(fd);
    return 0;
}
