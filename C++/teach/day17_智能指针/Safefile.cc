#include <stdio.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class SafeFile
{
public:
	SafeFile(FILE *fp)
		: _fp(fp)
	{}

	void write(const string& msg)
	{
		fwrite(msg.c_str(), 1, msg.size(), _fp);
	}

	~SafeFile()
	{
		if (_fp) {
			fclose(_fp);
			cout << ">> fclose(_fp)" << endl;
		}
	}

private:
	FILE* _fp;
};

int main()
{
	SafeFile sf(fopen("test.txt", "aw+"));
	sf.write("this is a new line\n");

	return 0;
}