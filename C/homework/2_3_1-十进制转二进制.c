/*
将十进制数转换成二进制数。输入十进制数输出对应的二进制数，输入“ctl + z”结束。
*/

#include <stdio.h> 
#include <stdlib.h> 

int main() {
	int ten = 0, i = 31, flag = 0, under0 = 0;
	int two[32] = {0};
	while (fflush(stdin), scanf("%d",&ten) != EOF) {	//输入十进制数
		i = 31;	//每次循环都必须初始化
		flag = 0;
		under0 = 0;
		for (int j = 0; j < 32; ++j) two[j] = 0;
		if (ten < 0) {
			under0 = 1;
			ten = -ten;
		}
		while (ten >= 1) {
			two[i] = ten % 2;
			ten /= 2;
			--i;
		}
		if (under0) {	//若输入的值为负数
			for (int j = 0; j < 32; ++j) {
				if (two[j]) two[j] = 0;
				else two[j] = 1;
			}	//取反
			++two[31];	//最后一位加一
			for (int j = 31; j >= 0; --j) {
				if (two[j] == 2) {
					two[j] = 0;
					if(j>0) ++two[j - 1];
				}
			}	//进位
		}
		for (int j = 0; j < 32; ++j) {	//输出二进制值
			if (two[j] != 0) flag = 1;
			if (flag) printf("%d", two[j]);
		}
		putchar('\n');
	}
	system("pause");
}
