#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1)
{
    printf("%d is coming\n",signum);
}
int main(int argc,char *argv[])
{
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags=SA_SIGINFO|SA_RESETHAND;
    act.sa_sigaction=sigFunc;
    int ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}

