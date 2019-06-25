#include <func.h>

int main(int argc,char *argv[])
{
    if(!fork())
    {
        printf("I am child,pid=%d,ppid=%d,pgid=%d,sid=%d\n",getpid(),getppid(),getpgid(0),getsid(0));
        setsid();    
        printf("I am child,pid=%d,ppid=%d,pgid=%d,sid=%d\n",getpid(),getppid(),getpgid(0),getsid(0));
        while(1);
        return 0;
    }else{
        printf("I am parent,pid=%d,ppid=%d,pgid=%d,sid=%d\n",getpid(),getppid(),getpgid(0),getsid(0));
        wait(NULL);
        return 0;
    }
}

