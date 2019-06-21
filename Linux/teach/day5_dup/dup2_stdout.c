#include <func.h>
//重定向标准输出
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd,fd1;
    fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    printf("\n");
    dup2(STDOUT_FILENO,100);//将标准输出存到100
    fd1=dup2(fd,STDOUT_FILENO);//文件描述符的复制,后面写多少就返回多少
    printf("fd1=%d\n",fd1);//不会输出到屏幕上，因为关闭了标准输出1
    close(fd);//是否close没有关系
    printf("you can not see me.\n");
    dup2(100,STDOUT_FILENO);//重新开启标准输出
    printf("you can see me.\n");
    close(fd1);
    return 0;
}

