/*有101个整数，其中有50个数出现了两次，1个数出现了一次， 找出出现了一次的那个数。*/

#include <stdio.h> 
#include <stdlib.h> 

int main() {
	int a[] = { 2,3,2,4,4 };
	int x = 0;
	for (int i = 0; i < 5; ++i) {
		x ^= a[i];
	}
	printf("出现了一次的那个数为%d\n", x);
	system("pause");
}
