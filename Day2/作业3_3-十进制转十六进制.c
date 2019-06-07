#include <stdio.h> 
#include <stdlib.h> 

int main() {
	int ten = 0, i = 31, flag = 0, under0 = 0, sixteen = 0;
	int two[32] = { 0 };
	while (fflush(stdin), scanf("%d", &ten) != EOF) {	//输入十进制数
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
					if (j > 0) ++two[j - 1];
				}
			}	//进位
		}
		//得到二进制值
		//这是在十转二进制的基础上改的程序，输出十六进制
		printf("0x");
		int k = 0;
		for (int j = 1; j <= 8; ++j) {
			sixteen = 0;
			for (int l = 8; k < j * 4; ++k,l/=2) {
				sixteen += two[k] * l;
			}
			if (sixteen > 0) flag = 1;
			if (flag) {
				switch (sixteen)
				{
				case 10:
					putchar('A'); break;
				case 11:
					putchar('B'); break;
				case 12:
					putchar('C'); break;
				case 13:
					putchar('D'); break;
				case 14:
					putchar('E'); break;
				case 15:
					putchar('F'); break;
				default:
					printf("%d", sixteen);
					break;
				}
			}
		}
		putchar('\n');
	}
	system("pause");
}
