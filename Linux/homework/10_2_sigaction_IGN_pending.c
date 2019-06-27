//sigaction实现2号信号，屏蔽3号信号的执行效果，同时在2号信号的信号处理流程中，判断3号信号是否被挂起
#include <func.h>

void SigFunc(int SigNum,siginfo_t *pSigInfo,void *pReserved)
{
    printf("捕捉到信号%d\n",SigNum);
    sleep(3);
    sigset_t SigSet;
    sigpending(&SigSet);
    if(sigismember(&SigSet,SIGQUIT))
    {
        printf("信号3正在阻塞\n");
    }else{
        printf("信号3未被阻塞\n");
    }
    printf("信号%d处理完毕\n",SigNum);
}
int main(int argc,char *argv[])
{
    signal(SIGQUIT,SIG_IGN);
    struct sigaction SigAct;
    memset(&SigAct,0,sizeof(SigAct));
    SigAct.sa_sigaction=SigFunc;
    SigAct.sa_flags=SA_SIGINFO;
    sigemptyset(&SigAct.sa_mask);
    sigaddset(&SigAct.sa_mask,SIGQUIT);
    int ret;
    ret=sigaction(SIGINT,&SigAct,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    ret=sigaction(SIGQUIT,&SigAct,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}

