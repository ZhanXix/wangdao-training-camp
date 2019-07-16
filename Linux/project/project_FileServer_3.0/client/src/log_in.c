#define _XOPEN_SOURCE
#include "fileserver_client.h"

int Sign_In(char *username,int socketFd)//注册
{
    File_Data_t fileData;
    bzero(&fileData,sizeof(fileData));
    char sendBuf[1004]={0};
    char buf[1000]={0};
    int ret;
sign_in:
    printf(LIGHT_BLUE "是否注册？\n");
    printf(NONE "(y/n):");
    fflush(stdout);
    bzero(buf,sizeof(buf));
    read(STDIN_FILENO,buf,sizeof(buf));
    if(buf[0]=='y'&&buf[1]=='\n')//开始注册
    {
        system("clear");
        printf(LIGHT_BLUE "---------------注册---------------\n");
        printf(NONE " 用户名：");
        fflush(stdout);
        bzero(buf,sizeof(buf));
        read(STDIN_FILENO,buf,sizeof(buf));
        if(strlen(buf)>39)
        {
            printf(NONE "错误：用户名过长！\n");
            goto sign_in;
        }
        bzero(username,40);
        strncpy(username,buf,strlen(buf)-1);
        bzero(&fileData,sizeof(fileData));
        strcpy(fileData.dataBuf,"signY");
        SEND_FILEDATA;
        //发送用户名
        bzero(&fileData,sizeof(fileData));
        strcpy(fileData.dataBuf,username);
        SEND_FILEDATA;
        //得到用户名是否存在的情况
        GET_FILEDATA;
        if(strcmp(fileData.dataBuf,"error")==0){
            printf(NONE "signIn ERROR: 用户名已存在！\n");
            goto sign_in;
        }
        //输入密码
sign_in2:
        fflush(stdout);
        bzero(buf,sizeof(buf));
        strcpy(buf,getpass(" 密码："));
        if(strlen(buf)>39)
        {
            printf(NONE "错误：密码过长！\n");
            goto sign_in2;
        }
        //发送密码
        bzero(&fileData,sizeof(fileData));
        strcpy(fileData.dataBuf,buf);
        SEND_FILEDATA;
        GET_FILEDATA;
        if(strcmp(fileData.dataBuf,"error")==0){
            printf("注册失败！\n");
            goto sign_in;
        }else{
            printf("注册成功！输入回车继续\n");
            getchar();
        }
    }else{
        bzero(&fileData,sizeof(fileData));
        strcpy(fileData.dataBuf,"signN");
        SEND_FILEDATA;
        system("clear");
    }
    
    return 0;
}
int Log_In(char *username,int socketFd)//登陆
{
    File_Data_t fileData;
    bzero(&fileData,sizeof(fileData));
    char sendBuf[1004]={0};
    char buf[1000]={0};
    char password[40]={0};
    int ret;
    system("clear");
LogIn:
    //输入用户名
    printf(LIGHT_BLUE "-----------文件服务器登陆-----------\n");
    printf(NONE " 用户名：");
    fflush(stdout);
    bzero(buf,sizeof(buf));
    read(STDIN_FILENO,buf,sizeof(buf));
    if(strlen(buf)>39)
    {
        printf(NONE "错误：用户名过长！\n");
        goto LogIn;
    }
    bzero(username,40);
    strncpy(username,buf,strlen(buf)-1);
    bzero(&fileData,sizeof(fileData));
    strcpy(fileData.dataBuf,username);
    SEND_FILEDATA;
    //得到用户名是否存在的情况
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"error")==0){
        printf(NONE "signIn ERROR: 用户名不存在！\n");
        goto LogIn;
    }
    //输入密码
LogIn2:
    bzero(password,sizeof(password));
    fflush(stdout);
    bzero(buf,sizeof(buf));
    strcpy(buf,getpass(" 密码："));
    if(strlen(buf)>39)
    {
        printf(NONE "错误：密码过长！\n");
        goto LogIn2;
    }
    strcpy(password,buf);
    //得到salt
    char salt[12]={0};
    GET_FILEDATA;
    strncpy(salt,fileData.dataBuf,12);
    char *shadow;
    shadow=(char*)calloc(100,sizeof(char));
    shadow=crypt(password,salt);
    //printf("signIn shadow:%s\n",shadow);
    //得到shadow
    char shadow_server[100];
    GET_FILEDATA;
    strncpy(shadow_server,fileData.dataBuf,100);
    //printf("signIn server:%s\n",shadow_server);
    if(strcmp(shadow,shadow_server)==0)
    {
        bzero(&fileData,sizeof(fileData));
        strcpy(fileData.dataBuf,"success");
        SEND_FILEDATA;
        return 0;
    }else{
        printf("密码错误！\n");
        bzero(&fileData,sizeof(fileData));
        strcpy(fileData.dataBuf,"error");
        SEND_FILEDATA;
        goto LogIn;
    }
    return 0;
}