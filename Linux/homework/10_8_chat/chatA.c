//做4个窗口，模拟聊天界面
#include <func.h>

int main(int argc,char *argv[])
{
    int ret;
    //mkfifo("chatAA.pipe",0666);
    //mkfifo("chatAB.pipe",0666);
    //mkfifo("chatBA.pipe",0666);
    //mkfifo("chatBB.pipe",0666);
    int fdw_AA=open("chatAA.pipe",O_WRONLY);
    ERROR_CHECK(fdw_AA,-1,"open");
    int fdw_AB=open("chatAB.pipe",O_WRONLY);
    ERROR_CHECK(fdw_AB,-1,"open");
    int fd_max=fdw_AA>fdw_AB?fdw_AA+1:fdw_AB+1;
    fd_set w_set;
    char buf[256]={0};
    while(1)
    {
        system("clear");
        FD_ZERO(&w_set);
        FD_SET(fdw_AA,&w_set);
        FD_SET(fdw_AB,&w_set);
        FD_SET(STDIN_FILENO,&w_set);
        ret=select(fd_max,NULL,&w_set,NULL,NULL);
        ERROR_CHECK(ret,-1,"select");
        if(FD_ISSET(fdw_AA,&w_set)&&FD_ISSET(fdw_AB,&w_set)&&FD_ISSET(STDIN_FILENO,&w_set))
        {
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(ret)
            {
                write(fdw_AA,buf,strlen(buf)-1);
                write(fdw_AB,buf,strlen(buf)-1);
            }else{
                break;
            }
        }
    }
    close(fdw_AA);
    close(fdw_AB);
    return 0;
}

