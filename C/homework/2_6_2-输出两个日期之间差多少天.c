/*
输入两个日期（年 月 日 年 月 日）， 输出这两个日期之间差多少天。
提示： sum = delt(year1 year2)  - dayofyear(date1)  + dayofyear(date2)
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
int main()
{
	int year1, month1, day1, year2, month2, day2;
	int result = 0;
	printf("输入两个日期（年月日）：\n");
	scanf("%d%d%d%d%d%d", &year1, &month1, &day1, &year2, &month2, &day2);
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
	printf("两个日期相差%d天\n", result);
	system("pause");
}