/*有102个整数，其中有50个数出现了两次，2个数出现了一次， 找出出现了一次的那2个数。*/

#include <stdio.h> 
#include <stdlib.h> 

int main() {
	int a[] = { 2,3,2,4,4,5 };
	int x = 0;
	for (int i = 0; i < 6; ++i) {
		x ^= a[i];
	}	//得到两个不相同的数的异或结果
	int y = x & -x;	//最低位为1的那个数
	int x1 = 0, x0 = 0;
	//分成两堆，分别求两个数
	for (int i = 0; i < 6; ++i) {
		if (a[i] & y) {
			x1 ^= a[i];
		}
		else {
			x0 ^= a[i];
		}
	}
	printf("出现了一次的那两个数为: %d %d\n", x1, x0);
	system("pause");
}
