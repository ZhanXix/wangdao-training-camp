#include <func.h>

int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    return 0;
}

