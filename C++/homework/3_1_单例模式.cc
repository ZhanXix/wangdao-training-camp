#include <iostream>
using std::cout;
using std::endl;

class Sigleton
{
public:
    static Sigleton * getInstance()
    {
        if( NULL == _pSigleton )
        {
            _pSigleton = new Sigleton();
        }
        return _pSigleton;
    }

    static void destory()
    {
        if( _pSigleton )
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

    //other data
    static Sigleton * _pSigleton;
};

Sigleton * Sigleton::_pSigleton = NULL;

int main()
{
    Sigleton * pSig1 = Sigleton::getInstance();
    Sigleton * pSig2 = Sigleton::getInstance();

    cout << "pSig1 = " << pSig1 << endl;
    cout << "pSig2 = " << pSig2 << endl;

    Sigleton::destory();

    return 0;
}

