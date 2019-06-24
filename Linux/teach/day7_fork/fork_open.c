#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    pid_t pid;
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    pid=fork();
    if(0==pid)
    {
        printf("I am child,my pid=%d,my ppid=%d\n",getpid(),getppid());
        write(fd,"niuniu",6);
    }
    else
    {
        printf("I am parent,my pid=%d,my childpid=%d\n",getpid(),pid);
        lseek(fd,5,SEEK_SET);
        printf("I am parent,seek success\n");
        sleep(1);
    }
    return 0;
}

