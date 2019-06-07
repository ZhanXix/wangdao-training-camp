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
