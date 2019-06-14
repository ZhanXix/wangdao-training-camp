/*
3.删除字符串中指定的字符。 例如 “abcdaefaghiagkl“ 删除‘a’,以后： “bcdefghigkl”
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char str[51] = { 0 };
	char c;
	int count, i;
	printf("输入字符串(最长50个字符)：\n");
	while (gets(str) != 0)
	{
		printf("输入想要删除的一个字符：\n");
		c = getchar();
		rewind(stdin);
		count = 0; //count表示当前需要移位的数目
		for (i = 0; i < strlen(str); ++i)
		{
			if (str[i] == c)
			{
				count++;
			}
			else
			{
				str[i - count] = str[i];
			}
		}
		str[strlen(str) - count] = 0;//最后补上结束符
		printf("处理结果：");
		puts(str);
		printf("\n输入字符串(最长50个字符)：\n");
		memset(str, 0, strlen(str));
	}
	system("pause");
}