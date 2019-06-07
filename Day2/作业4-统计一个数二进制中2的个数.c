/*统计一个整数对应的二进制数的1的个数。输入一个整数（可正可负）， 输出该整数的二进制包含1的个数， “ctl+ z” 结束。*/

#include <stdio.h> 
#include <stdlib.h> 

int main() {
	//在3.1的基础上修改
	int ten = 0, i = 31, flag = 0, under0 = 0;
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
		for (int j = 0; j < 32; ++j) {	//统计二进制值包含一的个数
			if (two[j]) flag++;
		}
		printf("该数字对应二进制数中所含1的位数为%d\n", flag);	
	}
	system("pause");
}
//可以用位运算做，不停地向右移一位并且和1做与运算即可
//但是这个方法我开始没想起来，因为时间关系所以就不再写一遍这题了
