#include <stdio.h> 
#include <stdlib.h> 

typedef struct student
{
	int num;
	struct student* pNext;
}Student_t, * pStudent_t;

void listHeadInsert(pStudent_t*, Student_t**, int);
void listPrint(pStudent_t);
void listTailInsert(pStudent_t*, Student_t**, int);
void listSortInsert(pStudent_t*, Student_t**, int);