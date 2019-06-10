/*
输入 一个日期 和一个整数 n，输出从该日期起经过n天以后的日期。
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
		if (i == 1)//考虑二月
		{
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			{//考虑闰年
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
	printf("输入某个日期（年月日）：\n");
	scanf("%d%d%d", &year1, &month1, &day1);
	year2 = year1;
	printf("输入经过天数：\n");
	scanf("%d", &diff);
	diff += dayofyear(year1, month1, day1);
	while(diff>365)
	{
		diff -= 365;
		if ((year2 % 4 == 0 && year2 % 100 != 0) || year2 % 400 == 0)
		{//考虑闰年
			diff--;
		}
		year2++;
	}
	if (diff == 0)
	{//考虑恰好是闰年最后一天的情况
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
	printf("这些天后是%d年%d月%d日\n", year2,month2,day2);
}