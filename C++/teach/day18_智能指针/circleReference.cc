#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;

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

	shared_ptr<Parent> _pParent;
};

int main()
{
	//shared_ptr的循环引用会导致内存泄漏
	shared_ptr<Parent> pParent(new Parent);
	shared_ptr<Child> pChild(new Child);
	pParent->_pChild = pChild;
	pChild->_pParent = pParent;

	return 0;
}