/*
输入一个年份, 月份，输出该月份的日历。
*/

#include <stdio.h> 
#include <stdlib.h> 

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
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
int diffofTwoday(int year1, int month1, int day1, int year2, int month2, int day2)
{
	int result = 0;
	if ((year1 > year2) || (year1 == year2 && month1 > month2) || (year1 == year2 && month1 == month2 && day1 > day2))
	{
		swap(&year1, &year2);
		swap(&month1, &month2);
		swap(&day1, &day2);
	}
	for (int i = year1; i < year2; ++i)
	{//计算两个年之间的差值
		result += 365;
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
		{//考虑闰年
			++result;
		}
	}
	result -= dayofyear(year1, month1, day1);
	result += dayofyear(year2, month2, day2);
	return result;
}
int dayofweek(int year2, int month2, int day2)
{
	int year1 = 2019, month1 = 6, day1 = 9;
	int week1 = 7;
	int week2 = 0, diff = 0;
	diff = diffofTwoday(year1, month1, day1, year2, month2, day2);
	if ((year1 > year2) || (year1 == year2 && month1 > month2) || (year1 == year2 && month1 == month2 && day1 > day2))
	{
		week2 = (7 - diff % 7) % 7;
	}
	else
	{
		week2 = diff % 7;
	}
	return week2;
}
int main()
{
	int year, month;
	int fisrtdayofweek;
	int day[42] = { 0 };
	char* week[7] = { "SUN","MON","TUE","WED","THU","FRI","SAT" };
	int monthDay[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	printf("输入要打印日历的年月：\n");
	scanf("%d%d", &year, &month);
	fisrtdayofweek = dayofweek(year, month, 1);
	for (int i = fisrtdayofweek, j = 1; j <= monthDay[month-1]; ++i, ++j)
	{
		day[i] = j;
	}
	putchar('|');
	for (int i = 0; i < 29; ++i)
	{
		putchar('-');
	}
	printf("|\n|");
	for (int i = 0; i < 7; ++i)
	{
		printf(" %s",week[i]);
	}
	printf(" |\n");
	for (int i = 0; i < 42; ++i)
	{
		if (i == 35 && day[i] == 0)
		{
			break;
		}
		if (i % 7 == 0)
		{
			putchar('|');
		}
		if (day[i] > 0)
		{
			printf("%4d", day[i]);
		}
		else
		{
			printf("    ");
		}
		if (i % 7 == 6)
		{
			printf(" |\n");
		}
	}
	putchar('|');
	for (int i = 0; i < 29; ++i)
	{
		putchar('-');
	}
	printf("|\n");
	system("pause");
}