#include <stdio.h> 
#include <stdlib.h> 

size_t mystrlen(char str[])
{
	size_t len = 0;
	while (str[len])
	{
		++len;
	}
	return len;
}
void mystrcpy(char to[],char from[])
{
	int i = 0;
	memset(to, '\0', 50);
	while (from[i])
	{
		to[i] = from[i];
		++i;
	}
	to[i] = '\0';
}
int mystrcmp(char str1[], char str2[])	//若字符串相同返回0，若str1<str2返回-1,str1>str2返回1
{
	int i;
	int flag = 0;	//比较标记
	for (i = 0; i < mystrlen(str1) && i < mystrlen(str2); ++i)
	{
		if (str1[i] > str2[i])
		{
			flag = 1;
			break;
		}
		else if(str1[i] < str2[i])
		{
			flag = -1;
			break;
		}
	}
	if (flag == 0 && mystrlen(str1) != mystrlen(str2))
	{
		if (mystrlen(str1) > mystrlen(str2))
		{
			flag = 1;
		}
		else
		{
			flag = -1;
		}
	}
	return flag;
}
void mystrcat(char to[], char from[])
{
	int i = mystrlen(to);	//直接从to的最后一个字符后开始
	for (int j = 0; j <= mystrlen(from); ++j, ++i)	//这里用<=的原因是复制from字符串的最后一个'\0'
	{
		to[i] = from[j];
	}
}
int main()
{
	char s1[50] = { 0 }, s2[50] = { 0 };
lable:	//标签用于多次调试
	printf("输入两个长度小于25的字符串s1、s2：\n");
	rewind(stdin);	//去除缓冲区内容
	memset(s1, '\0', 50);
	memset(s2, '\0', 50);
	gets(s1);
	gets(s2);
	printf("s1的长度为%d，s2的长度为%d\n",mystrlen(s1),mystrlen(s2));
	printf("s1与s2的比较结果为：");
	if (mystrcmp(s1, s2)==1)
	{
		printf("s1大于s2\n");
	}
	else if (mystrcmp(s1, s2) == -1)
	{
		printf("s1小于s2\n");
	}
	else
	{
		printf("s1等于s2\n");
	}
	printf("s1 = %s\n", s1);
	printf("s2 = %s\n", s2);
	printf("将s2剪切到s1后：\n");
	mystrcat(s1, s2);
	printf("s1 = %s\n",s1);
	printf("将s2复制到s1：\n");
	mystrcpy(s1, s2);
	printf("s1 = %s\n\n", s1);
	printf("...输入y继续：\n");
	if (getchar() == 'y')
	{
		goto lable;
	}
	return 0;
}
