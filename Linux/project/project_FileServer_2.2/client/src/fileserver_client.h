#ifndef FILESERVER_CLIENT_H
#define FILESERVER_CLIENT_H

#include "head.h"
#include "md5.h"

#define DEBUG
#define LIGHT_BLUE "\033[1;34m"
#define NONE "\033[m"

#define SEND_FILEDATA {fileData.dataLen=strlen(fileData.dataBuf);\
            bzero(sendBuf,sizeof(sendBuf));\
            memcpy(sendBuf,&fileData,fileData.dataLen+4);\
            ret=send(socketFd,sendBuf,fileData.dataLen+4,0);\
            ERROR_CHECK(ret,-1,"send");}
#define GET_FILEDATA {bzero(&fileData,sizeof(fileData));\
            ret=recv(socketFd,&fileData.dataLen,4,0);\
            ERROR_CHECK(ret,-1,"recv");\
            ret=recv(socketFd,fileData.dataBuf,fileData.dataLen,0);\
            ERROR_CHECK(ret,-1,"recv");\
            if(0==ret) {printf(LIGHT_BLUE "sever disconnect!\n");exit(0);}}

typedef struct file_data
{
    int dataLen;
    char dataBuf[1000];
}File_Data_t;

//fileserver_client.c
int Read_Config(char *ip,char *port);

int SEND_CD(int socketFd,char *buf,int i,char *path);
int SEND_LS(int socketFd);

int SEND_PUTS(int socketFd,char *buf,int i);
int SEND_GETS(int socketFd,char *buf,int i);
int SEND_REMOVE(int socketFd,char *buf,int i);

int SEND_PWD(int socketFd);

int SEND_MKDIR(int socketFd,char *buf,int i);
int SEND_RMDIR(int socketFd,char *buf,int i);

//log_in.c
int Sign_In(char *username,int socketFd);
int Log_In(char *username,int socketFd);



#endif // !FILESERVER_CLIENT_H
