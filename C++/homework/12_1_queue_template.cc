/*实现一个队列的类模板*/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <class T, int kSize = 10>
class Queue
{
public:
	Queue()
		: _front(0)
		, _rear(0)
		, _data(new T[kSize]())
	{}

	~Queue();

	bool full() const;
	bool empty() const;
	void push(const T& t);
	void pop();
	T& front() const;
	T& back() const;

private:
	int _front;
	int _rear;
	T* _data;
};

template <class T, int kSize>
Queue<T, kSize>::~Queue()
{
	if (_data) {
		delete[] _data;
	}
}

template <class T, int kSize>
bool Queue<T, kSize>::full() const
{
	return _front == (_rear + 1) % kSize;
}

template <class T, int kSize>
bool Queue<T, kSize>::empty() const
{
	return _front == _rear;
}

template <class T, int kSize>
void Queue<T, kSize>::push(const T& t)
{
	if (!full()) {
		_data[_rear++] = t;
		_rear %= kSize;
	}
	else {
		cout << "队列已满！" << endl;
	}
}

template <class T, int kSize>
void Queue<T, kSize>::pop()
{
	if (!empty()) {
		++_front;
		_front %= kSize;
	}
	else {
		cout << "队列为空！" << endl;
	}
}

template <class T, int kSize>
T& Queue<T, kSize>::front() const
{
	if (!empty()) {
		return _data[_front];
	}
	else {
		cout << "队列为空！" << endl;
	}
}

template <class T, int kSize>
T& Queue<T, kSize>::back() const
{
	if (!empty()) {
		return _data[(_rear - 1 + kSize) % kSize];
	}
	else {
		cout << "队列为空！" << endl;
	}
}

//测试代码
void test_int()
{
	Queue<int,11> queue;
	cout << "此时队列是否为空？" << queue.empty() << endl;
	queue.push(1);
	cout << "此时队列是否为空？" << queue.empty() << endl;

	for (int idx = 2; idx != 12; ++idx) {
		queue.push(idx);
	}
	cout << "此时队列是否已满？" << queue.full() << endl;

	cout << "此时队头元素是：" << queue.front() << endl;
	cout << "此时队尾元素是：" << queue.back() << endl;
	
	int num = queue.front();
	queue.pop();
	queue.push(num);

	cout << "元素先出队再入队后：" << endl;
	cout << "此时队头元素是：" << queue.front() << endl;
	cout << "此时队尾元素是：" << queue.back() << endl;

	cout << "元素全部依次出队：" << endl;
	while (!queue.empty()) {
		cout << queue.front() << " ";
		queue.pop();
	}
	cout << endl;
	cout << "此时队列是否为空？" << queue.empty() << endl;
}

void test_string()
{
	Queue<string, 11> queue;
	cout << "此时队列是否为空？" << queue.empty() << endl;
	queue.push("aaa");
	cout << "此时队列是否为空？" << queue.empty() << endl;

	for (int idx = 2; idx != 12; ++idx) {
		queue.push(string(3, 'a' + idx));
	}
	cout << "此时队列是否已满？" << queue.full() << endl;

	cout << "此时队头元素是：" << queue.front() << endl;
	cout << "此时队尾元素是：" << queue.back() << endl;

	string str = queue.front();
	queue.pop();
	queue.push(str);

	cout << "元素先出队再入队后：" << endl;
	cout << "此时队头元素是：" << queue.front() << endl;
	cout << "此时队尾元素是：" << queue.back() << endl;

	cout << "元素全部依次出队：" << endl;
	while (!queue.empty()) {
		cout << queue.front() << " ";
		queue.pop();
	}
	cout << endl;
	cout << "此时队列是否为空？" << queue.empty() << endl;
}

int main()
{
	test_int();
	cout << endl;
	test_string();

	return 0;
}