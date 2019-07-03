#include "func.h"

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    struct iovec iov[2];
    char buf1[10]="hello";
    iov[0].iov_base=buf1;
    iov[0].iov_len=5;
    char buf2[10]="world";
    iov[1].iov_base=buf2;
    iov[1].iov_len=5;
    writev(fd,iov,2);
    close(fd);
    return 0;
}