#include "fileserver_client.h"

int main()
{
    int ret;
    //从配置文件读取ip和port
    char ip[15]={0},port[5]={0};
    ret=Read_Config(ip,port);
    ERROR_RETURN(ret);
#ifdef DEBUG
    printf("server config: ip=%s,port=%s\n",ip,port);
#endif // DEBUG
    //连接服务器
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in socketAddr;
    bzero(&socketAddr,sizeof(socketAddr));
    socketAddr.sin_family=AF_INET;
    socketAddr.sin_addr.s_addr=inet_addr("192.168.5.192");
    socketAddr.sin_port=htons(2000);
    ret=connect(socketFd,(struct sockaddr*)&socketAddr,sizeof(socketAddr));
    ERROR_CHECK(ret,-1,"connect");
    printf("连接服务器成功...\n");
    printf("socketFd=%d\n",socketFd);
    //传输命令
    File_Data_t fileData;
    bzero(&fileData,sizeof(fileData));
    char buf[1000]={0};
    char sendBuf[1004]={0};
    char path[1024]="/";
    int i;
    system("clear");
    printf(LIGHT_BLUE "----------客户端启动成功----------\n");
    printf(NONE " cd 进入对应目录\n ls 列出相应目录文件\n puts 将本地文件上传至服务器\n");
    printf(" gets 文件名下载服务器文件到本地\n remove 删除服务器上文件\n pwd 显示目前所在路径\n");
    printf(" help 显示帮助\n exit 退出\n");
    printf(LIGHT_BLUE "----------------------------------\n\n%s > ",path);
    printf(NONE);
    fflush(stdout);
    while(-1!=read(STDIN_FILENO,buf,sizeof(buf)))
    {   
        for(i=0;i<strlen(buf);++i)
        {
            if(buf[i]==' '||buf[i]=='\n')
            {
                break;
            }
            fileData.dataBuf[i]=buf[i];
        }
        if(strcmp(fileData.dataBuf,"cd")==0)//cd
        {
            SEND_FILEDATA;
            ret=SEND_CD(socketFd,buf,i,path);
            if(-1==ret)
            {
                break;
            }
        }else if(strcmp(fileData.dataBuf,"ls")==0){
            SEND_FILEDATA;
            ret=SEND_LS(socketFd);
            if(-1==ret)
            {
                break;
            }
        }else if(strcmp(fileData.dataBuf,"puts")==0){
            SEND_FILEDATA;
            ret=SEND_PUTS(socketFd,buf,i);
            if(-1==ret)
            {
                break;
            }
        }else if(strcmp(fileData.dataBuf,"gets")==0){
            SEND_FILEDATA;
            ret=SEND_GETS(socketFd,buf,i);
            if(-1==ret)
            {
                break;
            }
        }else if(strcmp(fileData.dataBuf,"remove")==0){
            SEND_FILEDATA;
            ret=SEND_REMOVE(socketFd,buf,i);
            if(-1==ret)
            {
                break;
            }
        }else if(strcmp(fileData.dataBuf,"pwd")==0){
            SEND_FILEDATA;
            ret=SEND_PWD(socketFd);
            if(-1==ret)
            {
                break;
            }
        }else if(strcmp(fileData.dataBuf,"help")==0){
            printf(" cd 进入对应目录\n ls 列出相应目录文件\n puts 将本地文件上传至服务器\n");
            printf(" gets 文件名下载服务器文件到本地\n remove 删除服务器上文件\n pwd 显示目前所在路径\n");
            printf(" help 显示帮助\n exit 退出\n");
        }else if(strcmp(fileData.dataBuf,"exit")==0){
            printf(LIGHT_BLUE "BYEBYE!\n");
            close(socketFd);
            exit(0);
        }else{
            printf(LIGHT_BLUE "ERROR COMMAND！\n");
            printf(NONE);
        }
        bzero(buf,sizeof(buf));
        bzero(&fileData,sizeof(fileData));
        printf(LIGHT_BLUE "\n%s > ",path);
        printf(NONE);
        fflush(stdout);
    } 
    return 0;
}

