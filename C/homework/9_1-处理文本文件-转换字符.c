/*
����The_Holy_Bible.txt���еı������滻�ɿո񣬴�д��ĸת����Сд��ĸ������������ı����浽��The_Holy_Bible_Res.txt���С�
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
	while (memset(buf, 0, sizeof(buf)), (fgets(buf, sizeof(buf), fpIn)) != NULL)//��һ��
	{
		for (i = 0; i < strlen(buf); ++i)	//���������ַ�
		{
			if (buf[i] >= 'A' && buf[i] <= 'Z')
			{
				buf[i] += 32;	//��д��ĸת��ΪСд
			}
			else if ((buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= '0' && buf[i] <= '9') || buf[i] == ' '|| buf[i] == '\t' || buf[i] == '\n')
			{
				continue;	//�ų���ĸ�����֡��ո񡢺����Ʊ�����
			}
			else
			{
				buf[i] = ' ';	//��������ת��Ϊ�ո�
			}
		}
		fputs(buf, fpOut);
		//puts(buf);	//�������ڵ���
	}
	fclose(fpIn);
	fclose(fpOut);
error:
	system("pause");
}