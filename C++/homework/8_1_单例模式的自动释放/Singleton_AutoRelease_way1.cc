//����ģʽ���Զ��ͷ�
//������1��Ƕ���� + ��̬����

#include <iostream>
using std::cout;
using std::endl;

class Sigleton
{
	class AutoRelease
	{
	public:
		AutoRelease()
		{
			cout << "AutoRelease()" << endl;
		}

		~AutoRelease()
		{
			cout << "~AutoRelease()" << endl;
			if (_pSigleton) {
				delete _pSigleton;
			}
		}
	};

public:
	static Sigleton* getInstance()
	{
		if (nullptr == _pSigleton){
			_pSigleton = new Sigleton();
		}
		return _pSigleton;
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
	static AutoRelease _autoRelease;
};

Sigleton* Sigleton::_pSigleton = Sigleton::getInstance();
Sigleton::AutoRelease Sigleton::_autoRelease;

int main()//test
{
	Sigleton* pSig1 = Sigleton::getInstance();
	Sigleton* pSig2 = Sigleton::getInstance();

	cout << "pSig1 = " << pSig1 << endl;
	cout << "pSig2 = " << pSig2 << endl;

	return 0;
}

