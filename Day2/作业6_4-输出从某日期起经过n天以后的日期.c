/*
���� һ������ ��һ������ n������Ӹ������𾭹�n���Ժ�����ڡ�
 -> date -> tomorrow of the date
*/
#include <stdio.h> 
#include <stdlib.h> 

int dayofyear(int year, int month, int day)
{
	int monthDay[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int result = 0;
	for (int i = 0; i < month - 1; ++i)
	{
		result += monthDay[i];
		if (i == 1)//���Ƕ���
		{
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			{//��������
				++result;
			}
		}
	}
	result += day;
	return result;
}
int main()
{
	int year1, month1, day1, year2, month2, day2;
	int diff = 0;
	printf("����ĳ�����ڣ������գ���\n");
	scanf("%d%d%d", &year1, &month1, &day1);
	year2 = year1;
	printf("���뾭��������\n");
	scanf("%d", &diff);
	diff += dayofyear(year1, month1, day1);
	while(diff>365)
	{
		diff -= 365;
		if ((year2 % 4 == 0 && year2 % 100 != 0) || year2 % 400 == 0)
		{//��������
			diff--;
		}
		year2++;
	}
	if (diff == 0)
	{//����ǡ�����������һ������
		diff += 366;
		year2--;
	}
	int monthDay[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	month2 = 0;
	while (diff > monthDay[month2])
	{
		diff -= monthDay[month2];
		month2++;
	}
	month2++;
	day2 = diff;
	printf("��Щ�����%d��%d��%d��\n", year2,month2,day2);
}