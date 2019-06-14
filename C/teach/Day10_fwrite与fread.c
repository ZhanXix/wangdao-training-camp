#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fp;
	char str[20] = "hello\nworld";
	int val = 20000;	//20 4e 00 00   写整型、浮点型是无法所见即所得的
	int ret;
	fp = fopen("file.txt", "r+");
	if (NULL == fp)
	{
		perror("fopen");
		goto error;
	}
	val = strlen(str);
	ret = fwrite(str, sizeof(char), strlen(str), fp);
	ret = fseek(fp, -12, SEEK_CUR);	//由于文本模式中\n被存为\r\n，所以这里偏移12个字符
	if (ret != 0)
	{
		perror("fseek");
		goto error;
	}
	//ret = fwrite(&val, sizeof(int), 1, fp);	
	//val = 0;
	//ret = fread(&val, sizeof(int), 1, fp);
	memset(str, 0, sizeof(str));
	ret = fread(str, sizeof(char), sizeof(str), fp);
	fclose(fp);
error:
	system("pause");
}