/*
���������գ�����������ǵ���ĵڼ��졣
*/

#include <stdio.h> 
#include <stdlib.h> 

int main()
{
	int monthDay[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int year, month, day;
	int result = 0;
	printf("���������գ�\n");
	scanf("%d%d%d", &year, &month, &day);
	for (int i = 0; i < month - 1; ++i)
	{
		result += monthDay[i];
		if(i==1)//���Ƕ���
		{
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			{
				++result;
			}
		}
	}
	result += day;
	printf("���ǵ���ĵ�%d��\n", result);
	system("pause");
}