//使用mmap实现共享内存，大页共享内存
#include <func.h>
#define MAP_HUGE_2MB 1<<21
int main(int argc,char *argv[])
{
    int fd=open("hugepage/share",O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    int ret=lseek(fd,MAP_HUGE_2MB,SEEK_SET);
    ERROR_CHECK(ret,-1,"lseek");
    char *p=(char*)mmap(NULL,MAP_HUGE_2MB,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,(char*)-1,"mmap");
    pid_t pid=fork();
    if(pid>0)
    {
        sleep(1);
        printf("父进程从大页共享内存读取数据：%s\n",p);
        wait(NULL);
        ret=munmap(p,MAP_HUGE_2MB);
        ERROR_CHECK(ret,-1,"munmap");
        return 0;
    }else{
        strcpy(p,"Hello world!");
        exit(0);
    }
}

