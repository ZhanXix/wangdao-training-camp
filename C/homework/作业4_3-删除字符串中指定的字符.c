/*
3.ɾ���ַ�����ָ�����ַ��� ���� ��abcdaefaghiagkl�� ɾ����a��,�Ժ� ��bcdefghigkl��
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char str[51] = { 0 };
	char c;
	int count, i;
	printf("�����ַ���(�50���ַ�)��\n");
	while (gets(str) != 0)
	{
		printf("������Ҫɾ����һ���ַ���\n");
		c = getchar();
		rewind(stdin);
		count = 0; //count��ʾ��ǰ��Ҫ��λ����Ŀ
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
		str[strlen(str) - count] = 0;//����Ͻ�����
		printf("��������");
		puts(str);
		printf("\n�����ַ���(�50���ַ�)��\n");
		memset(str, 0, strlen(str));
	}
	system("pause");
}