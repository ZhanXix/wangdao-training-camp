#include <stdio.h>

int main()
{
    printf("Hello world\n");
    FILE *fp;
    int i=8^9;
    fp=fopen("noexist","rb+");
    if(NULL==fp)
    {
        perror("fopen");
        return -1;
    }
    return 0;
}

