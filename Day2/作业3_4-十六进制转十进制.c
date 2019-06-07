/*将十六进制数转换成十进制数。输入十六进制数输出对应的十进制数。输入“ctl +  z” 结束。*/

//考虑到处理负数，应该在3.2的基础上修改
//先将十六进制数转为二进制，再用3.2的方法将二进制转为十进制
//不过时间来不及，因此本题我只考虑了正十六进制转成正十进制的方法

#include <stdio.h> 
#include <stdlib.h> 

int main() {
	char c;
	int num[4] = { 0 };
	int ten = 0;
	int i = 0;
	while ((c = getchar()) != EOF) {
		if (c != '\n') {
			switch (c)
			{
			case 'A':case 'a':
				num[i] = 10; break;
			case 'B':case 'b':
				num[i] = 11; break;
			case 'C':case 'c':
				num[i] = 12; break;
			case 'D':case 'd':
				num[i] = 13; break;
			case 'E':case 'e':
				num[i] = 14; break;
			case 'F':case 'f':
				num[i] = 15; break;
			default: num[i] = c - 48; break;
			}
			++i;
		}
		else {
			if (i < 5) {
				for (int j = 3; j >= 4 - i; --j) {
					num[j] = num[j - (4 - i)];
				}
				for (int j = 4 - i - 1; j >= 0; --j) {
					num[j] = 0;
				}
			}
			for (int j = 3, x = 1; j >= 0; --j, x *= 16) {
				ten += num[j] * x;
			}
			printf("%d\n", ten);
			ten = 0;
			i = 0;
			for (int j = 0; j < 4; ++j) num[j] = 0;
		}
	}
}
