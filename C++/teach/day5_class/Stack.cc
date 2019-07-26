#include <iostream>
using std::cout;
using std::endl;


class Stack
{
public:
    Stack(int sz)
    : _sz(sz)
    , _top(-1)
    , _data(new int[sz]())
    {}

    bool empty() const
    {
        return _top == -1;
    }

    bool full() const
    {
        return _top == _sz-1;
    }

    void push(int number)
    {
        if(!full()){
            _data[++_top] = number;
        } else {
            cout << "stack is full, cannot push any member!" << endl;
        }
    }

    void pop()
    {
        if(!empty()){
            --_top;
        } else {
            cout << "stack is empty, no more data!" << endl;
        }
    }

    int &top()
    {
        return _data[_top];
    }

private:
    int _sz;
    int _top;
    int *_data;
};

int main()
{
    Stack stack(10);
    cout << "此时栈中是否为空？" << stack.empty() << endl;
    stack.push(1);
    cout << "此时栈中是否为空？" << stack.empty() << endl;

    for(int idx=2; idx!=12; ++idx){
        stack.push(idx);
    }
    cout << "此时栈中是否已满？" << stack.full() << endl;

    while(!stack.empty()){
        cout << stack.top() << endl;
        stack.pop();
    }
    cout << "此时栈中是否为空？" << stack.empty() << endl;

    return 0;
}

