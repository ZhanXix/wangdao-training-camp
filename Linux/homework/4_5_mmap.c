//新建一个文件，里边内容为hello，通过mmap映射该文件后，修改hello为world，然后解除映射

#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd,ret;
    fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0755);
    ERROR_CHECK(fd,-1,"open");
    ret=write(fd,"hello",5);
    ERROR_CHECK(ret,-1,"write");
    char *p;
    p=(char*)mmap(NULL,5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,(char*)-1,"mmap");
    strcpy(p,"world");
    p[5]=0;
    printf("%s\n",p);
    munmap(p,5);
    close(fd);
    return 0;
}
