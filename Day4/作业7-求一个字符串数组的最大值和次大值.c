/*
求一个字符串数组的最大值和次大值  void big(char *arr[],int size ,char** big1,char** big2)
*/

#include <stdio.h>
#include <stdlib.h>

void big(char* arr[], int size, char** big1, char** big2)
{
	if (size)
	{
		*big1 = arr[0];
		for (int i = 1; i < size; i++)
		{
			if (strcmp(arr[i], *big1) > 0)
			{
				*big2 = *big1;
				*big1 = arr[i];
			}
			else if (strcmp(arr[i], *big2) > 0)
			{
				*big2 = arr[i];
			}
		}
	}
}
#define N 6
int main() {
	char* arr[] = { "apple","bed","cake","pear","dining","end" };
	char* Max = NULL, * secMax = NULL;
	big(&arr, N, &Max, &secMax);
	printf("MAX: %s\n", Max);
	printf("secMAX: %s\n", secMax);
	system("pause");
}
