//单例模式的自动释放
//（方法2：静态成员函数 + atexit）

#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

class Sigleton
{
public:
	static Sigleton* getInstance()
	{
		if (nullptr == _pSigleton)
		{
			::atexit(destory);
			_pSigleton = new Sigleton();
		}
		return _pSigleton;
	}

	static void destory()
	{
		if (_pSigleton)
		{
			delete _pSigleton;
		}
	}

private:
	Sigleton()
	{
		cout << "Sigleton()" << endl;
	}

	~Sigleton()
	{
		cout << "~Sigleton()" << endl;
	}

	//private data
	static Sigleton* _pSigleton;
};

Sigleton* Sigleton::_pSigleton = Sigleton::getInstance();

int main()//test
{
	Sigleton* pSig1 = Sigleton::getInstance();
	Sigleton* pSig2 = Sigleton::getInstance();

	cout << "pSig1 = " << pSig1 << endl;
	cout << "pSig2 = " << pSig2 << endl;

	return 0;
}