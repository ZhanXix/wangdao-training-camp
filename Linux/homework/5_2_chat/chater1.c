#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int fdr,fdw;
    fdw=open(argv[1],O_WRONLY);//只写方式打开管道文件1
    ERROR_CHECK(fdw,-1,"open");
    fdr=open(argv[2],O_RDONLY);//只读方式打开管道文件2
    ERROR_CHECK(fdr,-1,"open");
    fd_set rd_set,wr_set;
    int ret;
    char buf[128];
    while(1)
    {
        int fdmax=fdr>fdw?fdr+1:fdw+1;
        FD_ZERO(&rd_set);
        FD_ZERO(&wr_set);
        FD_SET(fdr,&rd_set);
        FD_SET(STDIN_FILENO,&rd_set);
        FD_SET(fdw,&wr_set);
        ret=select(fdmax,&rd_set,&wr_set,NULL,NULL);
        ERROR_CHECK(ret,-1,"select");
        if(FD_ISSET(STDIN_FILENO,&rd_set)&&FD_ISSET(fdw,&wr_set))
        {
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(ret)
            {
                write(fdw,buf,strlen(buf)-1);
            }
            else
            {
                printf("---对话主动终止---\n");
                break;
            }
        }
        if(FD_ISSET(fdr,&rd_set))
        {
            bzero(buf,sizeof(buf));
            ret=read(fdr,buf,sizeof(buf));
            if(ret)
            {
                printf("%s\n",buf);
            }
            else
            {
                printf("---对话已终止---\n");
                break;
            }
        }
    }        
    close(fdr);
    close(fdw);
    return 0;
}

