#include <func.h>

int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1000,1<<20,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int *p;
    p=(int*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int*)-1,"shmat");
    if(!fork())
    {
        printf("I am child %d,%p\n",*p,p);
    }else{
        p[0]=10;
        printf("I am parent %d,%p\n",*p,p);
        wait(NULL);
    }
    return 0;
}

