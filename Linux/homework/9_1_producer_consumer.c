//使用计数信号量，实现生产者消费者模式
#include <func.h>

int main(int argc,char *argv[])
{
    int semid=semget(1000,2,IPC_CREAT|0600);//[0]仓库空余，[1]现有货物
    ERROR_CHECK(semid,-1,"semget");
    unsigned short semaphore_arr[2]={15,0};
    int ret=semctl(semid,0,SETALL,semaphore_arr);
    ERROR_CHECK(ret,-1,"semctl");
    struct sembuf sopP,sopV;
    pid_t pid=fork();
    ERROR_CHECK(pid,-1,"fork");
    if(pid>0)//生产者
    {
        while(1)
        {
            sopP.sem_num=0;
            sopP.sem_op=-1;
            sopP.sem_flg=SEM_UNDO;
            sopV.sem_num=1;
            sopV.sem_op=1;
            sopV.sem_flg=SEM_UNDO;
            printf("生产者--当前仓库空余%d个位置，现有货物%d个\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            semop(semid,&sopP,1);
            printf("生产完成，货物数+1！\n");
            semop(semid,&sopV,1);
            printf("生产者--当前仓库空余%d个位置，现有货物%d个\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            sleep(2);
        }
    }else{//消费者
        while(1)
        {
            sopP.sem_num=1;
            sopP.sem_op=-1;
            sopP.sem_flg=SEM_UNDO;
            sopV.sem_num=0;
            sopV.sem_op=1;
            sopV.sem_flg=SEM_UNDO;
            printf("消费者--当前仓库空余%d个位置，现有货物%d个\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            semop(semid,&sopP,1);
            printf("卖出一件货物！\n");
            semop(semid,&sopV,1);
            printf("消费者--当前仓库空余%d个位置，现有货物%d个\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            sleep(3);
        }
    }
    return 0;
}

