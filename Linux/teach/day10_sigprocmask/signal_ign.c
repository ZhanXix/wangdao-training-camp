#include <func.h>

int main(int argc,char *argv[])
{
    signal(SIGINT,SIG_IGN);
    sleep(10);//关键代码
    signal(SIGINT,SIG_DFL);
    return 0;
}

