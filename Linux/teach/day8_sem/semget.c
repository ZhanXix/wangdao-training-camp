#include <func.h>

int main(int argc,char *argv[])
{
    int semArrId=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(semArrId,-1,"semget");
    return 0;
}

