#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1)
{
    printf("before sleep,%d is coming\n",signum);
    sleep(3);
    printf("after sleep,%d is coming\n",signum);
}
int main(int argc,char *argv[])
{
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags=SA_SIGINFO|SA_NODEFER;
    act.sa_sigaction=sigFunc;
    int ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    ret=sigaction(SIGQUIT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}

