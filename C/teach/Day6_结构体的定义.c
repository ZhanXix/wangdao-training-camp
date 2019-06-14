#include <stdio.h> 
#include <stdlib.h> 

//结构体的定义
//为了避免浪费空间,在定义结构体时把小字节数据放到一起
struct student_t
{
	int num;
	char name[20];
	char sex;
	short high;
	int age;
	float score;
	char addr[30];
};//结构体类型声明，注意最后一定要加分号 

int main()
{
	struct student_t s = { 1001,"lele",'M',180,20,98.5,"Shanghai" };
	struct student_t sArr[3];
	int i;
	printf("%d %s %c %d %5.2f %s\n", s.num, s.name, s.sex, s.age, s.score, s.addr);
	for (i = 0; i < 3; i++)
	{
		scanf("%d%s %c%d%f%s", &sArr[i].num, sArr[i].name, &sArr[i].sex, &sArr[i].age, &sArr[i].score, sArr[i].addr);
	}
	for (i = 0; i < 3; i++)
	{
		printf("%d %10s %c %d %5.2f %s\n", sArr[i].num, sArr[i].name, sArr[i].sex, sArr[i].age, sArr[i].score, sArr[i].addr);
	}
}
