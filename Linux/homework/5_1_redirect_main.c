//将标准输出重定向到log1文件，标准错误输出重定向到log2文件
#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int fd1,fd2;
    fd1=open(argv[1],O_RDWR);
    ERROR_CHECK(fd1,-1,"open");
    fd2=open(argv[2],O_RDWR);
    ERROR_CHECK(fd2,-1,"open");
    fflush(stdout);
    int ret;
    ret=dup2(fd1,STDOUT_FILENO);//重定向标准输出
    ERROR_CHECK(ret,-1,"dup2");
    ret=dup2(fd2,STDERR_FILENO);//重定向标准错误输出
    ERROR_CHECK(ret,-1,"dup2");
    printf("This is stdout.\n");
    FILE *fp=fopen("unexist","r+");
    perror("This is stderr,fopen");
    close(fd1);
    close(fd2);
    return 0;
}

