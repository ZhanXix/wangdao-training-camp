//用C语言实现学生选择某个老师的课

#include "func.h"
#include <mysql/mysql.h>

int main(int argc,char *argv[])//第一个参数是学号，第二个参数是课程编号
{
    ARGS_CHECK(argc,3);
    MYSQL *connect;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *host="localhost";
    char *user="root";
    char *password="";
    char *database="day19_homework";
    connect=mysql_init(NULL);
    if(!mysql_real_connect(connect,host,user,password,database,0,NULL,0))
    {
        printf("连接数据库失败！\n");
    }else{
        printf("数据库已连接...\n");
    }
    char query[200]="select * from choose_course where";
    sprintf(query,"%s student_id=%s and course_id=%s;",query,argv[1],argv[2]);
    char insert[200]="insert into choose_course values";
    sprintf(insert,"%s(%s,%s);",insert,argv[1],argv[2]);
    if(mysql_query(connect,query))
    {
        printf("查询出错:%s\n",mysql_error(connect));
    }else{
        res=mysql_use_result(connect);
        row=mysql_fetch_row(res);
        if(row)
        {
            printf("请勿重复选课！\n");
        }else{
            if(mysql_query(connect,insert))
            {
                printf("选课失败！请确认数据是否正确\n");
            }else{
                printf("选课成功！\n");
            }
        }
        mysql_free_result(res);
    }
    mysql_close(connect);
    return 0;
}