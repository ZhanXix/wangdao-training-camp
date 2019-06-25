//做一个daemon进程，让其每一分钟，在/tmp/log文件中写一句 wohenshuai
#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid=fork();
    ERROR_CHECK(pid,-1,"fork");
    if(pid>0)//父进程退出
    {
        return 0;
    }else{//使子进程成为守护进程
        setsid();
        chdir("/");
        umask(0);
        for(int i=0;i<3;++i)
        {
            close(i);
        }
        int fd=open("/tmp/log",O_RDWR|O_CREAT,0666);
        ERROR_CHECK(fd,-1,"open");
        while(1){
            sleep(60);
            write(fd,"wohenshuai\n",11);
        }
    }
}

