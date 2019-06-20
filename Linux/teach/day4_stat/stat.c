#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int ret;
    struct stat buf;
    ret=stat(argv[1],&buf);//传出参数
    ERROR_CHECK(ret,-1,"stat");
    printf("%x %ld %d %d %ld %s\n",buf.st_mode,buf.st_nlink,buf.st_uid,buf.st_gid,buf.st_size,ctime(&buf.st_mtime));
    return 0;
}
