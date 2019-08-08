#include <iostream>
using std::cout;
using std::endl;

template <class T>
class Singleton
{
	class AutoRelease
	{
	public:
		AutoRelease() { cout << "AutoRelease()" << endl; }
		~AutoRelease()
		{
			if (_pInstance) {
				delete _pInstance;
			}
			cout << "~AutoRelease()" << endl;
		}
	};
public:
	template <class... Args>
	static T* getInstance(Args... args)
	{
		if (_pInstance == nullptr) {
			_auto;
			_pInstance = new T(args...);
		}
		return _pInstance;
	}

private:
	Singleton() { cout << "Singleton()" << endl; }
	~Singleton() { cout << "~Singleton()" << endl; }

private:
	static T* _pInstance;
	static AutoRelease _auto;
};

template<class  T>
T* Singleton<T>::_pInstance = nullptr;

template<class  T>
typename Singleton<T>::AutoRelease Singleton<T>::_auto;

class Point
{
public:
	Point(int ix, int iy)
		: _ix(ix)
		, _iy(iy)
	{
		cout << "Point(int, int)" << endl;
	}

	~Point() { cout << "~Point()" << endl; }

private:
	int _ix;
	int _iy;
};

int main()
{
	Point* pt = Singleton<Point>::getInstance(1, 2);
	Point* pt2 = Singleton<Point>::getInstance(1, 2);

	cout << "pt = " << pt << endl;
	cout << "pt2 = " << pt2 << endl;

	return 0;
}