/*将二进制转换成十进制数。输入二进制数输出对应的十进制数，输入“ctl + z”结束。
*/
#include <stdio.h> 
#include <stdlib.h> 

int main() {
	int two[32];
	char c;
	for (int i = 0; i < 32; ++i) two[i] = 0;
	int ten = 0, x = 1;
	int j = 0, under0 = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			if (j < 32) {
				for (int i = 31; i >= 32 - j; --i) {
					two[i] = two[i - (32 - j)];
				}
				for (int i = 32 - j - 1; i >= 0; --i) {
					two[i] = 0;
				}
			}
			if (two[0]) {//负二进制数变正
				under0 = 1;
				for (int i = 0; i < 32; ++i) {
					if (two[i]) two[i] = 0;
					else two[i] = 1;
				}	//取反
				++two[31];	//最后一位加一
				for (int i = 31; i >= 0; --i) {
					if (two[i] == 2) {
						two[i] = 0;
						if (i > 0) ++two[i - 1];
					}
				}	//进位
			}
			for (int i = 31; i >= 32 - j; --i) {
				ten += two[i] * x;
				x *= 2;
			}
			if (under0) ten = -ten;
			printf("%d\n", ten);
			j = 0, ten = 0, x = 1, under0 = 0;//重新初始化
			for (int i = 0; i < 32; ++i) two[i] = 0;
		}
		else {
			two[j] = c - 48;
			j++;
		}
	}
}
