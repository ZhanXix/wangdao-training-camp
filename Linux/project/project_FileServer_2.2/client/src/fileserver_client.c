#define _GNU_SOURCE 
#include "fileserver_client.h"

int Read_Config(char *ip,char *port)//读取配置文件中的服务器ip地址和端口号
{
    int i,j;
    FILE *fp=fopen("../conf/server.conf","r");
    ERROR_CHECK(fp,(FILE*)-1,"fopen");
    char buf[256]={0},name[40]={0};
    while(fgets(buf,sizeof(buf),fp)!=NULL)
    {
        for(i=0;i<sizeof(buf)&&buf[i]!=0;++i)
        {
            if('='==buf[i])
            {
                break;
            }
            name[i]=buf[i];
        }
        if(strcmp(name,"ip")==0)//读入ip
        {
            for(j=0,i+=1;i<sizeof(buf)&&buf[i]!='\n';++i,++j)
            {
                ip[j]=buf[i];
            }
        }else if(strcmp(name,"port")==0){//读入端口号
            for(j=0,i+=1;i<sizeof(buf)&&buf[i]!='\n';++i,++j)
            {
                port[j]=buf[i];
            }
        }
    }
    return 0;
}

int SEND_CD(int socketFd,char *buf,int i,char *path)
{
    int ret;
    int j;
    File_Data_t fileData;
    char sendBuf[1004]={0};
    if(buf[i]!=' ')
    {
        return -1;
    }
    i++;
    if(buf[i]=='/')
    {
        bzero(&fileData,sizeof(fileData));
        strcpy(fileData.dataBuf,"/");
        printf("GETPATH：%s ",fileData.dataBuf);
        SEND_FILEDATA;
        i++;
        GET_FILEDATA;
        if(strcmp(fileData.dataBuf,"success")==0){
            printf ("SUCCESS\n");
        }else{
            printf("RETURN ERROR\n");
            goto cdEnd;
        }
    }
    while(buf[i]!='\n'&&buf[i]!=' '&&buf[i]!=0)
    {
        bzero(&fileData,sizeof(fileData));
        for(j=0;i<1000&&buf[i]!=0;++i,++j)
        {
            if(buf[i]==' '||buf[i]=='\n'||buf[i]=='/')
            {
                break;
            }
            fileData.dataBuf[j]=buf[i];
        }
        printf("GETPATH：%s ",fileData.dataBuf);
        SEND_FILEDATA;
        GET_FILEDATA;
        if(strcmp(fileData.dataBuf,"success")==0){
            printf ("SUCCESS\n");
        }else{
            printf("RETURN ERROR\n");
            goto cdEnd;
        }
        i++;
    }
cdEnd:
    bzero(&fileData,sizeof(fileData));
    fileData.dataLen=0;
    SEND_FILEDATA;
    GET_FILEDATA;
    strcpy(path,fileData.dataBuf);
    //printf("GET_RETURN_PATH SUCCESS:%s\n",path);
    return 0;
}

int SEND_LS(int socketFd)
{
    int ret;
    File_Data_t fileData;
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"end")!=0)
    {
        printf(LIGHT_BLUE "TYPE%*sNAME\tSIZE\n",14," ");
        printf(NONE);
    }else{
        printf(LIGHT_BLUE "NO FILE EXISTS!\n");
        printf(NONE);
    }
    while(strcmp(fileData.dataBuf,"end")!=0)
    {
        printf("%s\n",fileData.dataBuf);
        GET_FILEDATA;
    }
    return 0;
}

int SEND_PUTS(int socketFd,char *buf,int i)
{
    int ret;
    char sendBuf[1024]={0};
    File_Data_t fileData;
    bzero(&fileData,sizeof(fileData));
    char filename[50]={0};
    size_t filesize;
    int sendFlag=0;
    i++;
    for(int j=0;j<50;i++,j++)
    {
        if(buf[i]==' '||buf[i]=='\n'||buf[i]==0)
        {
            break;
        }
        filename[j]=buf[i];
    }
    if(strlen(filename)==0)
    {
        fileData.dataLen=0;
        SEND_FILEDATA;
        printf("puts ERROR: please input filename\n");
        return 0;
    }
    DIR *dirFd;
    dirFd=opendir("../files");
    ERROR_CHECK(dirFd,NULL,"opendir");
    ret=chdir("../files");
    ERROR_CHECK(ret,-1,"chdir");
    struct dirent *dir;
    struct stat state_buf;
    while((dir=readdir(dirFd)))
    {
        if(strcmp(dir->d_name,filename)==0)
        {
            sendFlag=1;
            ret=stat(dir->d_name,&state_buf);
            ERROR_CHECK(ret,-1,"stat");
            filesize=state_buf.st_size;
            break;
        }
    }
    if(sendFlag==0)
    {
        fileData.dataLen=0;
        SEND_FILEDATA;
        printf("puts ERROR: please input correct filename\n");
        return 0;
    }
    strcpy(fileData.dataBuf,filename);
    SEND_FILEDATA;
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"error")==0){
        printf("puts ERROR: same file exist in server\n");
        return 0;
    }else{
        printf("puts SUCESS: start puts\n");
    }
    //计算MD5
    bzero(&fileData,sizeof(fileData));
    int fileFd=open(filename,O_RDONLY);
    compute_file_md5(fileFd,fileData.dataBuf);
    close(fileFd);
    SEND_FILEDATA;
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"error")==0){
        printf("puts SUCESS: quick\n");
        return 0;
    }
    //发送文件大小
    fileFd=open(filename,O_RDWR);
    ERROR_CHECK(fileFd,-1,"open");
    memcpy(fileData.dataBuf,&filesize,sizeof(filesize));
    fileData.dataLen=sizeof(filesize);
    bzero(sendBuf,sizeof(sendBuf));
    memcpy(sendBuf,&fileData,fileData.dataLen+4);
    ret=send(socketFd,sendBuf,fileData.dataLen+4,0);
    ERROR_CHECK(ret,-1,"send");
    //发送文件内容
    ret=sendfile(socketFd,fileFd,NULL,filesize);
    ERROR_CHECK(ret,-1,"sendfile");
    close(fileFd);
    printf("puts SUCESS: end puts\n");
    return 0;
}

int SEND_GETS(int socketFd,char *buf,int i)
{
    //printf("socketFd=%d\n",socketFd);
    int ret;
    char sendBuf[1024]={0};
    File_Data_t fileData;
    bzero(&fileData,sizeof(fileData));
    char filename[50]={0};
    i++;
    for(int j=0;j<50;i++,j++)
    {
        if(buf[i]==' '||buf[i]=='\n'||buf[i]==0)
        {
            break;
        }
        filename[j]=buf[i];
    }
    if(strlen(filename)==0)
    {
        fileData.dataLen=0;
        SEND_FILEDATA;
        //printf("send ret=%d\n",ret);
        printf("gets ERROR: please input filename\n");
        return 0;
    }
    DIR *dirFd;
    dirFd=opendir("../files");
    ERROR_CHECK(dirFd,NULL,"opendir");
    ret=chdir("../files");
    ERROR_CHECK(ret,-1,"chdir");
    struct dirent *dir;
    while((dir=readdir(dirFd)))
    {
        if(strcmp(dir->d_name,filename)==0)
        {
            printf(LIGHT_BLUE "The same file name exists.Do you want to delete it?\n");
            printf(NONE "(y/n):");
            fflush(stdout);
            read(STDIN_FILENO,sendBuf,sizeof(sendBuf));
            if(sendBuf[0]=='y'&&sendBuf[1]=='\n'){//覆盖原文件
                unlink(filename);
                break;
            }
            else
            {
                fileData.dataLen=0;
                SEND_FILEDATA;
                return 0;
            }
        }
    }
    strcpy(fileData.dataBuf,filename);
    //printf("start getting file %s...\n",fileData.dataBuf);
    SEND_FILEDATA;
    //printf("send ret=%d\n",ret);
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"error")==0){
        printf("gets ERROR: no same file exist in server\n");
        return 0;
    }else{
        printf("gets SUCESS: start gets\n");
    }
    //接收文件大小
    off_t fileSize;
    int dataLen;
    ret=recv(socketFd,&dataLen,sizeof(int),0);
    ERROR_CHECK(ret,-1,"recv");
    ret=recv(socketFd,&fileSize,dataLen,0);
    ERROR_CHECK(ret,-1,"recv");
    printf("file size：%ld\n",fileSize);
    //建立文件
    int fileFd=open(filename,O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fileFd,-1,"open");
    //接收文件
    int spliceRet;
    int fds[2];
    pipe(fds);
    off_t downloadSize=0,lastloadSize=0,slice=fileSize/1000;
    while(downloadSize<fileSize)
    {
        spliceRet=splice(socketFd,NULL,fds[1],NULL,4096,SPLICE_F_MOVE|SPLICE_F_MORE);
        ERROR_CHECK(spliceRet,-1,"splice")
        ret=splice(fds[0],NULL,fileFd,NULL,spliceRet,SPLICE_F_MOVE|SPLICE_F_MORE);
        ERROR_CHECK(ret,-1,"splice");
        downloadSize+=ret;
        if(downloadSize-lastloadSize>slice)
        {
            printf("download：%5.2f%%\r",(float)downloadSize/fileSize);
            fflush(stdout);
            lastloadSize=downloadSize;
        }
    }
    printf("download：100.00%%\n");
    return 0;
}

int SEND_REMOVE(int socketFd,char *buf,int i)
{
    int ret;
    char sendBuf[1024]={0};
    File_Data_t fileData;
    bzero(&fileData,sizeof(fileData));
    char filename[50]={0};
    i++;
    for(int j=0;j<50;i++,j++)
    {
        if(buf[i]==' '||buf[i]=='\n'||buf[i]==0)
        {
            break;
        }
        filename[j]=buf[i];
    }
    if(strlen(filename)==0)
    {
        fileData.dataLen=0;
        SEND_FILEDATA;
        printf("remove ERROR: please input filename\n");
        return 0;
    }
    //发送文件名
    strcpy(fileData.dataBuf,filename);
    SEND_FILEDATA;
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"error")==0){
        printf("gets ERROR: no same file exist in server\n");
        return 0;
    }else{
        printf("remove SUCESS\n");
    }
    return 0;
}

int SEND_PWD(int socketFd)
{
    int ret;
    File_Data_t fileData;
    GET_FILEDATA;
    printf(LIGHT_BLUE "CURRENT PATH: ");
    printf(NONE "%s\n",fileData.dataBuf);
    return 0;
}

int SEND_MKDIR(int socketFd,char *buf,int i)
{
    int ret;
    char sendBuf[1024]={0};
    File_Data_t fileData;
    bzero(&fileData,sizeof(fileData));
    char dirname[50]={0};
    //取得文件夹名
    i++;
    for(int j=0;j<50;i++,j++)
    {
        if(buf[i]==' '||buf[i]=='\n'||buf[i]==0)
        {
            break;
        }
        dirname[j]=buf[i];
    }
    if(strlen(dirname)==0)
    {
        fileData.dataLen=0;
        SEND_FILEDATA;
        printf("mkdir ERROR: please input dirname\n");
        return 0;
    }
    strcpy(fileData.dataBuf,dirname);
    SEND_FILEDATA;
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"error")==0){
        printf("mkdir ERROR: same dir exist in server\n");
        return 0;
    }else{
        printf("mkdir SUCESS\n");
    }
    return 0;
}

int SEND_RMDIR(int socketFd,char *buf,int i)
{
    int ret;
    char sendBuf[1024]={0};
    File_Data_t fileData;
    bzero(&fileData,sizeof(fileData));
    char dirname[50]={0};
    //取得文件夹名
    i++;
    for(int j=0;j<50;i++,j++)
    {
        if(buf[i]==' '||buf[i]=='\n'||buf[i]==0)
        {
            break;
        }
        dirname[j]=buf[i];
    }
    if(strlen(dirname)==0)
    {
        fileData.dataLen=0;
        SEND_FILEDATA;
        printf("rmdir ERROR: please input dirname\n");
        return 0;
    }
    strcpy(fileData.dataBuf,dirname);
    SEND_FILEDATA;
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"error")==0){
        printf("rmdir ERROR: no same dir exist in server\n");
        return 0;
    }
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"error")==0){
        printf("rmdir ERROR: this dir is not empty!\n");
        return 0;
    }else{
        printf("rmdir SUCCESS\n");
    }
    return 0;
}