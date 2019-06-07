/*输入一行字符串，把字符串翻转 。
Input: I____am__a__student
Output: student__a__am____I

（1）直接翻转一下
（2）把每个单词找出来，原地自身翻转
*/

#include <stdio.h>
#include <stdlib.h> 

void overreturn(char str[],int wordlen)	
//翻转函数——str为翻转的首地址，wordlen为需要翻转的长度
{
	int i,j;
	char temp;
	for (i = 0, j = wordlen - 1; i < j; ++i, --j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}
int main()
{
	char str[50] = { 0 };
	int  i = 0, flag = 0,wordlen=0;
	char* head = 0;
	printf("输入一个长度小于50的字符串(单词+若干空格)：\n");
	while (gets(str) != NULL)
	{
		printf("翻转句子：\n");
		overreturn(str, strlen(str));
		puts(str);
		printf("原句子：\n");
		overreturn(str, strlen(str));
		puts(str);
		printf("翻转单词：\n");
		for (flag = 0, i = 0, wordlen = 0, head = 0; str[i] != 0; ++i)
		{
			if (flag == 0 && str[i] != ' ')	//当前遇到新单词首
			{
				overreturn(head, wordlen);
				head = &str[i];
				wordlen = 1;
				flag = 1;
			}
			else if (flag && str[i] == ' ')	//当前遇到第一个空格
			{
				flag = 0;
			}
			else if (str[i] != ' ')
			{
				++wordlen;
			}	
		}
		overreturn(head, wordlen);
		puts(str);
		printf("\n输入一个长度小于50的字符串(单词+若干空格)：\n");
		memset(str, '\0', 50);
	}
	system("pause");
}
