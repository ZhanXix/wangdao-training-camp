/*
输入年月日，输出该日期是当年的第几天。
*/

#include <stdio.h> 
#include <stdlib.h> 

int main()
{
	int monthDay[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int year, month, day;
	int result = 0;
	printf("输入年月日：\n");
	scanf("%d%d%d", &year, &month, &day);
	for (int i = 0; i < month - 1; ++i)
	{
		result += monthDay[i];
		if(i==1)//考虑二月
		{
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			{
				++result;
			}
		}
	}
	result += day;
	printf("这是当年的第%d天\n", result);
	system("pause");
}