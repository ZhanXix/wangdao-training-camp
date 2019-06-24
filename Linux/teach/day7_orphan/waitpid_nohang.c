#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid;
    pid=fork();
    if(!pid)
    {
        printf("I am child,pid=%d\n",getpid());
        return 1;
    }else{
        int status;
        sleep(1);
        pid_t ChildPid=waitpid(pid,&status,WNOHANG);
        printf("I am parent,child pid=%d\n",ChildPid);
        if(ChildPid>0)
        {
            if(WIFEXITED(status))
            {
                printf("exit code=%d\n",WEXITSTATUS(status));
            }else{
                printf("child crash\n");
            }
        }
        return 0;
    }
}

