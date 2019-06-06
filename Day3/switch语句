#include <stdio.h> 
#include <stdlib.h> 

//switch语句
int main()
{
	int mon, year;
	while (scanf("%d%d", &year, &mon) != EOF)
	{
		switch (mon)
		{
		case 2:printf("%d is %d days\n", mon, 28 + ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)); break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:printf("%d is 31 days\n", mon); break;
		case 4:
		case 6:
		case 9:
		case 11:printf("%d is 30 days\n", mon); break;
		default:
			printf("error mon\n");
			break;
		}
	}
}
