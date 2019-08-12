#include <iostream>
#include <memory>
#include <string>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::shared_ptr;
using std::string;

//自定义删除器方式
struct FileDeleter
{
	void operator()(FILE* fp)
	{
		if (fp) {
			fclose(fp);
			cout << ">> fclose(fp)" << endl;
		}
	}
};

void test0()
{
	unique_ptr<FILE, FileDeleter> up(fopen("test.txt", "a+"));

	string msg = "hello,world";
	fwrite(msg.c_str(), 1, msg.size(), up.get());
}

void test1()
{
	shared_ptr<FILE> sp(fopen("test.txt", "a+"), FileDeleter());
	string msg = "hello,world\n";
	fwrite(msg.c_str(), 1, msg.size(), sp.get());
}

int main()
{
	//test0();
	test1();
	return 0;
}