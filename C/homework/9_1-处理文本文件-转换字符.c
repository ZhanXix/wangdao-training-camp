/*
将《The_Holy_Bible.txt》中的标点符号替换成空格，大写字母转换成小写字母并将处理过的文本保存到“The_Holy_Bible_Res.txt”中。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fpIn, * fpOut;
	char buf[5000];
	int i;
	fpIn = fopen("The_Holy_Bible.txt", "r");
	fpOut = fopen("The_Holy_Bible_Res.txt", "w");
	if (NULL == fpIn || NULL == fpOut)
	{
		perror("fopen");
		goto error;
	}
	while (memset(buf, 0, sizeof(buf)), (fgets(buf, sizeof(buf), fpIn)) != NULL)//读一行
	{
		for (i = 0; i < strlen(buf); ++i)	//处理这行字符
		{
			if (buf[i] >= 'A' && buf[i] <= 'Z')
			{
				buf[i] += 32;	//大写字母转换为小写
			}
			else if ((buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= '0' && buf[i] <= '9') || buf[i] == ' '|| buf[i] == '\t' || buf[i] == '\n')
			{
				continue;	//排除字母、数字、空格、横向制表、换行
			}
			else
			{
				buf[i] = ' ';	//其他符号转换为空格
			}
		}
		fputs(buf, fpOut);
		//puts(buf);	//本行用于调试
	}
	fclose(fpIn);
	fclose(fpOut);
error:
	system("pause");
}