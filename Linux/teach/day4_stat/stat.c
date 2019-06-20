#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int ret;
    struct stat buf;
    ret=stat(argv[1],&buf);//传出参数
    ERROR_CHECK(ret,-1,"stat");
    printf("%x %ld %s %s %ld %s\n",buf.st_mode,buf.st_nlink,getpwuid (buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,ctime(&buf.st_mtime));
    return 0;
}
