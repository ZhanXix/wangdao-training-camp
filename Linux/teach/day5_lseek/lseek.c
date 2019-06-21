#include <func.h>

int main(int argc,char *agrv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(agrv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int ret=lseek(fd,5,SEEK_SET);
    printf("pos=%d\n",ret);
    char buf[128];
    read(fd,buf,sizeof(buf));
    printf("%s",buf);
    close(fd);
    return 0;

}
