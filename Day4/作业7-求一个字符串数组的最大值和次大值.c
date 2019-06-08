/*
求一个字符串数组的最大值和次大值  void big(char *arr[],int size ,char** big1,char** big2)
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	char* str;
	char Max, secMax;
	int len;
	printf("输入需要处理的字符串最大长度：\n");
	while (scanf("%d", &len) != EOF)
	{
		str = (int*)malloc(len + 1);
		printf("输入需要处理的字符串：\n");
		rewind(stdin);
		gets(str);
		Max = str[0];
		for (int i = 0; i < len; ++i)
		{
			if (str[i] > Max) {
				secMax = Max;
				Max = str[i];
			}
		}
		printf("字符串最大值为：%c\n",Max);
		printf("字符串次大值为：%c\n", secMax);
		free(str);
		str = NULL;
		printf("\n输入需要处理的字符串最大长度：\n");
	}
	system("pause");
}