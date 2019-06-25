#include <func.h>

int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1000,1<<20,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    struct shmid_ds buf;
    int ret;
    ret=shmctl(shmid,IPC_STAT,&buf);
    ERROR_CHECK(ret,-1,"shmctl");
    printf("%d %o %ld %ld\n",buf.shm_perm.uid,buf.shm_perm.mode,buf.shm_segsz,buf.shm_nattch);
    buf.shm_perm.mode=0666;
    shmctl(shmid,IPC_SET,&buf);
    return 0;
}

