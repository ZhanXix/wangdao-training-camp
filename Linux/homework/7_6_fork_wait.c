//通过fork创建子进程，然后父进程通过wait回收，同时拿到子进程的返回值
#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid=fork();
    ERROR_CHECK(pid,-1,"fork");
    int state;
    if(pid>0)//父进程
    {
        printf("这里是父进程，pid为%d\n",getpid());
        sleep(1);
        int state;
        int cpid=wait(&state);
        if(WIFEXITED(state))
        {
            printf("已成功回收子进程，子进程pid为%d,返回值为%d\n",cpid,WEXITSTATUS(state));
        }else{
            printf("未成功回收子进程！\n");
        }
        return 0;
    }else{//子进程
        printf("这里是子进程，pid为%d，父进程pid为%d\n",getpid(),getppid());
        return 1;
    }
}

