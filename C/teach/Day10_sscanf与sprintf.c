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
	sprintf(buf, "%d %5.2f %s\n", s.num, s.score, s.name);//����Щ��������ת���ַ������浽buf��
	memset(&s, 0, sizeof(Student_t));
	sscanf(buf, "%d%f%s", &s.num, &s.score, s.name);//��buf����ַ��������Ӧ����������
	s.num = atoi("123");//�ַ���ת����
	s.score = atof("92.4");//�ַ���ת������
error:
	system("pause");
}