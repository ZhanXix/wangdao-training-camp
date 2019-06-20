#include <func.h>

int main(int args,char *argv[])
{
    ARGS_CHECK(args,2);
    DIR* dir;
    dir=opendir(argv[1]);
    ERROR_CHECK(dir,NULL,"opendir");
    struct dirent *p;
    off_t pos;
    while(p=readdir(dir))
    {
        printf("ino=%ld len=%d type=%d filename=%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
        if(!strcmp(p->d_name,"a.out"))
        {
            pos=telldir(dir);
        }
    }
    seekdir(dir,pos);
    printf("--------------------------------\n");
    p=readdir(dir);
    printf("ino=%ld len=%d type=%d filename=%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
    closedir(dir);
    return 0;
}
