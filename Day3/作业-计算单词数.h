#include <stdio.h>
#include <stdlib.h> 

int main()
{
	char str[50] = { 0 };
	int count = 0, i = 0, flag = 0;	
	printf("输入一个长度小于50的字符串(单词+若干空格)：\n");
	while (gets(str) != NULL)
	{
		for (flag = 0, count = 0, i = 0; str[i] != 0; ++i)
		{
			if (flag == 0 && str[i] != ' ')	//当前遇到新单词首
			{
				++count;
				flag = 1;
			}
			else if (str[i] == ' ')//当前遇到空格
			{
				flag = 0;
			}
		}
		printf("单词数为%d\n\n", count);
		printf("输入一个长度小于50的字符串(单词+若干空格)：\n");
	}
	system("pause");
}
