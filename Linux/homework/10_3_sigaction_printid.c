//通过sigaction，打印发送信号的发送者的pid和uid
#include <func.h>

void SigFunc(int SigNum,siginfo_t *pSigInfo,void *pReserved)
{
    printf("捕捉到信号%d，发送者pid为%d，uid为%d\n",SigNum,pSigInfo->si_pid,pSigInfo->si_uid);
}
int main(int argc,char *argv[])
{
    struct sigaction SigAct;
    memset(&SigAct,0,sizeof(SigAct));
    SigAct.sa_sigaction=SigFunc;
    SigAct.sa_flags=SA_SIGINFO;
    int ret;
    ret=sigaction(SIGINT,&SigAct,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    ret=sigaction(SIGQUIT,&SigAct,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}

