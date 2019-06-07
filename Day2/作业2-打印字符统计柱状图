#include <stdio.h> 
#include <stdlib.h> 

int main() {
	char c;
	int alp = 0, num = 0, oth = 0;	//数字，字母，其他
	int flag = 0;	//存储他们的排序序列
	int max = 0, mid = 0, min = 0;
	printf("请输入字符：\n");
	while ((c = getchar()) != EOF) {
		if (c >= 48 && c <= 57)	++num;
		else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) ++alp;
		else ++oth;
	}
	if (alp >= num && num >= oth) {
		max = alp,mid=num,min=oth;
		flag = 1;
	}
	else if (alp >= oth && oth >= num) {
		max = alp, mid = oth, min = num;
		flag = 2;
	}
	else if (oth >= alp && alp >= num) {
		max = oth, mid = alp, min = num;
		flag = 3;
	}
	else if (oth >= num && num >= alp) {
		max = oth, mid = num, min = alp;
		flag = 4;
	}
	else if (num >= oth && oth >= alp) {
		max = num, mid = oth, min = alp;
		flag = 5;
	}
	else if (num >= alp && alp >= oth) {
		max = num, mid = alp, min = oth;
		flag = 6;
	}
	printf("  %d  ", max);
	for (int i = 0; i < max - mid; ++i) {
		printf("\n*****");
	}
	printf("     %d  ", mid);
	for (int i = 0; i < mid - min; ++i) {
			printf("\n*****   *****");
	}
	printf("     %d  ", min);
	for (int i = 0; i < min; ++i) {
		printf("\n*****   *****   *****");
	}
	putchar('\n');
	switch (flag)
	{
	case 1:
		printf(" alp     num     oth"); break;
	case 2:
		printf(" alp     oth     num"); break;
	case 3:
		printf(" oth     alp     num"); break;
	case 4:
		printf(" oth     num     alp"); break;
	case 5:
		printf(" num     oth     alp"); break;
	case 6:
		printf(" num     alp     oth"); break;
	default:
		break;
	}
	putchar('\n');
	system("pause");
}
//想不出来如何简化排序
//存在的问题是他会把回车也算成其他字符
