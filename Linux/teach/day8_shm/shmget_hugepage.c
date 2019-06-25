#include <func.h>
#define SHM_HUGE_2MB    (1<<21)//1<<21就是2M

int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1000,1<<21,IPC_CREAT|0600|SHM_HUGETLB|SHM_HUGE_2MB);
    ERROR_CHECK(shmid,-1,"shmget");
    
    return 0;
}

//需要开启大页开关：echo 20 > /proc/sys/vm/nr_hugepages

