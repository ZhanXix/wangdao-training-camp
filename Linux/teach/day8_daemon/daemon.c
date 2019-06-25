#include <func.h>
void Daemon()
{
    if(fork())
    {
        exit(0);
    }
    setsid();
    chdir("/");
    umask(0);
    int i;
    for(i=0;i<3;++i)
    {
        close(i);
    }
}
int main(int argc,char *argv[])
{
    Daemon();
    while(1);
    return 0;
}

