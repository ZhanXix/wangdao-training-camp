#include <func.h>

int main(int argc,char *agrv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(agrv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int ret=lseek(fd,1024,SEEK_SET);
    printf("pos=%d\n",ret);
    char c='H';
    write(fd,&c,sizeof(char));
    close(fd);
    return 0;
}
