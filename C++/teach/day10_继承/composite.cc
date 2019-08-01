 ///
 /// @file    composite.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-01 11:44:46
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class Eye
{
public:
	void look() {	cout << "look()" << endl;}
};

class Nose 
{
public:
	void smell() {	cout << "smell()" << endl;}
};
 
class Mouth 
{
public:
	void eat() {	cout << "eat()" << endl;}
};

class Ear
{
public:
	void listen() {	cout << "listen()" << endl;}
};


class Head
: public Nose
, public Eye
, public Mouth
, public Ear
{}; //继承完成 (设计不合理)  A is B

class Head2
{
public:
	void look() 
	{
		_eye.look();
	}

	void smell()
	{
		_nose.smell();
	}

	void eat()
	{
		_mouth.eat();
	}

	void listen()
	{
		_ear.listen();
	}

private:
	Eye _eye;//组合方式  A has B
	Nose _nose;
	Mouth _mouth;
	Ear _ear;
};


int main(void)
{
	Head head;
	head.look();
	head.smell();
	head.eat();
	head.listen();
	cout << endl;

	Head2 head2;
	head2.look();
	head2.smell();
	head2.eat();
	head2.listen();

	return 0;
}
