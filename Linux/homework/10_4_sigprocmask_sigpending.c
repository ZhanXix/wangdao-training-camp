//通过sigprocmask阻塞2号信号，睡眠5秒后，解除阻塞，2号信号得到执行；在睡眠后，解除阻塞之前，通过sigpending检测是否有信号挂起
#include <func.h>

int main(int argc,char *argv[])
{
    sigset_t SigSet;
    sigemptyset(&SigSet);
    sigaddset(&SigSet,SIGINT);
    int ret;
    ret=sigprocmask(SIG_BLOCK,&SigSet,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask"); 
    sleep(5);
    sigset_t checkSet;
    sigpending(&checkSet);
    if(sigismember(&checkSet,SIGINT))
    {
        printf("信号2正在阻塞\n");
    }else{
        printf("信号2未被阻塞\n");
    }
    ret=sigprocmask(SIG_UNBLOCK,&SigSet,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask"); 
    return 0;
}

