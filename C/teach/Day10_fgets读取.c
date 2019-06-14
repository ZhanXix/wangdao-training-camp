#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])	//��������������������������exe�������һ��������
{
	int i;
	char buf[1024];
	FILE* fp;
	if (argc != 2)
	{
		printf("error args\n");
		goto error;
	}
	fp = fopen(argv[1], "r+");
	if (NULL == fp)
	{
		perror("fopen");
		goto error;
	}
	while (memset(buf, 0, sizeof(buf)), (fgets(buf, sizeof(buf), fp)) != NULL)
	{
		buf[0] -= 32;	//������ĸ��Ϊ��д
		if ('\n' == buf[strlen(buf) - 1])	//�ַ�������\n����Ҫ��ǰ��ƫ��һ���ַ�
		{
			fseek(fp, -strlen(buf) - 1, SEEK_CUR);
		}
		else
		{
			fseek(fp, -strlen(buf), SEEK_CUR);
		}
		fputs(buf, fp);
		fseek(fp, 0, SEEK_CUR);
	}
	fclose(fp);
error:
	system("pause");
}