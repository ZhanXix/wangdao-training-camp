//��������-����-����-func.c
#include "��������-����-����-func.h"

void printMessage()
{
	int ret;
	printf("How do you do\n");
	ret = printStar(5);

}
int printStar(int i)//��������
{
	printf("*****************************\n");
	return i+3;
}