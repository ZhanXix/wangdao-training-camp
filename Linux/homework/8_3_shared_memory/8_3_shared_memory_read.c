#include <func.h>

int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1000,1<<12,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    char *p=(char*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    printf("已从共享内存中读取数据：%s\n",p);
    int ret=shmctl(shmid,IPC_RMID,NULL);
    ERROR_CHECK(ret,-1,"shmctl");
    return 0;
}

