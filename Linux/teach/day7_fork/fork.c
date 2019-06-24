#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid;
    pid=fork();
    if(0==pid)
    {
        printf("I am child,my pid=%d,my ppid=%d\n",getpid(),getppid());
    }
    else
    {
        printf("I am parent,my pid=%d,my childpid=%d\n",getpid(),pid);
        sleep(1);
    }
    return 0;
}

