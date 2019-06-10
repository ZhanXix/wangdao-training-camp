#include <stdio.h> 
#include <stdlib.h> 

//结构体指针
typedef struct student
{
	int num;
	char name[20];
	float score;
}student_t,*pStudent_t;	//别名代表这个结构体，在函数体内写的时候就不用再在前面加struct
//pStudent_t等价于struct student*

typedef int INTERGE;	//编译时产生新类型
#define INTERGE int	 //预处理时即替换，一般不用这种方式
int main()
{
	student_t s = { 1001,"wangwu",96.5 };
	student_t sArr[3] = { 1001,"wangwu",96.5,1005,"lilei",88.5,1007,"zhangsan",92.5 };
	pStudent_t p;	//student_t* p;
	int num;
	p = &s;
	printf("%d %s %5.2f\n", (*p).num, p->name, p->score);
	p = sArr;
	num = p->num++;	//num=p->num;(p->num)++;
	printf("num=%d,p->num=%d\n", num, p->num);//1001,1002
	num = p++->num;	//num=p->num;p++;
	printf("num=%d,p->num=%d\n", num, p->num);//1002,1005
	num = ++p->num;	//num=++(p->num);
	printf("num=%d,p->num=%d\n", num, p->num);//1006,1006
	system("pause");
}
