#include <func.h>

int main(int argc,char *argv[])
{
    if(!fork())
    {
        printf("I am child,pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),getpgid(0));
        setpgid(0,0);//自己成立一个新的进程组
        printf("I am child,pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),getpgid(0));
        while(1);
        return 0;
    }else{
        printf("I am parent,pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),getpgid(0));
        wait(NULL);
        return 0;
    }
}

