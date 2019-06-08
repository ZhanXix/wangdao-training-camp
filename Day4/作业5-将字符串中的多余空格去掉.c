/*
将 字 符 串 中 的 相 邻 的 多 余 空 格 去 掉 ，
例 如 （空 格 用 下 划 线 表 示）：
”___hello____world___how_are_you__” ->”hello_world_how_are_you”
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* str;
	int flag, count, len;
	printf("输入需要处理的字符串长度：\n");
	while (scanf("%d", &len) != EOF)
	{
		str = (int*)malloc(len + 1);
		printf("输入需要处理的字符串：\n");
		rewind(stdin);
		gets(str);
		count = 0;//当前需要移位的数目
		flag = 0;//0表示当前的空格是第一个空格，1表示是多余空格
		for (int i = 0; i < len; ++i)
		{
			if (str[i] == ' ' && flag)
			{
				count++;
			}
			else if (str[i] == ' ')
			{
				str[i - count] = str[i];
				flag = 1;	//下一个空格多余
			}
			else
			{//当前遇到非空格
				str[i - count] = str[i];
				flag = 0;	//下一个空格不多余
			}
		}
		str[len - count] = 0;//最后补上结束符
		printf("处理结果：");
		puts(str);
		free(str);
		str = NULL;
		printf("\n\n输入需要处理的字符串长度：\n");
	}
	system("pause");
}
