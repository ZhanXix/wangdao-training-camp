#define _GNU_SOURCE 
#include "file_server.h"

void cleanup(void *p)
{
    pWork_Queue_t pW=(pWork_Queue_t)p;
    pthread_mutex_unlock(&pW->WorkQueuemutex);
}

void *Thread_Func(void *p)
{
    int ret;
    pThread_Pool_Info_t pT=(pThread_Pool_Info_t)p;
    pWork_Queue_t pW=pT->pWorkQueue;
    int clientFd;
    while(1)
    {
        //printf("线程开始加锁\n");
        pthread_mutex_lock(&pW->WorkQueuemutex);
        pthread_cleanup_push(cleanup,pW);
        if(pW->WorkQueueSize==0)
        {
            printf("线程开始等待>\n");
            pthread_cond_wait(&pT->cond,&pW->WorkQueuemutex);
        }
        printf("<线程开始工作\n");
        ret=WorkQueue_Get(&clientFd,pW);
        pthread_cleanup_pop(1);
        pthread_mutex_unlock(&pW->WorkQueuemutex);
        if(-1==ret)//未能成功取得队列结点
        {
            continue;
        }
        //连接数据库
        MYSQL *connect;
        int code=0;
        //接收命令
        File_Data_t fileData;
        bzero(&fileData,sizeof(fileData));
        while(0!=recv(clientFd,&fileData.dataLen,4,0))
        {
            if(-1==ret)
            {
                break;
            }
            ret=recv(clientFd,fileData.dataBuf,fileData.dataLen,0);
            if(-1==ret)
            {
                break;
            }
            ret=Command_Deal(fileData.dataBuf,clientFd,connect,&code);
            if(-1==ret)
            {
                break;
            }
            bzero(&fileData,sizeof(fileData));
        }
        close(clientFd);
    }
    return NULL;
}

int Command_Deal(char *command,int clientFd,MYSQL *connect,int *pCode)
{
    putchar('\n');
    int ret;
    if(strcmp(command,"cd")==0)//cd
    {
        puts("捕捉命令：cd");
        ret=Command_cd(clientFd,pCode,connect);
        ERROR_RETURN(ret);
    }else if(strcmp(command,"ls")==0){//ls
        puts("捕捉命令：ls");
        ret=Command_ls(clientFd,pCode,connect);
        ERROR_RETURN(ret);
    }else if(strcmp(command,"puts")==0){//puts
        puts("捕捉命令：puts");
        ret=Command_puts(clientFd,pCode,connect);
        ERROR_RETURN(ret);
    }else if(strcmp(command,"gets")==0){//gets
        puts("捕捉命令：gets");
        ret=Command_gets(clientFd,pCode,connect);
        ERROR_RETURN(ret);
    }else if(strcmp(command,"remove")==0){//remove
        puts("捕捉命令：remove");
        ret=Command_remove(clientFd,pCode,connect);
        ERROR_RETURN(ret);
    }else if(strcmp(command,"pwd")==0){//pwd
        puts("捕捉命令：pwd");
        ret=Command_pwd(clientFd,pCode,connect);
        ERROR_RETURN(ret);
    }
    return 0;
}

int GET_PATH(int code,char *path,MYSQL *connect)
{
    CONNECT_MYSQL;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[2000]={0};
    char pathBuf[1000]={0};
    if(0==code)
    {
        strcpy(pathBuf,"/");
    }
    while(code)
    {
        bzero(query,sizeof(query));
        sprintf(query,"select * from file_list where code=%d;",code);
        printf("get_path:select * from file_list where code=%d;\n",code);
        if(mysql_query(connect,query)){
            printf("get_path ERROR:%s\n",mysql_error(connect));
            return -1;
        }else{
            res=mysql_use_result(connect);
            row=mysql_fetch_row(res);
            if(row)
            {
                code=atoi(row[1]);
                printf("get_path SUCCESS:precode=%d,dirname=%s\n",code,row[2]);
                bzero(path,1000);
                strcat(path,"/");
                strcat(path,row[2]);
                strcat(path,pathBuf);
                strcpy(pathBuf,path);
                mysql_free_result(res);
            }else{
                printf("get_path ERROR:查询的行不存在\n");
                mysql_free_result(res);
                return -1;
            }
        }
    }
    strcpy(path,pathBuf);
    printf("get_path SUCCESS:%s\n",path);
    mysql_close(connect);  
    return 0;
}

int Command_cd(int clientFd,int *pCode,MYSQL *connect)
{
    CONNECT_MYSQL;
    int ret;
    int code=*pCode;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[2000]={0};
    File_Data_t fileData;
    char sendBuf[1004]={0};
    while(1)
    {
        bzero(&fileData,sizeof(fileData));
        ret=recv(clientFd,&fileData.dataLen,4,0);
        ERROR_CHECK(ret,-1,"recv");
        if(0==fileData.dataLen)//接收为空
        {
            break;
        }else{
            ret=recv(clientFd,fileData.dataBuf,fileData.dataLen,0);
            ERROR_CHECK(ret,-1,"recv");
            if(strcmp("/",fileData.dataBuf)==0)
            {
                printf("cd:返回主目录\n");
                code=0;
                SEND_SUCCESS;
            }else if(strcmp("..",fileData.dataBuf)==0)
            {
                bzero(query,sizeof(query));
                sprintf(query,"select * from file_list where code=%d;",code);
                printf("cd:select * from file_list where code=%d;\n",code);
                if(mysql_query(connect,query)){
                    printf("cd ERROR:%s\n",mysql_error(connect));
                    SEND_ERROR;
                    break;
                }else{
                    res=mysql_use_result(connect);
                    row=mysql_fetch_row(res);
                    if(row)
                    {
                        code=atoi(row[1]);
                        printf("cd SUCCESS:code=%d\n",code);
                        SEND_SUCCESS;
                        mysql_free_result(res);
                    }else{
                        printf("cd ERROR:目录不存在\n");
                        SEND_ERROR;
                        mysql_free_result(res);
                        break;
                    }                    
                }
            }else{
                bzero(query,sizeof(query));
                sprintf(query,"select * from file_list where precode=%d and filename='%s' and filetype='d';",code,fileData.dataBuf);
                printf("cd:select * from file_list where precode=%d and filename='%s' and filetype='d';\n",code,fileData.dataBuf);
                if(mysql_query(connect,query)){
                    printf("cd ERROR:%s\n",mysql_error(connect));
                    SEND_ERROR;
                    break;
                }else{
                    res=mysql_use_result(connect);
                    row=mysql_fetch_row(res);
                    if(row)
                    {
                        code=atoi(row[0]);
                        printf("cd SUCCESS:code=%d\n",code);
                        SEND_SUCCESS;
                        mysql_free_result(res);
                    }else{
                        printf("cd ERROR:目录不存在\n");
                        SEND_ERROR;
                        mysql_free_result(res);
                        break;
                    }                    
                }
            }
        }
    }
    mysql_close(connect);  
    *pCode=code;
    bzero(&fileData,sizeof(fileData));
    GET_PATH(code,fileData.dataBuf,connect);
    SEND_FILEDATA;
    return 0;
}

int Command_ls(int clientFd,int *pCode,MYSQL *connect)
{
    CONNECT_MYSQL;
    int ret;
    int code=*pCode;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[2000]={0};
    char lsBuf[1000]={0};
    File_Data_t fileData;
    char sendBuf[1004]={0};
    sprintf(query,"select * from file_list where precode=%d;",code);
    printf("ls:select * from file_list where precode=%d;\n",code);
    if(mysql_query(connect,query)){
        printf("ls ERROR:%s\n",mysql_error(connect));
        SEND_ERROR;
        return -1;
    }else{
        res=mysql_use_result(connect);
        if(res)
        {
            while((row=mysql_fetch_row(res))!=NULL)
            {
                bzero(lsBuf,sizeof(lsBuf));
                sprintf(lsBuf,"%s %20s\t%s",row[4],row[2],row[3]);
                printf("ls:%s %20s\t%s\n",row[4],row[2],row[3]);
                bzero(&fileData,sizeof(fileData));
                strcpy(fileData.dataBuf,lsBuf);
                SEND_FILEDATA;
            }
        }
        bzero(&fileData,sizeof(fileData));
        strcpy(fileData.dataBuf,"end");
        SEND_FILEDATA;
        printf("ls:end\n");
    } 
    mysql_close(connect);    
    return 0;
}

int Command_puts(int clientFd,int *pCode,MYSQL *connect)
{
    CONNECT_MYSQL;
    int ret;
    int code=*pCode;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1000]={0};
    char filename[50]={0};
    File_Data_t fileData;
    char sendBuf[1004]={0};
    GET_FILEDATA;
    if(0==fileData.dataLen)
    {
        return 0;
    }
    strcpy(filename,fileData.dataBuf);
    sprintf(query,"select * from file_list where precode=%d and filename='%s';",code,filename);
    printf("puts:select * from file_list where precode=%d and filename='%s';\n",code,filename);
    if(mysql_query(connect,query)){
        printf("puts ERROR:%s\n",mysql_error(connect));
        SEND_ERROR;
        return -1;
    }else{
        res=mysql_use_result(connect);
        row=mysql_fetch_row(res);
        if(row) //存在同名文件
        {
            printf("puts ERROR:存在同名文件\n");
            SEND_ERROR;
            return 0;
        }else{
            printf("puts SUCCESS:开始文件传输\n");
            SEND_SUCCESS;
        }
    }
    if(!fork())//创建子进程以进行文件传输
    {
        char path[1000]="../files";
        char pathBuf[1000]={0};
        GET_PATH(code,pathBuf,connect);
        strcat(path,pathBuf);
        printf("puts PATH:%s\n",path);
        ret=chdir(path);
        ERROR_CHECK(ret,-1,"chdir");
        //接收文件大小
        off_t fileSize;
        int dataLen;
        ret=recv(clientFd,&dataLen,sizeof(int),0);
        ERROR_CHECK(ret,-1,"recv");
        ret=recv(clientFd,&fileSize,dataLen,0);
        ERROR_CHECK(ret,-1,"recv");
        printf("文件大小：%ld\n",fileSize);
        //打开文件
        int fileFd=open(filename,O_RDWR|O_CREAT,0666);
        ERROR_CHECK(fileFd,-1,"open");
        //接收文件
        int ret,spliceRet;
        int fds[2];
        pipe(fds);
        off_t downloadSize=0,lastloadSize=0,slice=fileSize/1000;
        while(downloadSize<fileSize)
        {
            spliceRet=splice(clientFd,NULL,fds[1],NULL,4096,SPLICE_F_MOVE|SPLICE_F_MORE);
            ERROR_CHECK(spliceRet,-1,"splice")
            ret=splice(fds[0],NULL,fileFd,NULL,spliceRet,SPLICE_F_MOVE|SPLICE_F_MORE);
            ERROR_CHECK(ret,-1,"splice");
            downloadSize+=ret;
            if(downloadSize-lastloadSize>slice)
            {
                printf("已下载：%5.2f%%\r",(float)downloadSize/fileSize);
                fflush(stdout);
                lastloadSize=downloadSize;
            }
        }
        printf("已下载：100.00%%\n");
        //插入数据库
        bzero(query,sizeof(query));
        char MD5[32];
        md5Sum(MD5,filename);
        sprintf(query,"insert into file_list (precode,filename,filesize,filetype,MD5,owner) values (%d,'%s',%ld,'f','%s','xiaoming');",code,filename,fileSize,MD5);
        printf("puts:insert into file_list (precode,filename,filesize,filetype,MD5,owner) values (%d,'%s',%ld,'f','%s','xiaoming');\n",code,filename,fileSize,MD5);
        if(mysql_query(connect,query))
        {
            printf("puts Error making insert:%s\n",mysql_error(connect));
        }else{
            printf("puts:insert success\n");
        }
        exit(0);
    }else{
        wait(NULL);
        printf("puts:wait child process success\n");
    }
    mysql_close(connect);  
    return 0;
}

int Command_gets(int clientFd,int *pCode,MYSQL *connect)
{
    CONNECT_MYSQL;
    int ret;
    int code=*pCode;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1000]={0};
    char filename[50]={0};
    off_t filesize;
    File_Data_t fileData;
    char sendBuf[1004]={0};
    //printf("gets:filename\n");
    GET_FILEDATA;
    if(0==fileData.dataLen)
    {
        printf("gets ERROR:No filename\n");
        return 0;
    }
    strcpy(filename,fileData.dataBuf);
    sprintf(query,"select * from file_list where precode=%d and filename='%s' and filetype='f';",code,filename);
    printf("gets:select * from file_list where precode=%d and filename='%s' and filetype='f';\n",code,filename);
    if(mysql_query(connect,query)){
        printf("gets ERROR:%s\n",mysql_error(connect));
        SEND_ERROR;
        return -1;
    }else{
        res=mysql_use_result(connect);
        row=mysql_fetch_row(res);
        if(row) //存在同名文件
        {
            printf("gets SUCCESS:开始文件传输\n");
            SEND_SUCCESS;
        }else{
            printf("gets ERROR:不存在该文件\n");
            SEND_ERROR;
            return 0;
        }
    }
    mysql_close(connect);  
    if(!fork())//创建子进程以进行文件传输
    {
        char path[1000]="../files";
        char pathBuf[1000]={0};
        GET_PATH(code,pathBuf,connect);
        strcat(path,pathBuf);
        printf("gets PATH:%s\n",path);
        ret=chdir(path);
        ERROR_CHECK(ret,-1,"chdir");
        //发送文件大小
        struct stat state_buf;
        ret=stat(filename,&state_buf);
        ERROR_CHECK(ret,-1,"stat");
        filesize=state_buf.st_size;
        printf("gets filesize=%ld\n",filesize);
        bzero(&fileData,sizeof(fileData));
        memcpy(fileData.dataBuf,&filesize,sizeof(filesize));
        fileData.dataLen=sizeof(filesize);
        bzero(sendBuf,sizeof(sendBuf));
        memcpy(sendBuf,&fileData,fileData.dataLen+4);
        ret=send(clientFd,sendBuf,fileData.dataLen+4,0);
        ERROR_CHECK(ret,-1,"send");
        //打开文件
        int fileFd=open(filename,O_RDWR);
        ERROR_CHECK(fileFd,-1,"open");
        //发送文件内容
        ret=sendfile(clientFd,fileFd,NULL,filesize);
        ERROR_CHECK(ret,-1,"sendfile");
        close(fileFd);
        exit(0);
    }else{
        wait(NULL);
        printf("gets:wait child process success\n");
    }
    return 0;
}

int Command_remove(int clientFd,int *pCode,MYSQL *connect)
{
    int ret;
    int code=*pCode;
    int fileCode;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1000]={0};
    char filename[50]={0};
    File_Data_t fileData;
    char sendBuf[1004]={0};
    printf("remove get:filename\n");
    GET_FILEDATA;
    if(0==fileData.dataLen)
    {
        printf("remove get ERROR:no filename\n");
        return 0;
    }
    strcpy(filename,fileData.dataBuf);
    CONNECT_MYSQL;
    sprintf(query,"select * from file_list where precode=%d and filename='%s' and filetype='f';",code,filename);
    printf("remove:select * from file_list where precode=%d and filename='%s' and filetype='f';\n",code,filename);
    if(mysql_query(connect,query)){
        printf("gets ERROR:%s\n",mysql_error(connect));
        SEND_ERROR;
        return -1;
    }else{
        res=mysql_use_result(connect);
        row=mysql_fetch_row(res);
        if(row) //存在同名文件
        {
            printf("gets SUCCESS:开始删除文件\n");
            fileCode=atoi(row[0]);
        }else{
            printf("gets ERROR:不存在该文件\n");
            SEND_ERROR;
            return 0;
        }
    }
    mysql_close(connect);  
    //从数据库删除
    CONNECT_MYSQL;
    bzero(query,sizeof(query));
    sprintf(query,"delete from file_list where code=%d;",fileCode);
    printf("remove:delete from file_list where code=%d;\n",fileCode);
    if(mysql_query(connect,query))
    {
        printf("remove Error making insert:%s\n",mysql_error(connect));
    }else{
        printf("remove:delete file_info in mysql success\n");
    }
    mysql_close(connect);  
    SEND_SUCCESS;
    if(!fork())//创建子进程以进行文件删除
    {
        char path[1000]="../files";
        char pathBuf[1000]={0};
        GET_PATH(code,pathBuf,connect);
        strcat(path,pathBuf);
        printf("puts PATH:%s\n",path);
        ret=chdir(path);
        ERROR_CHECK(ret,-1,"chdir");
        //删除文件
        unlink(filename);
        printf("remove:delete file SUCCESS\n");
        exit(0);
    }else{
        wait(NULL);
        printf("puts:wait child process success\n");

    }
    return 0;
}

int Command_pwd(int clientFd,int *pCode,MYSQL *connect)
{
    int ret;
    File_Data_t fileData;
    char sendBuf[1004]={0};
    bzero(&fileData,sizeof(fileData));
    GET_PATH(*pCode,fileData.dataBuf,connect);
    SEND_FILEDATA;
    return 0;
}