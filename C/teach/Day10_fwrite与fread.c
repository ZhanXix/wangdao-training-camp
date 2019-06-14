#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fp;
	char str[10] = "20000";
	int val = 20000;	//20 4e 00 00   写整型、浮点型是无法所见即所得的
	int ret;
	fp = fopen("file.txt", "r+");
	if (NULL == fp)
	{
		perror("fopen");
		goto error;
	}
	//ret = fwrite(str, sizeof(char), strlen(str), fp);
	//ret = fwrite(&val, sizeof(int), 1, fp);	
	val = 0;
	ret = fread(&val, sizeof(int), 1, fp);
	fclose(fp);
error:
	system("pause");
}