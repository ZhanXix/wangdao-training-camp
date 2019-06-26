#include <func.h>

int main(int argc,char *argv[])
{
    int semArrId=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(semArrId,-1,"semget");
    int ret=semctl(semArrId,0,SETVAL,1);
    ERROR_CHECK(ret,-1,"semctl");
    ret=semctl(semArrId,0,GETVAL);
    printf("get sem val = %d\n",ret);
    ret=semctl(semArrId,0,IPC_RMID);
    ERROR_CHECK(ret,-1,"semctl");
    return 0;
}

