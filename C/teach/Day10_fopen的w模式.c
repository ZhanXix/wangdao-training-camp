#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fp = fopen("file.txt", "w+");
	fclose(fp);
}