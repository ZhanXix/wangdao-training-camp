#include <string.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class String
{
public:
	String()
		: _pstr(new char[1]())
	{
		cout << "String()" << endl;
	}

	String(const char* pstr)
		:_pstr(new char[strlen(pstr) + 1]())
	{
		cout << "String(const char*)" << endl;
		strcpy(_pstr, pstr);
	}

	String(const String& rhs)
		: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		cout << "String(const String&)" << endl;
		strcpy(_pstr, rhs._pstr);
	}

	~String()
	{
		cout << "~String()" << endl;
		if (_pstr) {
			delete[] _pstr;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const String& rhs);

private:
	char* _pstr;
};

std::ostream& operator<<(std::ostream& os, const String& rhs)
{
	os << rhs._pstr;
	return os;
}

int main()
{
	vector<String> strs;

	return 0;
}