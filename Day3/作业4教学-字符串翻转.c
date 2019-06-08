#include <stdio.h>
#include <stdlib.h>

void wordReverse(char* start, char* end)
{
	char tmp;
	while (start < end)
	{
		tmp = *start;
		*start = *end;
		*end = tmp;
		end--;
		start++;
	}
}
int main()
{
	char str[1000];
	char* front, * back;
	while (gets(str) != NULL)
	{
		wordReverse(str, str + strlen(str) - 1);
		puts(str);
		front = back = str;
		while (*front)
		{
			while (*front == ' ')
			{
				front++;
			}
			back = front;//µ¥´Ê¿ªÍ·
			while (*front != ' ' && *front)
			{
				front++;
			}
			wordReverse(back, front - 1);
		}
		puts(str);
	}
	system("pause");
}