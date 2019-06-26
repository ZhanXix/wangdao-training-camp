#include <func.h>

int main(int argc,char *argv[])
{
    int semArrId=semget(1000,2,IPC_CREAT|0600);
    ERROR_CHECK(semArrId,-1,"semget");
    unsigned short arr[2]={5,10};
    int ret=semctl(semArrId,0,SETALL,arr);//必须使用短整型数组
    ERROR_CHECK(ret,-1,"semctl");
    memset(arr,0,sizeof(arr));
    ret=semctl(semArrId,0,GETALL,arr);
    ERROR_CHECK(ret,-1,"semctl");
    printf("get val arr[1]=%d,arr[1]=%d\n",arr[0],arr[1]);
    return 0;
}

