#include <stdio.h> 
#include <stdlib.h> 

typedef struct
{
	int num;
	char name[20];
	float chinese;
	float math;
	float english;
}Student_t, * pStudent_t;

#define N 5

int compareNum(const void* pleft, const void* pright)
{
	pStudent_t p1 = (pStudent_t)pleft;
	pStudent_t p2 = (pStudent_t)pright;
	return p1->num - p2->num;
}
int compareScore(const void* pleft, const void* pright)
{
	pStudent_t p1 = (pStudent_t)pleft;
	pStudent_t p2 = (pStudent_t)pright;
	if (p1->chinese + p1->math + p1->english - (p2->chinese + p2->math + p2->english) > 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
int main()
{
	Student_t sArr[5];
	int i;
	for (i = 0; i < N; i++)
	{
		scanf("%d%s%f%f%f", &sArr[i].num, sArr[i].name, &sArr[i].chinese, &sArr[i].math, &sArr[i].english);
	}
	//qsort(sArr, N, sizeof(Student_t), compareNum);
	qsort(sArr, N, sizeof(Student_t), compareScore);
	for (i = 0; i < N; i++)
	{
		printf("%d %10s %5.2f %5.2f %5.2f %6.2f\n", sArr[i].num, sArr[i].name, sArr[i].chinese, sArr[i].math, sArr[i].english, sArr[i].chinese + sArr[i].math + sArr[i].english);
	}
	system("pause");
}