/*
�����⣺�������ӷ��� ʵ�����ⷶΧ�����������ļӷ��� �����ķ�Χ�� int �͵ı����޷���ʾ,50λ��
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char num1[51] = { 0 }, num2[51] = { 0 }, result[52] = { 0 };
	int p1, p2, p3;
	printf("����������������\n");
	gets(num1);
	gets(num2);
	p1 = strlen(num1) - 1;
	p2 = strlen(num2) - 1;
	p3 = 50;
	while (p1 >= 0&&p2 >= 0)
	{
		result[p3] += num1[p1] + num2[p2] - 2 * '0';
		if (result[p3] > 9)
		{
			result[p3] -= 10;
			result[p3-1]++;	//��λ
		}
		p1--;
		p2--;
		p3--;
	}
	while (p1 >= 0)
	{
		result[p3] += num1[p1] - '0';
		if (result[p3] > 9)
		{
			result[p3] -= 10;
			result[p3-1]++;	//��λ
		}
		p1--;
		p3--;
	}
	while (p2 >= 0)
	{
		result[p3] += num2[p2] - '0';
		if (result[p3] > 9)
		{
			result[p3] -= 10;
			result[p3-1]++;	//��λ
		}
		p2--;
		p3--;
	}
	printf("add result = ");
	for (p3 = 0; p3 < 52; p3++)
	{
		if (result[p3]) break;
	}
	for (; p3 < 51; p3++)
	{
		putchar(result[p3] + '0');
	}
	putchar('\n');
	system("pause");
}