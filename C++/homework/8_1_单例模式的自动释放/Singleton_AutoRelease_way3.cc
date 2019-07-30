//单例模式的自动释放
//（方法3：pthread_once + atexit）

#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

class Sigleton
{
public:
    static Sigleton* getInstance()
    {
        pthread_once(&_once, init);
        return _pSigleton;
    }

    static void init()
    {
        _pSigleton = new Sigleton();
        ::atexit(destory);
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
    static pthread_once_t _once;
};

Sigleton* Sigleton::_pSigleton = Sigleton::getInstance();
pthread_once_t Sigleton::_once = PTHREAD_ONCE_INIT;

int main()//test
{
    Sigleton* pSig1 = Sigleton::getInstance();
    Sigleton* pSig2 = Sigleton::getInstance();

    cout << "pSig1 = " << pSig1 << endl;
    cout << "pSig2 = " << pSig2 << endl;

    return 0;

}
