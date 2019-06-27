//sigaction实现信号不断重入的执行效果(来回打断的效果)
#include <func.h>

void SigFunc(int SigNum,siginfo_t *pSigInfo,void *pReserved)
{
    printf("捕捉到信号%d\n",SigNum);
    sleep(3);
    printf("信号%d处理完毕\n",SigNum);
}
int main(int argc,char *argv[])
{
    struct sigaction SigAct;
    memset(&SigAct,0,sizeof(SigAct));
    SigAct.sa_sigaction=SigFunc;
    SigAct.sa_flags=SA_SIGINFO|SA_NODEFER;
    int ret;
    ret=sigaction(SIGINT,&SigAct,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    ret=sigaction(SIGQUIT,&SigAct,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}

