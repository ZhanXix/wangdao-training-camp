#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1)
{
    printf("before sleep,%d is coming\n",signum);
    sleep(3);
    sigset_t pending;
    sigpending(&pending);//从PCB里拿出进程尚未处理的信号
    if(sigismember(&pending,SIGQUIT))
    {
        printf("SIGQUIT is pending\n");
    }else{
        printf("SIGQUIT is not pending\n");
    }
    printf("after sleep,%d is coming\n",signum);
}
int main(int argc,char *argv[])
{
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=sigFunc;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);//在二号信号的信号处理流程中阻塞三号信号
    int ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    ret=sigaction(SIGQUIT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}

