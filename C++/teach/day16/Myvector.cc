#include <iostream>
#include <memory>
#include <algorithm>
using std::cout;
using std::endl;

template<class T>
class Myvector
{
public:
	using iterator = T *;
	using const_iterator = const T *;

	Myvector()
		: _start(nullptr)
		, _finish(nullptr)
		, _end_of_storage(nullptr)
	{}

	~Myvector()
	{
		if (_start) {
			while (_finish != _start) {
				_alloc.destroy(--_finish);
			}
			_alloc.deallocate(_start, capacity());
		}
	}

	size_t size() const { return _finish - _start; }
	size_t capacity() const { return _end_of_storage - _start; }

	const_iterator begin() const { return _start; }
	const_iterator end() const { return _finish; }

	void push_back(const T& value);
	void pop_back();

	T & operator[](size_t idx)
	{
		return _start + idx;
	}

private:
	void reallocate();

private:
	static std::allocator<T> _alloc;
	T* _start;
	T* _finish;
	T* _end_of_storage;
};

template<class T>
std::allocator<T> Myvector<T>::_alloc;

template<class T>
void Myvector<T>::push_back(const T& value)
{
	if (size() == capacity()) {
		reallocate();
	}

	//构造对象
	_alloc.construct(_finish++, value);
}

template<class T>
void Myvector<T>::pop_back()
{
	if (size() > 0) {
		//销毁对象
		_alloc.destroy(--_finish);
	}
}

template<class T>
void Myvector<T>::reallocate()
{
	size_t capa = capacity();
	size_t newCapa = 2 * capa > 0 ? 2 * capa : 1;

	//开辟空间
	T* ptmp = _alloc.allocate(newCapa);//没有任何元素的空间
	if (_start) {
		//std::copy(_start, _finish, ptmp);//内部回调用赋值运算符，对象存在时使用
		std::uninitialized_copy(_start, _finish, ptmp);//定位new表达式

		while (_finish != _start) {
			_alloc.destroy(--_finish);
		}
		//回收空间
		_alloc.deallocate(_start, capa);
	}

	_start = ptmp;
	_finish = _start + capa;
	_end_of_storage = _start + newCapa;
}

template<class Container>
void display(const Container& c)
{
	typename Container::const_iterator cit = c.begin();
	while (cit != c.end()) {
		cout << *cit << " ";
		++cit;
	}
	cout << endl;
}

template<class Container>
void showCapacity(const Container& c)
{
	cout << "c's size = " << c.size() << endl;
	cout << "c'capacity size = " << c.capacity() << endl;
}

int main()
{
	Myvector<int> numbers;
	showCapacity(numbers);

	numbers.push_back(1);
	showCapacity(numbers);
	numbers.push_back(1);
	showCapacity(numbers);
	numbers.push_back(1);
	showCapacity(numbers);
	numbers.push_back(1);
	showCapacity(numbers);
	numbers.push_back(1);
	showCapacity(numbers);
	
	display(numbers);

	return 0;
}