#include <func.h>

int main(int argc,char *argv[])
{
    time_t now;
    time(&now);
    struct tm *p;
    p=gmtime(&now);
    printf("%04d-%02d-%02d %02d:%02d:%02d %d %d\n",\
           p->tm_year+1900,p->tm_mon+1,p->tm_mday,p->tm_hour+8,p->tm_min,p->tm_sec,p->tm_wday,p->tm_yday);
    return 0;
}

