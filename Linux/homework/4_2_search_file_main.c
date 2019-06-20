//传递一个路径名，还有一个文件名，搜索对应路径下是否有该文件，有就打印显示，显示绝对路径

#include <func.h>

int search_file(char *path,char *filename)
{
    DIR *fd;
    struct dirent *dir;
    fd=opendir(path);
    ERROR_CHECK(fd,NULL,"opendir");
    char pathbuf[1024]={0};
    while((dir=readdir(fd)))
    {
        if(!strcmp(dir->d_name,filename))
        {
            printf("%s/%s\n",path,filename);
        }
        if(!strcmp(dir->d_name,".")||!strcmp(dir->d_name,".."))
        {
            continue;
        }
        if(4==dir->d_type)
        {
        sprintf(pathbuf,"%s/%s",path,dir->d_name);
        search_file(pathbuf,filename);    
    }
    }
    closedir(fd);
    return 0;
}
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    search_file(argv[1],argv[2]);
    return 0;
}

