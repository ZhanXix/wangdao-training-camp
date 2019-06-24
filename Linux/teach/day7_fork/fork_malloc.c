#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid;
    char *pMalloc=(char*)malloc(20);
    strcpy(pMalloc,"hello");
    pid=fork();
    if(0==pid)
    {
        printf("I am child,my pid=%d,my ppid=%d,p=%s %p\n",getpid(),getppid(),pMalloc,pMalloc);
    }
    else
    {
        printf("I am parent,my pid=%d,my childpid=%d,p=%s %p\n",getpid(),pid,pMalloc,pMalloc);
        pMalloc[0]='H';
        printf("I am parent,after modify p=%s %p\n",pMalloc,pMalloc);
        sleep(1);
    }
    return 0;
}

