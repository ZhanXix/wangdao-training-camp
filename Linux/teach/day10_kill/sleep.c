#include <func.h>
void sigFunc(int signum)
{}
int main(int argc,char *argv[])
{
    signal(SIGALRM,sigFunc);
    alarm(3);
    pause();
    return 0;
}

