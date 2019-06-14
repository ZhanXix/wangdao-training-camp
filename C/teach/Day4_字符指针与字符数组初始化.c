#include <stdio.h>
#include <stdlib.h>

//字符指针与字符数组初始化
int main()
{
	char* p = "helloworld";	//把字符串常量的首地址赋给p，只能读，不可写
	char c[20] = "helloworld";	//等价于strcpy(c,"helloworld");
	//p[0] = 'H';	//无法执行，写入访问权限冲突
	c[0] = 'H';
	p = "how are you";
	//c = "how are you";	//左边存储的是地址，不可写
	//c[20] = "how are you";	//非法，试图将字符串常量的首地址赋给c[20]
	//strcpy(p, "how are you");	//非法，试图写入常量区
	p = c;
	strcpy(p, "how are you");//此时合法，p指向c的首地址
	system("pause");
}
