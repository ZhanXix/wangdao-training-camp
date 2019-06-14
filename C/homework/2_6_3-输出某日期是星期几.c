/*
输入一个日期，输出该日期是星期几。
提示： a. delt % 7   b. (7 – delt % 7) % 7
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
int main()
{
	int year1=2019, month1=6, day1=9;
	int week1 = 7;
	int year2, month2, day2;
	int week2 = 0, diff = 0;
	int flag = 0;
	char *week[7] = { "日","一","二","三","四","五","六" };
	printf("输入日期（年月日）：\n");
	scanf("%d%d%d", &year2, &month2, &day2);
	diff = diffofTwoday(year1, month1, day1, year2, month2, day2);
	if ((year1 > year2) || (year1 == year2 && month1 > month2) || (year1 == year2 && month1 == month2 && day1 > day2))
	{
		week2 = (7 - diff % 7) % 7;
	}
	else
	{
		week2 = diff % 7;
	}
	printf("这一天是星期%s\n", week[week2]);
	system("pause");
}