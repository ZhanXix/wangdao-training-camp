#include <func.h>
//一个物理页的大小是4k
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);//这里的权限要大于等于mmap设的权限
    ERROR_CHECK(fd,-1,"open");
    char *p=(char*)mmap(NULL,5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    //映射的空间长度必须是4k的倍数，这里写5他还是会分4k
    //mmap不能改变文件大小
    ERROR_CHECK(p,(char*)-1,"mmap");
    printf("%s\n",p);
    strcpy(p,"how");    //strcpy会放结束符'\0'
    int ret=munmap(p,5);
    ERROR_CHECK(ret,-1,"munmap");
    close(fd);
    return 0;
            
}
