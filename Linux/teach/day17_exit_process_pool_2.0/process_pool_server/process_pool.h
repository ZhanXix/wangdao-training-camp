/*
 *  written by xz in wdxly   
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <syslog.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <sys/uio.h>
#include <sys/sendfile.h>

#define ARGS_CHECK(argc,val) {if(argc!=val) {printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retVal,funcName) {if(ret==retVal) {perror(funcName);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcName) {if(ret!=0) {printf("%s:%s\n",funcName,strerror(ret));return -1;}}
#define CHILD_THREAD_ERROR_CHECK(ret,funcName) {if(ret!=0) {printf("%s:%s\n",funcName,strerror(ret));return (void*)-1;}}

#define FILENAME "file"

typedef struct{
    pid_t pid;//子进程的pid
    int pipeFd;//子进程的管道对端
    short busy;//用于标示子进程是否忙碌，0表示忙碌，1表示非忙碌
}process_data_t;

typedef struct{
    int dataLen;//存储buf上要发送的数据上去
    char buf[1000];//火车车厢
}train_t;

int makeChild(process_data_t *p,int procseeNum);
int childHandle(int pipeFd);
int sendFd(int pipeFd,int fd,char childExitFlag);
int recvFd(int pipeFd,int *fd,char* childExitFlag);
int tcpInit(int *psocketFd,char *ip,char *port);
int epollInAdd(int epfd,int fd);
int tranFile(int newFd);
