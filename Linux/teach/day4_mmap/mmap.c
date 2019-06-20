#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    printf("fd=%d\n",fd);
    char *p;
    p=(char*)mmap(NULL,5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);//NULL:系统自动填堆内存起始地址
    ERROR_CHECK(p,(char*)-1,"mmap");
    p[5]=0;
    printf("%s\n",p);
    p[0]='H';
    munmap(p,5);//解除映射
    close(fd);
    return 0;
}
