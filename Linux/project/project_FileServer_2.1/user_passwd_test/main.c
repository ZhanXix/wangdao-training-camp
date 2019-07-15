#define _XOPEN_SOURCE 
#include "func.h"
#include <unistd.h>
int Make_Salt(char *salt)//产生一个15位的字符串
{
    salt[0]='$';
    salt[1]='6';
    salt[2]='$';
    srand(time(NULL)); 
    int flag=0;
    for(int i=3;i<11;++i)
    {
        flag=rand()%3;
        switch (flag)
        {
        case 0:
            salt[i]='a'+rand()%26;
            break;
        case 1:
            salt[i]='A'+rand()%26;
            break;
        case 2:
            salt[i]='0'+rand()%10;
            break;
        default:
            return -1;
            break;
        }
    }
    printf("MAKE_SALT:salt=%s\n",salt);
    return 0;
}

int main()
{
    char username[40]={0};
    char salt[12]={0};
    char *buf;
    buf=(char*)calloc(100,sizeof(char));
    read(STDIN_FILENO,username,sizeof(username));
    Make_Salt(salt);
    //strcat(salt,username);
    buf=crypt(username,salt);
    puts(buf);
    printf("%ld\n",strlen(buf));
    return 0;
}