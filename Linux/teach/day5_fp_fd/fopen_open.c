#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    FILE *fp;
    fp=fopen(argv[1],"rb+");
    ERROR_CHECK(fp,NULL,"fopen");
    int fd=fileno(fp);
    printf("fd=%d\n",fd);
    char buf[128]={0};
    read(fd,buf,sizeof(buf));
    printf("buf=%s",buf);
    return 0;
}

