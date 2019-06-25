#include <func.h>

int main(int argc,char *argv[])
{
    FILE *fp;
    fp=popen("./add","w");
    ERROR_CHECK(fp,NULL,"popen");
    char buf[128]="3 4";
    fputs(buf,fp);
    pclose(fp);
    return 0;
}

