//传递任意一个目录路径，能够显示该目录的ls -l的效果

#include <func.h>

int print_mode(mode_t mode) //mode是一个16进制数
{
    int tmp=0;
    tmp=mode>>15;
    if(tmp) 
    {
        putchar('-');
    }
    else
    {
        putchar('d');
    }
    tmp=mode>>8;
    char rwx[3]={'r','w','x'};
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<3;++j)
        {
            if(tmp&1)
            {
                putchar(rwx[j]);
            }
            else
            {
                putchar('-');
            }
            tmp=mode>>(8-i*3-j-1);
        }
    }
    return 0;
}
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    DIR *fd;
    fd=opendir(argv[1]);
    ERROR_CHECK(fd,NULL,"opendir");
    int ret;
    ret=chdir(argv[1]);
    ERROR_CHECK(ret,-1,"chdir");
    struct dirent *dir;
    struct stat state_buf;
    struct tm *time;
    const char* mon[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec"};
    while((dir=readdir(fd)))
    {
        if('.'==dir->d_name[0]) //避开隐藏文件，如果需要实现-a效果，删去该if判定即可
        {
            continue;
        }
        ret=stat(dir->d_name,&state_buf);
        ERROR_CHECK(ret,-1,"stat");
        print_mode(state_buf.st_mode);
        printf(" %ld %s %s %10ld ",state_buf.st_nlink,getpwuid(state_buf.st_uid)->pw_name,getgrgid(state_buf.st_gid)->gr_name,state_buf.st_size);
        time=localtime(&state_buf.st_mtime);
        printf("%s %d %02d:%02d ",mon[time->tm_mon],time->tm_mday,time->tm_hour,time->tm_min);
        printf("%s\n",dir->d_name);
    }
    return 0;
}
