#include <func.h>
//重定向标准输出
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd,fd1;
    fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    printf("\n");
    close(1);
    fd1=dup(fd);//文件描述符的复制
    printf("fd1=%d\n",fd1);//不会输出到屏幕上
    close(fd);
    printf("you can not see me.\n");
    close(fd1);
    return 0;
}

