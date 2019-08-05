/*ʵ��һ�����е���ģ��*/

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
		cout << "����������" << endl;
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
		cout << "����Ϊ�գ�" << endl;
	}
}

template <class T, int kSize>
T& Queue<T, kSize>::front() const
{
	if (!empty()) {
		return _data[_front];
	}
	else {
		cout << "����Ϊ�գ�" << endl;
	}
}

template <class T, int kSize>
T& Queue<T, kSize>::back() const
{
	if (!empty()) {
		return _data[(_rear - 1 + kSize) % kSize];
	}
	else {
		cout << "����Ϊ�գ�" << endl;
	}
}

//���Դ���
void test_int()
{
	Queue<int,11> queue;
	cout << "��ʱ�����Ƿ�Ϊ�գ�" << queue.empty() << endl;
	queue.push(1);
	cout << "��ʱ�����Ƿ�Ϊ�գ�" << queue.empty() << endl;

	for (int idx = 2; idx != 12; ++idx) {
		queue.push(idx);
	}
	cout << "��ʱ�����Ƿ�������" << queue.full() << endl;

	cout << "��ʱ��ͷԪ���ǣ�" << queue.front() << endl;
	cout << "��ʱ��βԪ���ǣ�" << queue.back() << endl;
	
	int num = queue.front();
	queue.pop();
	queue.push(num);

	cout << "Ԫ���ȳ�������Ӻ�" << endl;
	cout << "��ʱ��ͷԪ���ǣ�" << queue.front() << endl;
	cout << "��ʱ��βԪ���ǣ�" << queue.back() << endl;

	cout << "Ԫ��ȫ�����γ��ӣ�" << endl;
	while (!queue.empty()) {
		cout << queue.front() << " ";
		queue.pop();
	}
	cout << endl;
	cout << "��ʱ�����Ƿ�Ϊ�գ�" << queue.empty() << endl;
}

void test_string()
{
	Queue<string, 11> queue;
	cout << "��ʱ�����Ƿ�Ϊ�գ�" << queue.empty() << endl;
	queue.push("aaa");
	cout << "��ʱ�����Ƿ�Ϊ�գ�" << queue.empty() << endl;

	for (int idx = 2; idx != 12; ++idx) {
		queue.push(string(3, 'a' + idx));
	}
	cout << "��ʱ�����Ƿ�������" << queue.full() << endl;

	cout << "��ʱ��ͷԪ���ǣ�" << queue.front() << endl;
	cout << "��ʱ��βԪ���ǣ�" << queue.back() << endl;

	string str = queue.front();
	queue.pop();
	queue.push(str);

	cout << "Ԫ���ȳ�������Ӻ�" << endl;
	cout << "��ʱ��ͷԪ���ǣ�" << queue.front() << endl;
	cout << "��ʱ��βԪ���ǣ�" << queue.back() << endl;

	cout << "Ԫ��ȫ�����γ��ӣ�" << endl;
	while (!queue.empty()) {
		cout << queue.front() << " ";
		queue.pop();
	}
	cout << endl;
	cout << "��ʱ�����Ƿ�Ϊ�գ�" << queue.empty() << endl;
}

int main()
{
	test_int();
	cout << endl;
	test_string();

	return 0;
}