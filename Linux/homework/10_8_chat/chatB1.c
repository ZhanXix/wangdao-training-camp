#include <func.h>

int main(int argc,char *argv[])
{
    system("clear");
    int ret;
    int fdr_BB=open("chatBB.pipe",O_RDONLY);
    ERROR_CHECK(fdr_BB,-1,"open");
    int fdr_AB=open("chatAB.pipe",O_RDONLY);
    ERROR_CHECK(fdr_AB,-1,"open");
    int fd_max=fdr_BB>fdr_AB?fdr_BB+1:fdr_AB+1;
    fd_set r_set;
    char buf[256]={0};
    while(1)
    {
        FD_ZERO(&r_set);
        FD_SET(fdr_BB,&r_set);
        FD_SET(fdr_AB,&r_set);
        ret=select(fd_max,&r_set,NULL,NULL,NULL);
        ERROR_CHECK(ret,-1,"select");
        if(FD_ISSET(fdr_BB,&r_set))
        {
            bzero(buf,sizeof(buf));
            ret=read(fdr_BB,buf,sizeof(buf));
            if(ret)
            {
                printf("%76s\n",buf);
            }else{
                printf("---对话主动终止---\n");
                break;
            }
        }
        if(FD_ISSET(fdr_AB,&r_set))
        {
            bzero(buf,sizeof(buf));
            ret=read(fdr_AB,buf,sizeof(buf));
            if(ret)
            {
                printf("%s\n",buf);
            }else{
                printf("---对话已终止---\n");
                break;
            }
        }
    }
    close(fdr_BB);
    close(fdr_AB);
    return 0;
}

