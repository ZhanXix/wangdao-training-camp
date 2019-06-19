#include <stdio.h>

int multi(int,int);
int main()
{
    int a,b;
    printf("输入两个数字：");
    scanf("%d%d",&a,&b);
    printf("%d * %d = %d\n",a,b,multi(a,b));
    return 0;
}
