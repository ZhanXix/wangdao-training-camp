//新建共享内存，连接，然后往共享内存写入How are you,然后另外一个进程连接共享内存，读取数据并打印显示,删除共享内存
#include <func.h>

int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1000,1<<12,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    char *p=(char*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    strcpy(p,"How are you");
    while(1);
    return 0;
}

