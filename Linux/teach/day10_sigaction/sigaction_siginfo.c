#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1)
{
    printf("%d is coming,send pid=%d,send uid=%d\n",signum,p->si_pid,p->si_uid);
}
int main(int argc,char *argv[])
{
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=sigFunc;
    int ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}

