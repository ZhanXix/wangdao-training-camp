/*
2.�� �� �� �� �� �� �� �� �� �� �� ��%020����
�� �� ��hello   world   how     ��
->��hello%020%020%020world%020%020%020how%020%020%020%020��

*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* str;
	str = (char*)malloc(11);
	int now;	//��ʾ��ǰ����λ��
	int count;	//��ʾ��ǰ�ַ����Ŀո���
	printf("����һ���ַ���(�10���ַ�)��\n");
	while (gets(str) != NULL)
	{
		count = 0;
		for (now = 0; now < strlen(str); ++now)
		{
			if (str[now] == ' ')
			{
				++count;
			}
		}
		str = (char*)realloc(str, strlen(str) + count * 3 + 1);//�����¿ռ�
		int len = strlen(str) + count * 3 + 1;
		for (now = 0; now < strlen(str); ++now)
		{
			if (str[now] == ' ')
			{
				for (int i = len - 1; i >= now + 4; --i)
				{
					str[i] = str[i - 3];//�������λ
				}
				str[now] = '%';
				str[++now] = '0';
				str[++now] = '2';
				str[now + 1] = '0';
			}
		}
		printf("��������");
		puts(str);
		printf("\n����һ�������ַ������ֵ��ַ���(�50���ַ�)��\n");
		memset(str, 0, strlen(str));
	}
	free(str);
	str = NULL;
	system("pause");
}

//��ѧ���Ӻ���ǰ�ţ����Ա��⸲��