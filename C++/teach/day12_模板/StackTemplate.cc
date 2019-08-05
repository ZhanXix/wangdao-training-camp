#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <class T, int kSize = 10>
class Stack
{
public:
	Stack()
		: _top(-1)
		, _data(new T[kSize]())
	{}

	~Stack();

	bool full() const;
	bool empty() const;
	void push(const T& t);
	void pop();
	T& top() const;

private:
	int _top;
	T* _data;
};

template <class T, int kSize>
Stack<T, kSize>::~Stack()
{
	if (_data) {
		delete[] _data;
	}
}

template <class T, int kSize>
bool Stack<T, kSize>::full() const
{
	return _top == kSize - 1;
}

template <class T, int kSize>
bool Stack<T, kSize>::empty() const
{
	return _top == -1;
}

template <class T, int kSize>
void Stack<T, kSize>::push(const T& t)
{
	if (!full()) {
		_data[++_top] = t;
	}
	else {
		//LogInfo();
		cout << "Stack is full, cannot push any more data!" << endl;
	}
}

template <class T, int kSize>
void Stack<T, kSize>::pop()
{
	if (!empty()) {
		--_top;
	}
	else {
		cout << "Stack is empty, no more data!" << endl;
	}
}

template <class T, int kSize>
T& Stack<T, kSize>::top() const
{
	return _data[_top];
}

void test0()
{
	//vector<int> numbers;	//ʵ����
	Stack<int> stack; //��ģ�� ==> ģ����
	cout << "��ʱջ���Ƿ�Ϊ�գ�" << stack.empty() << endl;
	stack.push(1);
	cout << "��ʱջ���Ƿ�Ϊ�գ�" << stack.empty() << endl;

	for (int idx = 2; idx != 12; ++idx) {
		stack.push(idx);
	}
	cout << "��ʱջ���Ƿ�������" << stack.full() << endl;

	while (!stack.empty()) {
		cout << stack.top() << endl;
		stack.pop();
	}

	cout << "��ʱջ���Ƿ�Ϊ�գ�" << stack.empty() << endl;
} 

void test1()
{
	Stack<string> stack;
	cout << "��ʱջ���Ƿ�Ϊ�գ�" << stack.empty() << endl;
	stack.push("aaa");
	cout << "��ʱջ���Ƿ�Ϊ�գ�" << stack.empty() << endl;

	for (int idx = 1; idx != 11; ++idx) {
		stack.push(string(3, 'a' + idx));
	}
	cout << "��ʱջ���Ƿ�������" << stack.full() << endl;

	while (!stack.empty()) {
		cout << stack.top() << endl;
		stack.pop();
	}

	cout << "��ʱջ���Ƿ�Ϊ�գ�" << stack.empty() << endl;
}

int main()
{
	//test0();
	test1();
	return 0;
}