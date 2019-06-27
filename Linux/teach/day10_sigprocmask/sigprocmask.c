#include <func.h>

int main(int argc,char *argv[])
{
    sigset_t procMask;
    sigemptyset(&procMask);
    sigaddset(&procMask,SIGINT);
    int ret;
    ret=sigprocmask(SIG_BLOCK,&procMask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    sleep(10);
    ret=sigprocmask(SIG_UNBLOCK,&procMask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    return 0;
}

