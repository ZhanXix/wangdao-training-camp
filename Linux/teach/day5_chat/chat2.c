#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int fdw=open(argv[1],O_WRONLY);//1pipe
    int fdr=open(argv[2],O_RDONLY);//2pipe
    printf("I am chat2 fdr=%d,fdw=%d\n",fdr,fdw);
    char buf[128]={0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        read(fdr,buf,sizeof(buf));
        printf("%s\n",buf); 
        memset(buf,0,sizeof(buf));
        read(STDIN_FILENO,buf,sizeof(buf));
        write(fdw,buf,strlen(buf)-1);
    }
    return 0;
}

