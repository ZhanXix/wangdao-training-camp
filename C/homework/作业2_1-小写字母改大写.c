/*从键盘上输入字符，将小写字母转换成大写字母。输入“ctl + z” 结束 。*/
#include <stdio.h> 
#include <stdlib.h> 

int main() {
	char c;
	printf("请输入字符：\n");
	while ((c=getchar()) != EOF) {
		if (c >= 97 && c <= 122) {
			c -= 32;//小写字母转换为大写字母
		}
		putchar(c);
	}
	system("pause");
}
