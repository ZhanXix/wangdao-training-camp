#include <iostream>
using std::cout;
using std::endl;

template <typename... Args>
void print(Args... args)
{
	//��ȡ�ɱ����ʵ�ʴ��ݲ����ĸ���
	cout << "sizeof...(Args) = " << sizeof...(Args) << endl;
	cout << "sizeof...(args) = " << sizeof...(args) << endl;
}

#if 0
void display()
{
	cout << endl;
}
#endif

template <typename T>
void display(T t)
{
	cout << t << endl;
}

template <typename T, typename... Args>// Args ģ�������
void display(T t, Args... args)// args ����������
{
	cout << t << " ";
	display(args...);// ���/���

	//print(args...);
}

int main()
{
	print(1, 1.11, 'a', "hello");

	display(1, 1.11, 'a', "hello");
	//cout << 1 << " ";
	//display(1.11, 'a', "hello");
	//	cout << 1.11 << " ";
	//	display('a', "hello");
	//		cout << 'a' << " ";
	//		display("hello");
	//			cout << "hello" << " ";
	//			display();

	return 0;
}