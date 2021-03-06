//两个进程对一个共享内存各加1000万，查看最后结果
#include <func.h>

int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1000,1<<12,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int *p=(int*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int*)-1,"shmat");
    p[0]=0;
    pid_t pid=fork();
    ERROR_CHECK(pid,-1,"fork");
    if(pid>0){//父进程
        int i;
        for(i=0;i<10000000;++i)
        {
            ++p[0];
        }
        wait(NULL);
        printf("add result=%d\n",p[0]);
        return 0;
    }else{//子进程
        int i;
        for(i=0;i<10000000;++i)
        {
            ++p[0];
        }
        exit(0);
    }
}

