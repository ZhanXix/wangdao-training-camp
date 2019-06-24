#include <func.h>

int main(int argc,char *argv[])
{
    if(!fork())
    {
        printf("I am child,pid=%d\n",getpid());
        return 1;
    }else{
        int status;
        pid_t pid=wait(&status);
        printf("I am parent,child pid=%d\n",pid);
        if(WIFEXITED(status))
        {
            printf("exit code=%d\n",WEXITSTATUS(status));
        }else{
            printf("child crash\n");
        }
        return 0;
    }
}

