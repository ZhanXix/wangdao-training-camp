#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* fp;
	char c;
	int ret;
	char buf[5000];
	fp = fopen("file.txt‪","r+");	//可以是相对路径（相对于当前目录的路径），也可以是绝对路径（从盘符开始的路径）
	if (NULL == fp)
	{
		perror("fopen");
		goto error;
	}
	//while ((c = fgetc(fp)) != EOF)
	//{
	//	putchar(c);
	//}
	//c = 'H';
	//ret=fputc(c, fp);
	//if (EOF == ret)
	//{
	//	perror("fputc");
	//	goto error;
	//}
	while (memset(buf,0, sizeof(buf)),(fgets(buf, sizeof(buf), fp)) != NULL)//读一行
	{
		puts(buf);
	}
	fclose(fp);
error:
	system("pause");
}