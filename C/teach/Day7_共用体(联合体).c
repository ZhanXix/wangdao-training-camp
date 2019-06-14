#include <stdio.h> 
#include <stdlib.h> 

//共用体(联合体)
union data
{
	int i;
	char c;
	float f;
};
typedef struct student
{
	int num;
	float score;
}Student_t;
enum weekday{sun=10,mon,tue,wed,thu,fri,sat};
int main()
{
	union data a;//联合体，所有成员共用一块空间
	Student_t s;
	enum weekday workday;
	a.i = 10;
	a.c = 'A';
	a.f = 98.5;
	s.num = 1001;
	s.score = 98.5;
	printf("wed=%d\n", wed);
	workday = mon;
	printf("workday=%d\n", workday);
	system("pause");
}
