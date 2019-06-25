//创建一个无名管道，fork子进程，然后子进程向管道写端写Hello，父进程接收数据并打印
#include <func.h>

int main(int argc,char *argv[])
{
    int nameless_pipe[2];
    pipe(nameless_pipe);//[0]读端，[1]写端
    pid_t pid=fork();
    ERROR_CHECK(pid,-1,"fork");
    if(pid>0)//父进程
    {
        close(nameless_pipe[1]);
        char buf[128]={0};
        read(nameless_pipe[0],buf,sizeof(buf));
        printf("父进程接收数据：%s\n",buf);
        wait(NULL);
    }else{//子进程
        close(nameless_pipe[0]);
        write(nameless_pipe[1],"Hello",5);
        exit(0);
    }
    return 0;
}

