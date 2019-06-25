#include <func.h>

int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1000,1<<12,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int *p=(int*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int*)-1,"shmat");
    p[0]=0;
    int semid;
    semid=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(semid,-1,"semget");
    int ret=semctl(semid,0,SETVAL,1);
    ERROR_CHECK(ret,-1,"semctl");
    struct sembuf P,V;
    P.sem_num=0;
    P.sem_op=-1;
    P.sem_flg=SEM_UNDO;
    V.sem_num=0;
    V.sem_op=1;
    V.sem_flg=SEM_UNDO;
    pid_t pid=fork();
    ERROR_CHECK(pid,-1,"fork");
    if(pid>0){//父进程
        int i;
        for(i=0;i<10000000;++i)
        {
            ++p[0];
        }
        wait(NULL);
        printf("add result=%d\n",p[0]);
        return 0;
    }else{//子进程
        int i;
        for(i=0;i<10000000;++i)
        {
            ++p[0];
        }
        exit(0);
    }
}

