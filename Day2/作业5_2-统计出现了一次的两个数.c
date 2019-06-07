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
	int a1[6] = { 0 }, a0[6] = { 0 };
	int i1 = 0, i0 = 0;
	//分成两堆
	for (int i = 0; i < 6; ++i) {
		if (a[i] & y) {
			a1[i1] = a[i];
			++i1;
		}
		else {
			a0[i0] = a[i];
			++i0;
		}
	}
	printf("出现了一次的那两个数为:");
	//分别求两个数
	x = 0;
	for (int i = 0; i < 6; ++i) {
		x ^= a1[i];
	}
	printf("%d ", x);
	x = 0;
	for (int i = 0; i < 6; ++i) {
		x ^= a0[i];
	}
	printf("%d\n", x);
	system("pause");
}
