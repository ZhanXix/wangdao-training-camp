#ifndef FILE_SERVER_H
#define FILE_SERVER_H

#include "head.h"
#include "thread_pool.h"
#include "md5.h"

#define DEBUG
#define SEND_SUCCESS {bzero(&fileData,sizeof(fileData));\
                bzero(sendBuf,sizeof(sendBuf));\
                fileData.dataLen=7;\
                strcpy(fileData.dataBuf,"success");\
                memcpy(sendBuf,&fileData,sizeof(fileData));\
                ret=send(clientFd,sendBuf,fileData.dataLen+4,0);\
                ERROR_CHECK(ret,-1,"send");}
#define SEND_ERROR {bzero(&fileData,sizeof(fileData));\
                bzero(sendBuf,sizeof(sendBuf));\
                fileData.dataLen=5;\
                strcpy(fileData.dataBuf,"error");\
                memcpy(sendBuf,&fileData,sizeof(fileData));\
                ret=send(clientFd,sendBuf,fileData.dataLen+4,0);\
                ERROR_CHECK(ret,-1,"send");}
#define SEND_FILEDATA {fileData.dataLen=strlen(fileData.dataBuf);\
                bzero(sendBuf,sizeof(sendBuf));\
                memcpy(sendBuf,&fileData,fileData.dataLen+4);\
                ret=send(clientFd,sendBuf,fileData.dataLen+4,0);\
                ERROR_CHECK(ret,-1,"send");}
#define GET_FILEDATA {bzero(&fileData,sizeof(fileData));\
                ret=recv(clientFd,&fileData.dataLen,4,0);\
                ERROR_CHECK(ret,-1,"recv");\
                ret=recv(clientFd,fileData.dataBuf,fileData.dataLen,0);\
                ERROR_CHECK(ret,-1,"recv");}


#define CONNECT_MYSQL {char *host="localhost";\
                char *user="root";\
                char *password="";\
                char *database="file_server_info";\
                connect=mysql_init(NULL);\
                if(!mysql_real_connect(connect,host,user,password,database,0,NULL,0))\
                {printf("CONNECT_MYSQL:ERROR\n");}\
                else{printf("CONNECT_MYSQL:SUCESS\n");}}

//file_server.c
int Read_Config(char *ip,char *port,int *threadNum);
int Tcp_Init(int *pSocketFd,char *ip,char *port);
int Epoll_Add(int epFd,int socketFd);

//log_in.c
int SignIn_Deal(int clientFd);
int LogIn_Deal(int clientFd,char *username);
int Make_Salt(char *salt);


#endif // !FILE_SERVER_H



