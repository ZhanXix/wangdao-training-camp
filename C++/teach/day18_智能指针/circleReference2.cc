#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

class Child;

class Parent
{
public:
	Parent() { cout << "Parent()" << endl; }
	~Parent() { cout << "~Parent()" << endl; }

	shared_ptr<Child> _pChild;
};

class Child
{
public:
	Child() { cout << "Child()" << endl; }
	~Child() { cout << "~Child()" << endl; }

	weak_ptr<Parent> _pParent;
};

int main()
{
	//shared_ptr的循环引用会导致内存泄漏
	//解决方案：weak_ptr
	shared_ptr<Parent> pParent(new Parent);
	shared_ptr<Child> pChild(new Child);
	cout << "pParent' use_count = " << pParent.use_count() << endl;
	cout << "pChild' use_count = " << pChild.use_count() << endl;
	pParent->_pChild = pChild;//引用计数加一
	pChild->_pParent = pParent;//weak_ptr = shared_ptr

	cout << "pParent' use_count = " << pParent.use_count() << endl;
	cout << "pChild' use_count = " << pChild.use_count() << endl;

	return 0;
}