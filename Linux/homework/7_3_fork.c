//通过fork创建子进程，让父子进程都打印pid，都处于while(1),然后用ps进程查看，查看完毕，用kill命令杀掉

#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid=fork();
    ERROR_CHECK(pid,-1,"fork");
    if(pid>0)//父进程
    {
        printf("这里是父进程，pid为%d\n",getpid());
        while(1);
    }else{//子进程
        printf("这里是子进程，pid为%d，父进程pid为%d\n",getpid(),getppid());
        while(1);
    }
    return 0;
}

