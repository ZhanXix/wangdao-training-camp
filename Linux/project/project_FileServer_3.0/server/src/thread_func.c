#define _GNU_SOURCE 
#include "../include/file_server.h"

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
        //当前目录号
        int code=0;
        //登陆
        char username[40]={0};
        ret=SignIn_Deal(clientFd);
        if(-1==ret)
        {
            close(clientFd);
            continue;
        }
        ret=LogIn_Deal(clientFd,username);
        if(-1==ret)
        {
            close(clientFd);
            continue;
        }
        printf("登陆成功！用户名：%s\n",username);
        //写日志
        MYSQL *conn;
        CONNECT_MYSQL;
        char query[1000]={0};
        sprintf(query,"insert into log_list (username,log) values ('%s','*login*');",username);
        printf("Log:insert into log_list (username,log) values ('%s','*login*');\n",username);
        if(mysql_query(conn,query))
        {
            printf("Log ERROR connect mysql:%s\n",mysql_error(conn));
            break;
        }
        mysql_close(conn);
        //接收命令
        File_Data_t fileData;
        bzero(&fileData,sizeof(fileData));
        char command[10]={0};
        while(0!=recv(clientFd,&fileData.dataLen,4,0))
        {
            ret=recv(clientFd,fileData.dataBuf,fileData.dataLen,0);
            if(-1==ret)
            {
                break;
            }
            //处理命令
            ret=Command_Deal(fileData.dataBuf,clientFd,&code,username);
            if(-1==ret)
            {
                break;
            }
            bzero(command,sizeof(command));
            strcpy(command,fileData.dataBuf);
            //写日志
            CONNECT_MYSQL;
            bzero(query,sizeof(query));
            sprintf(query,"insert into log_list (username,log) values ('%s','%s');",username,command);
            printf("Log:insert into log_list (username,log) values ('%s','%s');\n",username,command);
            if(mysql_query(conn,query))
            {
                printf("Log ERROR connect mysql:%s\n",mysql_error(conn));
                break;
            }
            mysql_close(conn);
            //重置fileData
            bzero(&fileData,sizeof(fileData));
        }
        //写日志
        CONNECT_MYSQL;
        bzero(query,sizeof(query));
        sprintf(query,"insert into log_list (username,log) values ('%s','*exit*');",username);
        printf("Log:insert into log_list (username,log) values ('%s','*exit*');\n",username);
        if(mysql_query(conn,query))
        {
            printf("Log ERROR connect mysql:%s\n",mysql_error(conn));
            break;
        }
        mysql_close(conn);
        //断开客户端连接
        close(clientFd);
    }
    return NULL;
}

int Command_Deal(char *command,int clientFd,int *pCode,char *username)
{
    MYSQL *conn=NULL;
    putchar('\n');
    int ret;
    if(strcmp(command,"cd")==0)//cd
    {
        puts("捕捉命令：cd");
        ret=Command_cd(clientFd,pCode,conn,username);
        ERROR_RETURN(ret);
    }else if(strcmp(command,"ls")==0){//ls
        puts("捕捉命令：ls");
        ret=Command_ls(clientFd,pCode,conn,username);
        ERROR_RETURN(ret);
    }else if(strcmp(command,"puts")==0){//puts
        puts("捕捉命令：puts");
        ret=Command_puts(clientFd,pCode,conn,username);
        ERROR_RETURN(ret);
    }else if(strcmp(command,"gets")==0){//gets
        puts("捕捉命令：gets");
        ret=Command_gets(clientFd,pCode,conn,username);
        ERROR_RETURN(ret);
    }else if(strcmp(command,"remove")==0){//remove
        puts("捕捉命令：remove");
        ret=Command_remove(clientFd,pCode,conn,username);
        ERROR_RETURN(ret);
    }else if(strcmp(command,"pwd")==0){//pwd
        puts("捕捉命令：pwd");
        ret=Command_pwd(clientFd,pCode,conn);
        ERROR_RETURN(ret);
    }else if(strcmp(command,"mkdir")==0){//mkdir
        puts("捕捉命令：mkdir");
        ret=Command_mkdir(clientFd,pCode,conn,username);
        ERROR_RETURN(ret);
    }
    return 0;
}

int GET_PATH(int code,char *path,MYSQL *conn)
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
        if(mysql_query(conn,query)){
            printf("get_path ERROR:%s\n",mysql_error(conn));
            return -1;
        }else{
            res=mysql_use_result(conn);
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
    mysql_close(conn);  
    return 0;
}

int Command_cd(int clientFd,int *pCode,MYSQL *conn,char *username)
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
                sprintf(query,"select * from file_list where code=%d and owner='%s';",code,username);
                printf("cd:select * from file_list where code=%dand owner='%s';\n",code,username);
                if(mysql_query(conn,query)){
                    printf("cd ERROR:%s\n",mysql_error(conn));
                    SEND_ERROR;
                    break;
                }else{
                    res=mysql_use_result(conn);
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
                sprintf(query,"select * from file_list where precode=%d and filename='%s' and filetype='d' and owner='%s';",code,fileData.dataBuf,username);
                printf("cd:select * from file_list where precode=%d and filename='%s' and filetype='d' and owner='%s';\n" ,code,fileData.dataBuf,username);
                if(mysql_query(conn,query)){
                    printf("cd ERROR:%s\n",mysql_error(conn));
                    SEND_ERROR;
                    break;
                }else{
                    res=mysql_use_result(conn);
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
    mysql_close(conn);  
    *pCode=code;
    bzero(&fileData,sizeof(fileData));
    GET_PATH(code,fileData.dataBuf,conn);
    SEND_FILEDATA;
    return 0;
}

int Command_ls(int clientFd,int *pCode,MYSQL *conn,char *username)
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
    sprintf(query,"select * from file_list where precode=%d and owner='%s';",code,username);
    printf("ls:select * from file_list where precode=%d and owner='%s';\n",code,username);
    if(mysql_query(conn,query)){
        printf("ls ERROR:%s\n",mysql_error(conn));
        SEND_ERROR;
        return -1;
    }else{
        res=mysql_use_result(conn);
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
    mysql_close(conn);    
    return 0;
}

int Command_puts(int clientFd,int *pCode,MYSQL *conn,char *username)
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
    off_t fileSize;
    GET_FILEDATA;
    if(0==fileData.dataLen)
    {
        return 0;
    }
    strcpy(filename,fileData.dataBuf);
    sprintf(query,"select * from file_list where precode=%d and filename='%s' and owner='%s';",code,filename,username);
    printf("puts:select * from file_list where precode=%d and filename='%s' and owner='%s';\n",code,filename,username);
    if(mysql_query(conn,query)){
        printf("puts ERROR:%s\n",mysql_error(conn));
        SEND_ERROR;
        return -1;
    }else{
        res=mysql_use_result(conn);
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
    mysql_close(conn);  
    //接收文件MD5
    GET_FILEDATA;
    char MD5[100]={0};
    strcpy(MD5,fileData.dataBuf);
    printf("puts MD5:%s",MD5);
    //查询是否可以极速秒传
    CONNECT_MYSQL;
    bzero(query,sizeof(query));
    sprintf(query,"select * from file_list where MD5='%s';",MD5);
    printf("puts:select * from file_list where MD5='%s';\n",MD5);
    if(mysql_query(conn,query)){
        printf("puts ERROR:%s\n",mysql_error(conn));
        return -1;
    }else{
        res=mysql_use_result(conn);
        row=mysql_fetch_row(res);
        if(row) //存在同MD5文件
        {
            printf("puts SUCCESS:quick\n");
            fileSize=atoi(row[3]);
            SEND_ERROR;
        }else{
            printf("puts SUCCESS:开始文件传输\n");
            SEND_SUCCESS;
            int dataLen;
            ret=recv(clientFd,&dataLen,sizeof(int),0);
            ERROR_CHECK(ret,-1,"recv");
            ret=recv(clientFd,&fileSize,dataLen,0);
            ERROR_CHECK(ret,-1,"recv");
            printf("文件大小：%ld\n",fileSize);
            //打开文件
            int fileFd=open(MD5,O_RDWR|O_CREAT,0666);
            ERROR_CHECK(fileFd,-1,"open");
            //接收文件
            int spliceRet;
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
            close(fileFd); 
        }
    }
    mysql_close(conn);  
    CONNECT_MYSQL;
    bzero(query,sizeof(query));
    sprintf(query,"insert into file_list (precode,filename,filesize,filetype,MD5,owner) values (%d,'%s',%ld,'f','%s','%s');",code,filename,fileSize,MD5,username);
    printf("puts:insert into file_list (precode,filename,filesize,filetype,MD5,owner) values (%d,'%s',%ld,'f','%s','%s');\n",code,filename,fileSize,MD5,username);
    if(mysql_query(conn,query))
    {
        printf("puts Error making insert:%s\n",mysql_error(conn));
    }else{
        printf("puts:insert success\n");
    }
    return 0;
}

int Command_gets(int clientFd,int *pCode,MYSQL *conn,char *username)
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
    char trueFilename[100]={0};
    //printf("gets:filename\n");
    GET_FILEDATA;
    if(0==fileData.dataLen)
    {
        printf("gets ERROR:No filename\n");
        return 0;
    }
    strcpy(filename,fileData.dataBuf);
    sprintf(query,"select * from file_list where precode=%d and filename='%s' and filetype='f' and owner='%s';",code,filename,username);
    printf("gets:select * from file_list where precode=%d and filename='%s' and filetype='f'  and owner='%s';\n",code,filename,username);
    if(mysql_query(conn,query)){
        printf("gets ERROR:%s\n",mysql_error(conn));
        SEND_ERROR;
        return -1;
    }else{
        res=mysql_use_result(conn);
        row=mysql_fetch_row(res);
        if(row) //存在同名文件
        {
            printf("gets SUCCESS:开始文件传输\n");
            strcpy(trueFilename,row[5]);
            SEND_SUCCESS;
        }else{
            printf("gets ERROR:不存在该文件\n");
            SEND_ERROR;
            return 0;
        }
    }
    mysql_close(conn);
    //gets模式
    off_t clientFileSize=0;
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"broken")==0){
        printf("gets ERROR: 客户端未确认继续传输\n");
        return 0;
    }else if(strcmp(fileData.dataBuf,"continue")==0){//续传
        printf("gets MODE: 续传\n");
        GET_FILEDATA;
        memcpy(&clientFileSize,fileData.dataBuf,sizeof(clientFileSize));
        printf("gets continue:now filesize=%ld\n",clientFileSize);
    }else{
        printf("gets MODE: 正常\n");
    }
    //发送文件大小
    struct stat state_buf;
    ret=stat(trueFilename,&state_buf);
    ERROR_CHECK(ret,-1,"stat");
    filesize=state_buf.st_size;
    printf("gets filesize=%ld\n",filesize);
    if(clientFileSize>0&&clientFileSize>=filesize){
        SEND_ERROR;
        return 0;
    }else if(clientFileSize>0){
        SEND_SUCCESS;
    }
    bzero(&fileData,sizeof(fileData));
    memcpy(fileData.dataBuf,&filesize,sizeof(filesize));
    fileData.dataLen=sizeof(filesize);
    bzero(sendBuf,sizeof(sendBuf));
    memcpy(sendBuf,&fileData,fileData.dataLen+4);
    ret=send(clientFd,sendBuf,fileData.dataLen+4,0);
    ERROR_CHECK(ret,-1,"send");
    //打开文件
    int fileFd=open(trueFilename,O_RDWR);
    ERROR_CHECK(fileFd,-1,"open");
    if(clientFileSize>0)//续传项目
    {
        ret=lseek(fileFd,clientFileSize,SEEK_SET);
        ERROR_CHECK(ret,-1,"lseek");
    }
    //传输文件
    if(filesize <= 1<<8 || filesize >= 1<<9)//小于100M时或大于1G时
    {
        //发送文件内容
        ret=sendfile(clientFd,fileFd,NULL,filesize);
        ERROR_CHECK(ret,-1,"sendfile");
    }else{//mmap
        char *pMap=(char*)mmap(NULL,filesize-clientFileSize,PROT_READ|PROT_WRITE,MAP_SHARED,fileFd,0);
        ERROR_CHECK(pMap,(char*)-1,"mmap");
        ret=send(clientFd,pMap,filesize-clientFileSize,0);
        ERROR_CHECK(ret,-1,"send");
    }
    close(fileFd);
    return 0;
}

int Command_remove(int clientFd,int *pCode,MYSQL *conn,char *username)
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
    char trueFilename[100]={0};
    char filetype[2]={0};
    printf("remove get:filename\n");
    GET_FILEDATA;
    if(0==fileData.dataLen)
    {
        printf("remove get ERROR:no filename\n");
        return 0;
    }
    strcpy(filename,fileData.dataBuf);
    CONNECT_MYSQL;
    sprintf(query,"select * from file_list where precode=%d and filename='%s' and owner='%s';",code,filename,username);
    printf("remove:select * from file_list where precode=%d and filename='%s' and owner='%s';\n",code,filename,username);
    if(mysql_query(conn,query)){
        printf("remove ERROR:%s\n",mysql_error(conn));
        SEND_ERROR;
        return -1;
    }else{
        res=mysql_use_result(conn);
        row=mysql_fetch_row(res);
        if(row) //存在同名文件
        {
            printf("remove SUCCESS:查询到该文件\n");
            strncpy(filetype,row[4],1);
            if(filetype[0]=='f')
            {
                strcpy(trueFilename,row[5]);
            }
            fileCode=atoi(row[0]);
            SEND_SUCCESS;
        }else{
            printf("remove ERROR:不存在该文件\n");
            SEND_ERROR;
            return 0;
        }
    }
    mysql_close(conn);  
    if(filetype[0]=='f')
    {
        //从数据库删除
        CONNECT_MYSQL;
        bzero(query,sizeof(query));
        sprintf(query,"delete from file_list where code=%d;",fileCode);
        printf("remove:delete from file_list where code=%d;\n",fileCode);
        if(mysql_query(conn,query))
        {
            printf("remove Error making delete:%s\n",mysql_error(conn));
        }else{
            printf("remove:delete file_info in mysql success\n");
        }
        mysql_close(conn);  
        //删除文件
        CONNECT_MYSQL;
        sprintf(query,"select * from file_list where MD5='%s';",trueFilename);
        printf("select * from file_list where MD5='%s';\n",trueFilename);
        if(mysql_query(conn,query)){
            printf("remove ERROR:%s\n",mysql_error(conn));
            return -1;
        }else{
            res=mysql_use_result(conn);
            row=mysql_fetch_row(res);
            if(!row) //不存在同MD5的文件
            {
                unlink(trueFilename); 
            }
        }
        printf("remove:delete file SUCCESS\n");
        mysql_close(conn);  
        SEND_SUCCESS;
    }else{
        CONNECT_MYSQL;
        bzero(query,sizeof(query));
        sprintf(query,"select * from file_list where precode=%d;",fileCode);
        printf("select * from file_list where precode=%d;\n",fileCode);
        if(mysql_query(conn,query)){
            printf("rmdir ERROR:%s\n",mysql_error(conn));
            SEND_ERROR;
            return -1;
        }else{
            res=mysql_use_result(conn);
            row=mysql_fetch_row(res);
            if(row) //文件夹下有文件
            {
                printf("rmdir ERROR:文件夹不为空\n");
                SEND_ERROR;
                GET_FILEDATA;
                if(strcmp(fileData.dataBuf,"N")==0)
                {
                    return 0;
                }else{
                    printf("rmdir:删除文件夹下全部文件\n"); 
                    ret=Rmdir_All(fileCode);
                    if(ret==0)
                    {
                        SEND_SUCCESS;
                    }else{
                        SEND_ERROR;
                    }
                    return 0;
                }
            }else{
                printf("rmdir SUCCESS:文件夹为空\n"); 
            }
        }
        mysql_close(conn); 
        CONNECT_MYSQL;
        bzero(query,sizeof(query));
        sprintf(query,"delete from file_list where code=%d;",fileCode);
        printf("rmdir:delete from file_list where code=%d;\n",fileCode);
        if(mysql_query(conn,query))
        {
            printf("rmdir Error making delete:%s\n",mysql_error(conn));
            SEND_ERROR;
            return -1;
        }else{
            printf("rmdir:delete file_info in mysql success\n");
            SEND_SUCCESS;
        }
        mysql_close(conn);  
        printf("rmdir:delete file SUCCESS\n");
    }
    return 0;
}

int Command_pwd(int clientFd,int *pCode,MYSQL *conn)
{
    int ret;
    File_Data_t fileData;
    char sendBuf[1004]={0};
    bzero(&fileData,sizeof(fileData));
    GET_PATH(*pCode,fileData.dataBuf,conn);
    SEND_FILEDATA;
    return 0;
}

int Command_mkdir(int clientFd,int *pCode,MYSQL *conn,char *username)
{
    CONNECT_MYSQL;
    int ret;
    int code=*pCode;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1000]={0};
    char dirname[50]={0};
    File_Data_t fileData;
    char sendBuf[1004]={0};
    GET_FILEDATA;
    if(0==fileData.dataLen)
    {
        return 0;
    }
    strcpy(dirname,fileData.dataBuf);
    sprintf(query,"select * from file_list where precode=%d and filename='%s' and owner='%s' and filetype='d';",code,dirname,username);
    printf("mkdir:select * from file_list where precode=%d and filename='%s' and owner='%s' and filetype='d';\n",code,dirname,username);
    if(mysql_query(conn,query)){
        printf("mkdir ERROR:%s\n",mysql_error(conn));
        SEND_ERROR;
        return -1;
    }else{
        res=mysql_use_result(conn);
        row=mysql_fetch_row(res);
        if(row) //存在同名文件夹
        {
            printf("mkdir ERROR:存在同名文件夹\n");
            SEND_ERROR;
            return 0;
        }else{
            printf("mkdir SUCCESS:开始创建文件夹\n");    
        }
    }
    //插入数据库
    bzero(query,sizeof(query));
    sprintf(query,"insert into file_list (precode,filename,filesize,filetype,owner) values (%d,'%s',0,'d','%s');",code,dirname,username);
    printf("mkdir:insert into file_list (precode,filename,filesize,filetype,owner) values (%d,'%s',0,'d','%s');\n",code,dirname,username);
    if(mysql_query(conn,query))
    {
        printf("mkdir Error making insert:%s\n",mysql_error(conn));
    }else{
        printf("mkdir:insert success\n");
    }
    SEND_SUCCESS;
    mysql_close(conn);  
    return 0;
}

int Rmdir_All(int dirCode)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1000]={0};
    int *tobeRemove;
    int i=0,count=0;
    CONNECT_MYSQL;
    sprintf(query,"select * from file_list where precode=%d;",dirCode);
    printf("remove_all: select * from file_list where precode=%d;\n",dirCode);
    if(mysql_query(conn,query)){
        printf("remove_all ERROR:%s\n",mysql_error(conn));
        return -1;
    }else{
        res=mysql_use_result(conn);
        while((row=mysql_fetch_row(res)))
        {
            ++count;
        }
    }
    mysql_close(conn);
    if(count>0)//文件夹下有文件
    {
        tobeRemove=(int*)calloc(count+1,sizeof(int));
        CONNECT_MYSQL;
        sprintf(query,"select * from file_list where precode=%d;",dirCode);
        printf("remove_all: select * from file_list where precode=%d;\n",dirCode);
        if(mysql_query(conn,query)){
            printf("remove_all ERROR:%s\n",mysql_error(conn));
            return -1;
        }else{
            res=mysql_use_result(conn);
            while((row=mysql_fetch_row(res))&&i<count)
            {
                tobeRemove[i]=atoi(row[0]);
                ++i;
            }
        }
        mysql_close(conn);
        for(i=0;i<count;++i)
        {
            Rmdir_All(tobeRemove[i]);//递归删除
        }
    }
    //查询文件类型
    char filetype[2]={0};
    char trueFilename[100]={0};
    CONNECT_MYSQL;
    sprintf(query,"select * from file_list where code=%d;",dirCode);
    printf("remove_all: select * from file_list where code=%d;\n",dirCode);
    if(mysql_query(conn,query)){
        printf("remove_all ERROR:%s\n",mysql_error(conn));
        return -1;
    }else{
        res=mysql_use_result(conn);
        row=mysql_fetch_row(res);
        strncpy(filetype,row[4],1);
        if(filetype[0]=='f')
        {
            strcpy(trueFilename,row[5]);
        }
    }
    mysql_close(conn);
    //删除
    if(filetype[0]=='f')
    {
        //从数据库删除
        CONNECT_MYSQL;
        bzero(query,sizeof(query));
        sprintf(query,"delete from file_list where code=%d;",dirCode);
        printf("remove:delete from file_list where code=%d;\n",dirCode);
        if(mysql_query(conn,query))
        {
            printf("remove Error making delete:%s\n",mysql_error(conn));
            return -1;
        }else{
            printf("remove:delete file_info in mysql success\n");
        }
        mysql_close(conn);  
        //删除文件
        CONNECT_MYSQL;
        sprintf(query,"select * from file_list where MD5='%s';",trueFilename);
        printf("select * from file_list where MD5='%s';\n",trueFilename);
        if(mysql_query(conn,query)){
            printf("remove ERROR:%s\n",mysql_error(conn));
            return -1;
        }else{
            res=mysql_use_result(conn);
            row=mysql_fetch_row(res);
            if(!row) //不存在同MD5的文件
            {
                unlink(trueFilename); 
            }
        }
        printf("remove:delete file SUCCESS\n");
        mysql_close(conn);
    }else{//删除数据库中的文件夹
        CONNECT_MYSQL;
        bzero(query,sizeof(query));
        sprintf(query,"delete from file_list where code=%d;",dirCode);
        printf("rmdir:delete from file_list where code=%d;\n",dirCode);
        if(mysql_query(conn,query))
        {
            printf("rmdir Error making delete:%s\n",mysql_error(conn));
            return -1;
        }else{
            printf("rmdir:delete file_info in mysql success\n");
        }
        mysql_close(conn);  
        printf("rmdir:delete file SUCCESS\n");
    }
    printf("remove_all:delete file %d SUCCESS\n",dirCode);
    return 0;
}