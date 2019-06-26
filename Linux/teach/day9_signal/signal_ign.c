#include <func.h>

void sigFunc(int signum)
{
    printf("%d is coming\n",signum);
}
int main(int argc,char *argv[])
{
    if(signal(SIGINT,SIG_IGN)==SIG_ERR){
        perror("signal");
        return -1;
    }
    sleep(10);
    signal(SIGINT,SIG_DFL);
    while(1);
    return 0;
}

