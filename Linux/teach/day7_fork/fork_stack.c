#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid;
    int iStack=10;
    pid=fork();
    if(0==pid)
    {
        printf("I am child,my pid=%d,my ppid=%d,iStack=%d %p\n",getpid(),getppid(),iStack,&iStack);
    }
    else
    {
        printf("I am parent,my pid=%d,my childpid=%d,iStack=%d %p\n",getpid(),pid,iStack,&iStack);
        iStack=5;
        printf("I am parent,after modify iStack=%d %p\n",iStack,&iStack);
        sleep(1);
    }
    return 0;
}

