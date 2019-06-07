/*输入一行字符串（单词和若干空格），输出该行单词（每个单词一行）
Input：____hello_________world_ how___are___you___\n

Output: hello
	world
	how
	are
	you
*/

#include <stdio.h>
#include <stdlib.h> 

int main()
{
	char str[50] = { 0 };
	int  i = 0, flag = 0;
	printf("输入一个长度小于50的字符串(单词+若干空格)：\n");
	while (gets(str) != NULL)
	{
		printf("单词分别为：\n");
		for (flag = 0, i = 0; str[i] != 0; ++i)
		{
			if (flag == 0 && str[i] != ' ')	//当前遇到新单词首
			{
				flag = 1;
				putchar(str[i]);
			}
			else if (flag && str[i] == ' ')//当前遇到第一个空格
			{
				flag = 0;
				putchar('\n');
			}
			else if (str[i] != ' ')
			{
				putchar(str[i]);
			}
		}
		printf("\n输入一个长度小于50的字符串(单词+若干空格)：\n");
	}
	system("pause");
}
