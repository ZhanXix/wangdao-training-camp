#include <func.h>
#define MAP_HUGE_2MB 1<<21
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR|O_CREAT);
    ERROR_CHECK(fd,-1,"open");
    int ret=ftruncate(fd,MAP_HUGE_2MB);
    ERROR_CHECK(ret,-1,"ftruncate");
    char *p=(char*)mmap(0,MAP_HUGE_2MB,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,(char*)-1,"mmap");
    strcpy(p,"hello");
    sleep(20);
    ret=munmap(p,MAP_HUGE_2MB);
    ERROR_CHECK(ret,-1,"munmap");
    return 0;
}
//首先要把文件系统挂载为大页形式的文件系统
//sudo mount none ~/Documents/day8/shm/huge -t hugetlbfs
//查看内存信息
//cat /proc/meminfo 
