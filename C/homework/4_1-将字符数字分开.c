/*
1.�������ַ����ֵ��ַ����ֿ�,ʹ�÷ֿ�����ַ���ǰһ���������ֺ�һ��������ĸ��
���硰h1ell2o3�� ->��123hello��
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char str[51] = { 0 };
	int lastNum;	//��ʾ���һ���ź������������λ��
	int now;	//��ʾ��ǰ����λ��
	char temp;
	printf("����һ�������ַ������ֵ��ַ���(�50���ַ�)��\n");
	while (gets(str) != 0)
	{
		for (lastNum = 0, now = 0; now < strlen(str); ++now)
		{
			if (str[now] >= '0' && str[now] <= '9')
			{
				temp = str[now];
				for (int i = now; i > lastNum; --i)
				{//��֮ǰ����ĸ�����λ
					str[i] = str[i - 1];
				}
				str[lastNum] = temp;
				lastNum++;
			}
		}
		printf("��������");
		puts(str);
		printf("\n����һ�������ַ������ֵ��ַ���(�50���ַ�)��\n");
	}
	system("pause");
}

/*
* ��ѧ����O(1)ʵ�֣�����ʹ�ÿ��ŵ�˼�룬�����ַŵ�ǰ�棬����ĸ�ŵ�����
* ��������ֱ�ӽ�������Ӧ��ʹ�ò�������˼�룬ÿ���ƶ�һ���ַ������Ա���˳�����
* �ƶ�һ���ַ�������memmove
*/