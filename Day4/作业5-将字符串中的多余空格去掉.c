/*
�� �� �� �� �� �� �� �� �� �� �� �� �� ȥ �� ��
�� �� ���� �� �� �� �� �� �� ʾ����
��___hello____world___how_are_you__�� ->��hello_world_how_are_you��
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* str;
	int flag, count, len;
	printf("������Ҫ������ַ������ȣ�\n");
	while (scanf("%d", &len) != EOF)
	{
		str = (int*)malloc(len + 1);
		printf("������Ҫ������ַ�����\n");
		rewind(stdin);
		gets(str);
		count = 0;//��ǰ��Ҫ��λ����Ŀ
		flag = 0;//0��ʾ��ǰ�Ŀո��ǵ�һ���ո�1��ʾ�Ƕ���ո�
		for (int i = 0; i < len; ++i)
		{
			if (str[i] == ' ' && flag)
			{
				count++;
			}
			else if (str[i] == ' ')
			{
				str[i - count] = str[i];
				flag = 1;	//��һ���ո����
			}
			else
			{//��ǰ�����ǿո�
				str[i - count] = str[i];
				flag = 0;	//��һ���ո񲻶���
			}
		}
		str[len - count] = 0;//����Ͻ�����
		printf("��������");
		puts(str);
		free(str);
		str = NULL;
		printf("\n\n������Ҫ������ַ������ȣ�\n");
	}
	system("pause");
}
