#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    printf("uid=%d,gid=%d,euid=%d,egid=%d\n",getuid(),getgid(),geteuid(),getegid());
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    write(fd,"hello\n",6);
    close(fd);
    return 0;
}

