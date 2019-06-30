#include "func.h"
struct msgbuf{
    char type;
    char mtext[255];
}Msgbuf_t;
int main()
{
    system("clear");
    //设置共享内存 A-A1
    int shmAA=shmget(1000,sizeof(Msgbuf_t),IPC_CREAT|0666);
    ERROR_CHECK(shmAA,-1,"shmget");
    struct msgbuf *pAA=(struct msgbuf*)shmat(shmAA,NULL,0);
    ERROR_CHECK(pAA,(struct msgbuf*)-1,"shmat");
    //信号量
    int semAA=semget(1000,2,IPC_CREAT|0600);
    ERROR_CHECK(semAA,-1,"semget");
    struct sembuf sopp,sopv;
    sopp.sem_num=1;
    sopp.sem_op=-1;
    sopp.sem_flg=SEM_UNDO;
    sopv.sem_num=0;
    sopv.sem_op=1;
    sopv.sem_flg=SEM_UNDO;
    //读内存
    while(1)
    {
        semop(semAA,&sopp,1);
        if('A'==pAA->type){
            printf("%77s",pAA->mtext);
            pAA->type='0';
        }else if('B'==pAA->type){
            printf("%s",pAA->mtext);
            pAA->type='0';
        }else if('E'==pAA->type){
            printf("---------------对话主动中止---------------\n");
            break;
        }else if('F'==pAA->type){
            printf("----------------对话已中止----------------\n");
            break;
        }else{
            printf("内存读取错误!%c\n",pAA->type);
        }
        semop(semAA,&sopv,1);
    }
}