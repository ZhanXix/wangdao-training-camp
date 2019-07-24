/*
编写一个类，实现简单的栈。栈中有以下操作：
		   > 元素入栈     void push(int);
		   > 元素出栈     void pop();
		   > 读出栈顶元素 int top();
		   > 判断栈空     bool emty();
		   > 判断栈满     bool full();
	 如果栈溢出，程序终止。栈的数据成员由存放
	 10个整型数据的数组构成。先后做如下操作：
	     > 创建栈
	     > 将10入栈
	     > 将12入栈
	     > 将14入栈
	     > 读出并输出栈顶元素
	     > 出栈
	     > 读出并输出栈顶元素
*/

#include <iostream>
using std::cout;
using std::endl;

class Stack
{
public:
    Stack()
    : _top(0)
    {
        cout << "Stack()" << endl;
    }

    void push(int val)
    {
        cout << "PUSH " << val << endl;
        _arr[_top] = val;          
        ++_top;
    }

    void pop()
    {
        cout << "POP" << endl;
        --_top;
    }

    int top()
    {
        if(_top>=1)
        {
            return _arr[_top-1];
        }else{
            return 0;
        }
    }

    bool empty()
    {
        if(0 == _top)
        {
            return true;
        }else{
            return false;
        }
    }

    bool full()
    {
        if(10 == _top)
        {
            return true;
        }else{
            return false;
        }
    }

private:
    int _arr[10];
    int _top;
};


int main()
{
    Stack st;
    st.push(10);
    st.push(12);
    st.push(14);
    cout << "st.top() = " <<st.top() << endl;
    st.pop();
    cout << "st.top() = " <<st.top() << endl;

    return 0;
}

