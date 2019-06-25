#include <func.h>

int main(int argc,char *argv[])
{
    FILE *fp;
    fp=popen("ls","r");
    ERROR_CHECK(fp,NULL,"popen");
    char buf[128];
    fread(buf,sizeof(char),sizeof(buf)-1,fp);
    printf("buf=%s\n",buf);
    pclose(fp);
    return 0;
}

