#define _XOPEN_SOURCE 
#include "../include/file_server.h"

int SignIn_Deal(int clientFd)
{
    File_Data_t fileData;
    bzero(&fileData,sizeof(fileData));
    char sendBuf[1004]={0};
    char username[40]={0};
    char password[40]={0};
    int ret;
LogIn:
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"signN")==0)
    {
        return 0;
    }
    //得到用户名
    bzero(username,sizeof(username));
    GET_FILEDATA;
    strcpy(username,fileData.dataBuf);
    printf("signIn:username=%s\n",username);
    //查询用户名是否存在
    MYSQL *connect=NULL;
    CONNECT_MYSQL;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[2000]={0};
    bzero(query,sizeof(query));
    sprintf(query,"select * from user_list where username='%s';",username);
    printf("signIn:select * from user_list where username='%s';\n",username);
    if(mysql_query(connect,query)){
        printf("signIn ERROR:%s\n",mysql_error(connect));
        mysql_close(connect); 
        SEND_ERROR;
        goto LogIn;
    }else{
        res=mysql_use_result(connect);
        row=mysql_fetch_row(res);
        if(row)
        {
            printf("signIn ERROR:存在相同用户名\n");
            SEND_ERROR;
            mysql_close(connect);  
            goto LogIn;
        }else{
            printf("signIn SUCCESS:不存在相同用户名\n");
            SEND_SUCCESS;
        }
    }
    mysql_close(connect); 
    //得到一个salt
    char salt[12];
    Make_Salt(salt);
    //收取密码
    GET_FILEDATA;
    strcpy(password,fileData.dataBuf);
    char *shadow;
    shadow=(char*)calloc(100,sizeof(char));
    shadow=crypt(password,salt);
    printf("signIn shadow:%s\n",shadow);
    //插入数据库
    CONNECT_MYSQL;
    bzero(query,sizeof(query));
    sprintf(query,"insert into user_list (username,salt,passwd) values ('%s','%s','%s');",username,salt,shadow);
    printf("insert into user_list (username,salt,passwd) values ('%s','%s','%s');\n",username,salt,shadow);
    if(mysql_query(connect,query)){
        printf("signIn ERROR:%s\n",mysql_error(connect));
        SEND_ERROR;
        mysql_close(connect); 
        goto LogIn;
    }else{
        printf("signIn SUCCESS\n");
        SEND_SUCCESS;
        mysql_close(connect); 
    }
    return 0;
}

int LogIn_Deal(int clientFd,char *username)
{
    File_Data_t fileData;
    bzero(&fileData,sizeof(fileData));
    char sendBuf[1004]={0};
    int ret;
LogIn:
    //接收用户名
    GET_FILEDATA;
    bzero(username,40);
    strncpy(username,fileData.dataBuf,40);
    printf("LogIn:username=%s\n",username);
    //查询用户名是否存在
    MYSQL *connect=NULL;
    CONNECT_MYSQL;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[2000]={0};
    bzero(query,sizeof(query));
    sprintf(query,"select * from user_list where username='%s';",username);
    printf("LogIn:select * from user_list where username='%s';\n",username);
    if(mysql_query(connect,query)){
        printf("LogIn ERROR:%s\n",mysql_error(connect));
        mysql_close(connect); 
        SEND_ERROR;
        goto LogIn;
    }else{
        res=mysql_use_result(connect);
        row=mysql_fetch_row(res);
        if(row)
        {
            printf("LogIn SUCCESS:存在相同用户名\n");
            SEND_SUCCESS;
            //传回salt
            bzero(&fileData,sizeof(fileData));
            strcpy(fileData.dataBuf,row[2]);
            printf("LogIn salt=%s\n",fileData.dataBuf);
            SEND_FILEDATA;
            //传回shadow
            bzero(&fileData,sizeof(fileData));
            strcpy(fileData.dataBuf,row[3]);
            printf("LogIn shadow=%s\n",fileData.dataBuf);
            SEND_FILEDATA;
        }else{
            printf("LogIn ERROR:不存在相同用户名\n");
            SEND_ERROR;
            mysql_close(connect);  
            goto LogIn;
        }
    }
    mysql_close(connect); 
    GET_FILEDATA;
    if(strcmp(fileData.dataBuf,"error")==0){
        printf("LogIn ERROR: 密码错误！\n");
        goto LogIn;
    }
    return 0;
}

int Make_Salt(char *salt)//产生一个11位的随机字符串
{
    salt[0]='$';
    salt[1]='6';
    salt[2]='$';
    srand(time(NULL)); 
    int flag=0;
    for(int i=3;i<11;++i)
    {
        flag=rand()%3;
        switch (flag)
        {
        case 0:
            salt[i]='a'+rand()%26;
            break;
        case 1:
            salt[i]='A'+rand()%26;
            break;
        case 2:
            salt[i]='0'+rand()%10;
            break;
        default:
            return -1;
            break;
        }
    }
    printf("MAKE_SALT:salt=%s\n",salt);
    return 0;
}

