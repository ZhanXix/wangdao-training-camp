#include <func.h>

int main(int argc,char *argv[])
{
    int semArrId=semget(1000,2,IPC_CREAT|0600);
    ERROR_CHECK(semArrId,-1,"semget");
    unsigned short arr[2]={10,0};//0号信号量的值代表仓库位置数目，1号信号量的值代表产品个数
    semctl(semArrId,0,SETALL,arr);
    struct sembuf sopp,sopv;
    if(!fork())
    {
        while(1)
        {
            sopp.sem_num=1;
            sopp.sem_op=-1;
            sopp.sem_flg=SEM_UNDO;//防止死锁内崩溃，崩溃后自动把之前所有操作回退
            sopv.sem_num=0;
            sopv.sem_op=1;
            sopv.sem_flg=SEM_UNDO;
            printf("I am child,space num=%d,productor num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            semop(semArrId,&sopp,1);//产品个数减一
            printf("consume success\n");
            semop(semArrId,&sopv,1);//仓库个数加一
            printf("I am child,space num=%d,productor num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            sleep(2);
        }
    }else{
        while(1)
        {
            sopp.sem_num=0;
            sopp.sem_op=-1;
            sopp.sem_flg=SEM_UNDO;
            sopv.sem_num=1;
            sopv.sem_op=1;
            sopv.sem_flg=SEM_UNDO;
            printf("I am parent,space num=%d,productor num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            semop(semArrId,&sopp,1);//仓库个数减一
            printf("pruduce success\n");
            semop(semArrId,&sopv,1);//产品个数加一
            printf("I am parent,space num=%d,productor num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            sleep(1); 
        }
    }
    return 0;
}

