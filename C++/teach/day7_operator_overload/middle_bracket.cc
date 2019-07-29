#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class CharArray
{
public:
    CharArray(int size)
    : _size(size)
    , _data( new char[size]() )
    {}

    char & operator[](int idx)
    {
        cout << "char & operator[](int)" << endl;
        if(idx < _size && idx >= 0){
            return _data[idx];
        } else {
            static char nullchar = '\0';
            return  nullchar;
        }
    }

    const char & operator[](int idx) const
    {
        return _data[idx];
    }

    ~CharArray()
    {
        if(_data){
            delete [] _data; 
        }
        cout << "~CharArray()" << endl;
    }

    int size() const { return strlen(_data); }

private:
    int _size;
    char *_data;
};

int main()
{
    CharArray ca(20);
    const char * pstr = "hello,world";
    cout << "pstr = " << pstr;

    int sz = strlen(pstr);
    for(int idx=0; idx!=sz; ++idx){
        ca[idx] = pstr[idx];
    }

    cout << "ca = ";
    for(int idx=0; idx!=ca.size(); ++idx){
        //cout << ca[idx];
        cout << ca.operator[](idx);
    }
    cout << endl;
    return 0;
}

