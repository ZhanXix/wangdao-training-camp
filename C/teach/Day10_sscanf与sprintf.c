#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int num;
	float score;
	char name[20];
}Student_t;

int main(int argc, char* argv[])
{
	Student_t s = { 1001,98.5,"lele" };
	char buf[1000];
	sprintf(buf, "%d %5.2f %s\n", s.num, s.score, s.name);//将这些数据类型转成字符串，存到buf里
	memset(&s, 0, sizeof(Student_t));
	sscanf(buf, "%d%f%s", &s.num, &s.score, s.name);//将buf里的字符串拆成相应的数据类型
	s.num = atoi("123");//字符串转整型
	s.score = atof("92.4");//字符串转浮点数
error:
	system("pause");
}