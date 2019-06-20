#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(argv[1],O_TRUNC);
    ERROR_CHECK(fd,-1,"open");
    printf("fd=%d\n",fd);
    return 0;
}
