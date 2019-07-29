#include <iostream>
using std::cout;
using std::endl;

class Data
{
public:
    Data(int data=0)
    : _data(data)
    {
        cout << "Data()" << endl;
    }

    int getData() const { return _data; }

    ~Data()
    {
        cout << "~Data()" << endl;
    }

    int _data;
};

class MiddleLayer
{
public:
    MiddleLayer(Data * pdata = nullptr)
    : _pdata(pdata)
    {
        cout << "MiddleLayer(Data*)" << endl;
    }

    Data * operator->()
    {
        return _pdata;
    }

    Data & operator*()//解引用运算符
    {
        return *_pdata;
    }

    ~MiddleLayer()
    {
        cout << "~MiddleLayer()" << endl;
        if(_pdata){
            delete _pdata;
        }
    }

private:
    Data * _pdata;
};

class ThirdLayer
{
public:
    ThirdLayer(MiddleLayer *ml)
    : _ml(ml)
    { cout << "ThirdLayer(MiddleLayer*)" << endl; }

    MiddleLayer & operator->()
    {
        return *_ml;
    }

    ~ThirdLayer()
    {
        cout << "~ThirdLayer()" << endl;
        if(_ml){
            delete _ml;
        }
    }

private:
    MiddleLayer * _ml;
};

int main()
{
    //ml虽然是一个对象，但用法类似一个指针
    //可以将其看成是一个智能指针的雏形
    MiddleLayer ml(new Data(10));
    cout << ml->getData() << endl;
    //cout << (ml.operator->())->getData() << endl;
    cout << (*ml).getData() << endl;

    ThirdLayer tl(new MiddleLayer(new Data(11)));
    cout << tl->getData() << endl;
    cout << ((tl.operator->()).operator->())->getData() << endl;

    return 0;
}

