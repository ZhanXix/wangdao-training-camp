//使用shm实现大页共享内存
#include <func.h>
#define SHM_HUGE_2MB 1<<21
int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1000,SHM_HUGE_2MB,IPC_CREAT|0600|SHM_HUGETLB|SHM_HUGE_2MB);
    ERROR_CHECK(shmid,-1,"shmget");
    char *p=(char*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    pid_t pid=fork();
    ERROR_CHECK(pid,-1,"fork");
    if(pid>0){
        sleep(1);
        printf("父进程从大页共享内存读取数据：%s\n",p);
        wait(NULL);
    }else{
        printf("子进程写入数据...\n");
        strcpy(p,"Hello father^-^");
        exit(0);
    }
    return 0;
}

