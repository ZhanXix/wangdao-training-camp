//luke用户编写一个程序，用来往file文件中写入内容hello，然后编译后，增加s权限，这时xiognda执行该程序，能够往file文件中写入hello
#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR|O_CREAT,0666);
    write(fd,"hello\n",6);
    return 0;
}

