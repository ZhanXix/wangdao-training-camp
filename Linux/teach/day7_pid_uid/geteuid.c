#include <func.h>

int main(int argc,char *argv[])
{
    printf("uid=%d,gid=%d,euid=%d,egid=%d\n",getuid(),getgid(),geteuid(),getegid());
    return 0;
}

