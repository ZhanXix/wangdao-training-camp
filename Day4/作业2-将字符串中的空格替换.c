/*
2.将 字 符 串 中 的 空 格 替 换 成 “%020”，
例 如 “hello   world   how     ”
->”hello%020%020%020world%020%020%020how%020%020%020%020”

*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* str;
	str = (char*)malloc(11);
	int now;	//表示当前处理位置
	int count;	//表示当前字符串的空格数
	printf("输入一串字符串(最长10个字符)：\n");
	while (gets(str) != NULL)
	{
		count = 0;
		for (now = 0; now < strlen(str); ++now)
		{
			if (str[now] == ' ')
			{
				++count;
			}
		}
		str = (char*)realloc(str, strlen(str) + count * 3 + 1);//开辟新空间
		int len = strlen(str) + count * 3 + 1;
		for (now = 0; now < strlen(str); ++now)
		{
			if (str[now] == ' ')
			{
				for (int i = len - 1; i >= now + 4; --i)
				{
					str[i] = str[i - 3];//向后移三位
				}
				str[now] = '%';
				str[++now] = '0';
				str[++now] = '2';
				str[now + 1] = '0';
			}
		}
		printf("处理结果：");
		puts(str);
		printf("\n输入一串包含字符和数字的字符串(最长50个字符)：\n");
		memset(str, 0, strlen(str));
	}
	free(str);
	str = NULL;
	system("pause");
}

//教学：从后往前放，可以避免覆盖