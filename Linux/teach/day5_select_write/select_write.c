#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fdr=open(argv[1],O_RDWR);
    int fdw=open(argv[1],O_RDWR);
    fd_set rdset,wrset;
    int ret;
    char buf[128]={0};
    while(1)
    {
        FD_ZERO(&rdset);
        FD_ZERO(&wrset);
        FD_SET(fdr,&rdset);
        FD_SET(fdw,&wrset);
        ret=select(fdw+1,&rdset,&wrset,NULL,NULL);
        if(FD_ISSET(fdr,&rdset))
        {
            bzero(buf,sizeof(buf));
            read(fdr,buf,sizeof(buf));
            puts(buf);
            sleep(1);
        }
        if(FD_ISSET(fdw,&wrset))
        {
            write(fdw,"hello world",11);
            sleep(2);
        }
    }
    return 0;
}

