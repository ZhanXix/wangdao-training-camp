/*
��һ���ַ�����������ֵ�ʹδ�ֵ  void big(char *arr[],int size ,char** big1,char** big2)
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	char* str;
	char Max, secMax;
	int len;
	printf("������Ҫ������ַ�����󳤶ȣ�\n");
	while (scanf("%d", &len) != EOF)
	{
		str = (int*)malloc(len + 1);
		printf("������Ҫ������ַ�����\n");
		rewind(stdin);
		gets(str);
		Max = str[0];
		for (int i = 0; i < len; ++i)
		{
			if (str[i] > Max) {
				secMax = Max;
				Max = str[i];
			}
		}
		printf("�ַ������ֵΪ��%c\n",Max);
		printf("�ַ����δ�ֵΪ��%c\n", secMax);
		free(str);
		str = NULL;
		printf("\n������Ҫ������ַ�����󳤶ȣ�\n");
	}
	system("pause");
}