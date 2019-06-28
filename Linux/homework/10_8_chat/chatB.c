#include <func.h>

int main(int argc,char *argv[])
{
    int ret;
    int fdw_BB=open("chatBB.pipe",O_WRONLY);
    ERROR_CHECK(fdw_BB,-1,"open");
    int fdw_BA=open("chatBA.pipe",O_WRONLY);
    ERROR_CHECK(fdw_BA,-1,"open");
    int fd_max=fdw_BB>fdw_BA?fdw_BB+1:fdw_BA+1;
    fd_set w_set;
    char buf[256]={0};
    while(1)
    {
        system("clear");
        FD_ZERO(&w_set);
        FD_SET(fdw_BB,&w_set);
        FD_SET(fdw_BA,&w_set);
        FD_SET(STDIN_FILENO,&w_set);
        ret=select(fd_max,NULL,&w_set,NULL,NULL);
        ERROR_CHECK(ret,-1,"select");
        if(FD_ISSET(fdw_BB,&w_set)&&FD_ISSET(fdw_BA,&w_set)&&FD_ISSET(STDIN_FILENO,&w_set))
        {
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(ret)
            {
                write(fdw_BB,buf,strlen(buf)-1);
                write(fdw_BA,buf,strlen(buf)-1);
            }else{
                break;
            }
        }
    }
    close(fdw_BB);
    close(fdw_BA);
    return 0;
}

