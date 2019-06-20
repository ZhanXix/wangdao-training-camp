//定义一个学生结构体类型struct student，里边含有学号，姓名，分数，定义结构体数组struct student s[3],给数组赋初值后，写入文件，然后通过lseek偏移到开头，然后再读取进行打印输出

#include <func.h>

typedef struct student
{
    int id;
    char name[20];
    double score;
}stu_t;

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd,ret,len=0;
    fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0755);
    ERROR_CHECK(fd,-1,"open");
    stu_t s[3];
    char buf[128];
    printf("输出三位学生的信息(学号、姓名、分数):\n");
    for(int i=0;i<3;++i)
    {
        ret=scanf("%d%s%lf",&s[i].id,s[i].name,&s[i].score);
    }
    for(int i=0;i<3;++i)
    {
        memset(buf,0,sizeof(buf));
        sprintf(buf,"%d %s %.2lf\n",s[i].id,s[i].name,s[i].score);
        ret=write(fd,buf,strlen(buf));
        len+=strlen(buf);
        ERROR_CHECK(ret,-1,"write");
    }
    lseek(fd,-len,SEEK_CUR);
    printf("---------------------------------\n");
    while((ret=read(fd,buf,sizeof(buf)))>0)
    {
        printf("%s",buf);
    }
    close(fd);
    return 0;
}
